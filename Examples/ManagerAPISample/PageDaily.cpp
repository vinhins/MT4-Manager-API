//+------------------------------------------------------------------+
//|                                  MetaTrader 4 Manager API Sample |
//|                   Copyright 2001-2014, MetaQuotes Software Corp. |
//|                                        http://www.metaquotes.net |
//+------------------------------------------------------------------+
#include "stdafx.h"
#include "ManagerAPISample.h"
#include "PageDaily.h"

//+------------------------------------------------------------------+
//|                                                                  |
//+------------------------------------------------------------------+
IMPLEMENT_DYNCREATE(CPageDaily, CPropertyPageEx)
//+------------------------------------------------------------------+
//|                                                                  |
//+------------------------------------------------------------------+
CPageDaily::CPageDaily() : CPropertyPageEx(CPageDaily::IDD),m_daily(NULL),m_daily_total(0)
  {
   //{{AFX_DATA_INIT(CPageDaily)
   //}}AFX_DATA_INIT
   m_psp.dwFlags&=~PSP_HASHELP;
  }
//+------------------------------------------------------------------+
//|                                                                  |
//+------------------------------------------------------------------+
CPageDaily::~CPageDaily()
  {
  }
//+------------------------------------------------------------------+
//|                                                                  |
//+------------------------------------------------------------------+
void CPageDaily::DoDataExchange(CDataExchange* pDX)
  {
   CPropertyPageEx::DoDataExchange(pDX);
   //{{AFX_DATA_MAP(CPageDaily)
   DDX_Control(pDX, IDC_DAILY, m_Daily);
   //}}AFX_DATA_MAP
  }
//+------------------------------------------------------------------+
//|                                                                  |
//+------------------------------------------------------------------+
BEGIN_MESSAGE_MAP(CPageDaily, CPropertyPageEx)
   //{{AFX_MSG_MAP(CPageDaily)
   ON_WM_DESTROY()
   ON_BN_CLICKED(IDC_REQUEST, OnRequest)
   ON_NOTIFY(LVN_GETDISPINFO, IDC_DAILY, OnGetdispinfoDaily)
   //}}AFX_MSG_MAP
END_MESSAGE_MAP()
//+------------------------------------------------------------------+
//|                                                                  |
//+------------------------------------------------------------------+
BOOL CPageDaily::OnInitDialog()
  {
   CRect rc;
   int   cx=0;
//---
   CPropertyPageEx::OnInitDialog();
//---
   m_Daily.SetExtendedStyle(LVS_EX_FULLROWSELECT);
   m_Daily.GetWindowRect(&rc);
   cx=(rc.Width()-::GetSystemMetrics(SM_CXVSCROLL)-::GetSystemMetrics(SM_CXBORDER)*4)/5;
   m_Daily.InsertColumn(0,"Time",   LVCFMT_LEFT,cx);
   m_Daily.InsertColumn(1,"Login",  LVCFMT_LEFT,cx);
   m_Daily.InsertColumn(2,"Balance",LVCFMT_RIGHT,cx);
   m_Daily.InsertColumn(3,"Credit", LVCFMT_RIGHT,cx);
   m_Daily.InsertColumn(4,"Equity", LVCFMT_RIGHT,cx);
//---
   return(TRUE);
  }
//+------------------------------------------------------------------+
//|                                                                  |
//+------------------------------------------------------------------+
void CPageDaily::OnDestroy()
  {
//---
   if(m_daily!=NULL)
     {
      ExtManager->MemFree(m_daily);
      m_daily=NULL;
      m_daily_total=0;
     }
//---
   CPropertyPageEx::OnDestroy();
  }
//+------------------------------------------------------------------+
//|                                                                  |
//+------------------------------------------------------------------+
void CPageDaily::OnRequest()
  {
   DailyGroupRequest req={ "group",0,time(NULL),1000 };
   int logins[1000];
//---
   for(int i=0; i<req.total; i++) logins[i]=1000+i;
//---
   m_Daily.SetItemCount(0);
//---
   AfxGetApp()->BeginWaitCursor();
   if(m_daily!=NULL)
     {
      ExtManager->MemFree(m_daily);
      m_daily=NULL;
      m_daily_total=0;
     }
   m_daily=ExtManager->DailyReportsRequest(&req,logins,&m_daily_total);
   AfxGetApp()->EndWaitCursor();
//---
   m_Daily.SetItemCount(m_daily_total);
  }
//+------------------------------------------------------------------+
//|                                                                  |
//+------------------------------------------------------------------+
void CPageDaily::OnGetdispinfoDaily(NMHDR *pNMHDR,LRESULT *pResult)
  {
   LV_DISPINFO* pDI=(LV_DISPINFO*)pNMHDR;
   if(pResult!=NULL) *pResult=0;
//---
   char tmp[256]="";
   int  i=pDI->item.iItem;
   if(i<0 || i>=m_daily_total) return;
//---
   if(pDI->item.mask&LVIF_TEXT)
     {
      switch(pDI->item.iSubItem)
        {
         case 0:
           {
            tm *ptm=gmtime(&m_daily[i].ctm);
            _snprintf(tmp,sizeof(tmp)-1,"%.04d.%.02d.%.02d",ptm->tm_year+1900,ptm->tm_mon+1,ptm->tm_mday);
            break;
           }
         case 1: _snprintf(tmp,sizeof(tmp)-1,"%d",m_daily[i].login);       break;
         case 2: _snprintf(tmp,sizeof(tmp)-1,"%.02lf",m_daily[i].balance); break;
         case 3: _snprintf(tmp,sizeof(tmp)-1,"%.02lf",m_daily[i].credit);  break;
         case 4: _snprintf(tmp,sizeof(tmp)-1,"%.02lf",m_daily[i].equity);  break;
         default: break;
        }
      pDI->item.pszText=tmp;
     }
//---
  }
//+------------------------------------------------------------------+
//|                                                                  |
//+------------------------------------------------------------------+
