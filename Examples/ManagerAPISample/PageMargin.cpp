//+------------------------------------------------------------------+
//|                                  MetaTrader 4 Manager API Sample |
//|                   Copyright 2001-2014, MetaQuotes Software Corp. |
//|                                        http://www.metaquotes.net |
//+------------------------------------------------------------------+
#include "stdafx.h"
#include "ManagerAPISample.h"
#include "PageMargin.h"
//---
//+------------------------------------------------------------------+
//|                                                                  |
//+------------------------------------------------------------------+
IMPLEMENT_DYNCREATE(CPageMargin, CPropertyPageEx)
//+------------------------------------------------------------------+
//|                                                                  |
//+------------------------------------------------------------------+
CPageMargin::CPageMargin() : CPropertyPageEx(CPageMargin::IDD),
   m_levels(NULL),m_levels_total(0)
  {
   //{{AFX_DATA_INIT(CPageMargin)
   //}}AFX_DATA_INIT
   m_psp.dwFlags&=~PSP_HASHELP;
  }
//+------------------------------------------------------------------+
//|                                                                  |
//+------------------------------------------------------------------+
CPageMargin::~CPageMargin()
  {
  }
//+------------------------------------------------------------------+
//|                                                                  |
//+------------------------------------------------------------------+
void CPageMargin::DoDataExchange(CDataExchange* pDX)
  {
   CPropertyPageEx::DoDataExchange(pDX);
   //{{AFX_DATA_MAP(CPageMargin)
   DDX_Control(pDX, IDC_USERS, m_Users);
   //}}AFX_DATA_MAP
  }
//+------------------------------------------------------------------+
//|                                                                  |
//+------------------------------------------------------------------+
BEGIN_MESSAGE_MAP(CPageMargin, CPropertyPageEx)
   //{{AFX_MSG_MAP(CPageMargin)
   ON_NOTIFY(LVN_GETDISPINFO, IDC_USERS, OnGetdispinfoUsers)
   ON_WM_DESTROY()
   //}}AFX_MSG_MAP
   ON_REGISTERED_MESSAGE(ExtPumpingMsg, OnPumpingMsg)
END_MESSAGE_MAP()
//+------------------------------------------------------------------+
//|                                                                  |
//+------------------------------------------------------------------+
BOOL CPageMargin::OnInitDialog()
  {
   CRect rc;
   int   cx=0;
//---
   CPropertyPageEx::OnInitDialog();
//---
   m_Users.GetClientRect(&rc);
   cx=(rc.Width()-::GetSystemMetrics(SM_CXVSCROLL)-::GetSystemMetrics(SM_CXBORDER)*4)/4;
   m_Users.SetExtendedStyle(LVS_EX_FULLROWSELECT);
   m_Users.InsertColumn(0,"Login", LVCFMT_LEFT,cx);
   m_Users.InsertColumn(1,"Margin",LVCFMT_RIGHT,cx);
   m_Users.InsertColumn(2,"Free",  LVCFMT_RIGHT,cx);
   m_Users.InsertColumn(3,"Level", LVCFMT_RIGHT,cx);
//---
   return(TRUE);
  }
//+------------------------------------------------------------------+
//|                                                                  |
//+------------------------------------------------------------------+
void CPageMargin::OnDestroy()
  {
//---
   if(m_levels!=NULL) { ExtManagerPump->MemFree(m_levels); m_levels=NULL; m_levels_total=0; }
//---
   CPropertyPageEx::OnDestroy();
  }
//+------------------------------------------------------------------+
//|                                                                  |
//+------------------------------------------------------------------+
LRESULT CPageMargin::OnPumpingMsg(WPARAM wParam,LPARAM)
  {
//---
   if(wParam==PUMP_UPDATE_TRADES || wParam==PUMP_UPDATE_MARGINCALL)
     {
      if(m_levels!=NULL)
        {
         ExtManagerPump->MemFree(m_levels);
         m_levels=NULL; m_levels_total=0;
        }
      m_levels=ExtManagerPump->MarginsGet(&m_levels_total);
      m_Users.SetItemCount(m_levels_total);
     }
//---
   return(0);
  }
//+------------------------------------------------------------------+
//|                                                                  |
//+------------------------------------------------------------------+
void CPageMargin::OnGetdispinfoUsers(NMHDR *pNMHDR,LRESULT *pResult)
  {
   LV_DISPINFO* pDI=(LV_DISPINFO*)pNMHDR;
   if(pResult!=NULL) *pResult=0;
//---
   char tmp[256]="";
   int  i=pDI->item.iItem;
   if(i<0 || i>=m_levels_total) return;
//---
   if(pDI->item.mask&LVIF_TEXT)
     {
      switch(pDI->item.iSubItem)
        {
         case 0: _snprintf(tmp,sizeof(tmp)-1,"%d",m_levels[i].login);            break;
         case 1: _snprintf(tmp,sizeof(tmp)-1,"%.02lf",m_levels[i].margin);       break;
         case 2: _snprintf(tmp,sizeof(tmp)-1,"%.02lf",m_levels[i].margin_free);  break;
         case 3:
            if(m_levels[i].margin>0.0)
               _snprintf(tmp,sizeof(tmp)-1,"%.01lf%%",m_levels[i].margin_level);
            break;
         default: break;
        }
      pDI->item.pszText=tmp;
     }
//---
  }
//+------------------------------------------------------------------+
//|                                                                  |
//+------------------------------------------------------------------+
