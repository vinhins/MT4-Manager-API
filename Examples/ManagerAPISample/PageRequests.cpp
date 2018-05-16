//+------------------------------------------------------------------+
//|                                  MetaTrader 4 Manager API Sample |
//|                   Copyright 2001-2014, MetaQuotes Software Corp. |
//|                                        http://www.metaquotes.net |
//+------------------------------------------------------------------+
#include "stdafx.h"
#include "ManagerAPISample.h"
#include "PageRequests.h"

//+------------------------------------------------------------------+
//|                                                                  |
//+------------------------------------------------------------------+
IMPLEMENT_DYNCREATE(CPageRequests, CPropertyPageEx)
//+------------------------------------------------------------------+
//|                                                                  |
//+------------------------------------------------------------------+
CPageRequests::CPageRequests() : CPropertyPageEx(CPageRequests::IDD)
  {
   //{{AFX_DATA_INIT(CPageRequests)
   //}}AFX_DATA_INIT
   m_psp.dwFlags&=~PSP_HASHELP;
  }
//+------------------------------------------------------------------+
//|                                                                  |
//+------------------------------------------------------------------+
CPageRequests::~CPageRequests()
  {
  }
//+------------------------------------------------------------------+
//|                                                                  |
//+------------------------------------------------------------------+
void CPageRequests::DoDataExchange(CDataExchange* pDX)
  {
   CPropertyPageEx::DoDataExchange(pDX);
   //{{AFX_DATA_MAP(CPageRequests)
   DDX_Control(pDX, IDC_REQUESTS, m_Requests);
   //}}AFX_DATA_MAP
  }
//+------------------------------------------------------------------+
//|                                                                  |
//+------------------------------------------------------------------+
BEGIN_MESSAGE_MAP(CPageRequests, CPropertyPageEx)
   //{{AFX_MSG_MAP(CPageRequests)
   //}}AFX_MSG_MAP
   ON_REGISTERED_MESSAGE(ExtPumpingMsg, OnPumpingMsg)
END_MESSAGE_MAP()
//+------------------------------------------------------------------+
//|                                                                  |
//+------------------------------------------------------------------+
BOOL CPageRequests::OnInitDialog()
  {
   CRect rc;
   int   cx=0;
//---
   CPropertyPageEx::OnInitDialog();
//---
   m_Requests.SetExtendedStyle(LVS_EX_FULLROWSELECT);
   m_Requests.GetWindowRect(&rc);
   cx=(rc.Width()-::GetSystemMetrics(SM_CXVSCROLL)-::GetSystemMetrics(SM_CXBORDER)*4)/4;
   m_Requests.InsertColumn(0,"Login",  LVCFMT_LEFT,cx);
   m_Requests.InsertColumn(1,"Request",LVCFMT_LEFT,cx*3);
//---
   return(TRUE);
  }
//+------------------------------------------------------------------+
//|                                                                  |
//+------------------------------------------------------------------+
LRESULT CPageRequests::OnPumpingMsg(WPARAM wParam,LPARAM)
  {
//---
   if(wParam==PUMP_UPDATE_REQUESTS)
     {
      RequestInfo *info=NULL;
      int          total=0;
      char         tmp[256]="";
      //---
      info=ExtManagerPump->RequestsGet(&total);
      m_Requests.DeleteAllItems();
      for(int i=0; i<total; i++)
        {
         _snprintf(tmp,sizeof(tmp)-1,"%d",info[i].login);
         m_Requests.InsertItem(i,tmp);
         m_Requests.SetItemText(i,1,info[i].trade.symbol);
        }
      //---
     }
//---
   return(0);
  }
//+------------------------------------------------------------------+
//|                                                                  |
//+------------------------------------------------------------------+
