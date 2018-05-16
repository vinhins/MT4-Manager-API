//+------------------------------------------------------------------+
//|                                  MetaTrader 4 Manager API Sample |
//|                   Copyright 2001-2014, MetaQuotes Software Corp. |
//|                                        http://www.metaquotes.net |
//+------------------------------------------------------------------+
#include "stdafx.h"
#include "ManagerAPISample.h"
#include "ManagerSheet.h"

//+------------------------------------------------------------------+
//|                                                                  |
//+------------------------------------------------------------------+
HWND CManagerSheet::hwndThis=NULL;
//+------------------------------------------------------------------+
//|                                                                  |
//+------------------------------------------------------------------+
IMPLEMENT_DYNAMIC(CManagerSheet, CPropertySheetEx)
//+------------------------------------------------------------------+
//|                                                                  |
//+------------------------------------------------------------------+
CManagerSheet::CManagerSheet(UINT nIDCaption,CWnd *pParentWnd,UINT iSelectPage) : CPropertySheetEx(nIDCaption,pParentWnd,iSelectPage)
  {
   m_psh.dwFlags|=PSH_NOAPPLYNOW;
   m_psh.dwFlags&=~PSH_HASHELP;
   AddPage(&m_main);
   AddPage(&m_mw);
   AddPage(&m_symbols);
   AddPage(&m_users);
   AddPage(&m_online);
   AddPage(&m_orders);
   AddPage(&m_summary);
   AddPage(&m_exposure);
   AddPage(&m_margin);
   AddPage(&m_requests);
   AddPage(&m_plugins);
   AddPage(&m_dealer);
   AddPage(&m_mailbox);
   AddPage(&m_news);
   AddPage(&m_reports);
   AddPage(&m_daily);
   AddPage(&m_journal);
   AddPage(&m_logs);
  }
//+------------------------------------------------------------------+
//|                                                                  |
//+------------------------------------------------------------------+
CManagerSheet::~CManagerSheet()
  {
  }
//+------------------------------------------------------------------+
//|                                                                  |
//+------------------------------------------------------------------+
BEGIN_MESSAGE_MAP(CManagerSheet, CPropertySheetEx)
   //{{AFX_MSG_MAP(CManagerSheet)
   ON_WM_DESTROY()
   //}}AFX_MSG_MAP
   ON_REGISTERED_MESSAGE(ExtPumpingMsg, OnPumpingMsg)
END_MESSAGE_MAP()
//+------------------------------------------------------------------+
//|                                                                  |
//+------------------------------------------------------------------+
BOOL CManagerSheet::OnInitDialog()
  {
   BOOL bResult=CPropertySheetEx::OnInitDialog();
//---
   hwndThis=GetSafeHwnd();
//---
   SetActivePage(&m_logs);
   SetActivePage(&m_news);
   SetActivePage(&m_mailbox);
   SetActivePage(&m_plugins);
   SetActivePage(&m_requests);
   SetActivePage(&m_margin);
   SetActivePage(&m_exposure);
   SetActivePage(&m_summary);
   SetActivePage(&m_orders);
   SetActivePage(&m_online);
   SetActivePage(&m_users);
   SetActivePage(&m_mw);
   SetActivePage(&m_main);
//---
   return(bResult);
  }
//+------------------------------------------------------------------+
//|                                                                  |
//+------------------------------------------------------------------+
void CManagerSheet::OnDestroy()
  {
   hwndThis=NULL;
   CPropertySheetEx::OnDestroy();
  }
//+------------------------------------------------------------------+
//|                                                                  |
//+------------------------------------------------------------------+
LRESULT CManagerSheet::OnPumpingMsg(WPARAM wParam,LPARAM)
  {
//---
   switch(wParam)
     {
      case PUMP_START_PUMPING:
         m_logs.LogOut("PUMP_START_PUMPING");
         m_mw.PostMessage(ExtPumpingMsg,PUMP_START_PUMPING);
         break;
      case PUMP_STOP_PUMPING:
         m_logs.LogOut("PUMP_STOP_PUMPING");
         break;
      case PUMP_UPDATE_BIDASK:
         m_mw.PostMessage(ExtPumpingMsg,PUMP_UPDATE_BIDASK);
         m_orders.PostMessage(ExtPumpingMsg,PUMP_UPDATE_BIDASK);
         m_summary.PostMessage(ExtPumpingMsg,PUMP_UPDATE_BIDASK);
         break;
      case PUMP_UPDATE_SYMBOLS:
         m_logs.LogOut("PUMP_UPDATE_SYMBOLS");
         m_mw.PostMessage(ExtPumpingMsg,PUMP_UPDATE_SYMBOLS);
         m_summary.PostMessage(ExtPumpingMsg,PUMP_UPDATE_SYMBOLS);
         break;
      case PUMP_UPDATE_GROUPS:
         m_logs.LogOut("PUMP_UPDATE_GROUPS");
         break;
      case PUMP_UPDATE_USERS:
         m_logs.LogOut("PUMP_UPDATE_USERS");
         m_users.PostMessage(ExtPumpingMsg,PUMP_UPDATE_USERS);
         break;
      case PUMP_UPDATE_ONLINE:
         m_logs.LogOut("PUMP_UPDATE_ONLINE");
         m_online.PostMessage(ExtPumpingMsg,PUMP_UPDATE_ONLINE);
         break;
      case PUMP_UPDATE_TRADES:
         m_logs.LogOut("PUMP_UPDATE_TRADES");
         m_orders.PostMessage(ExtPumpingMsg,PUMP_UPDATE_TRADES);
         m_summary.PostMessage(ExtPumpingMsg,PUMP_UPDATE_TRADES);
         m_exposure.PostMessage(ExtPumpingMsg,PUMP_UPDATE_TRADES);
         m_margin.PostMessage(ExtPumpingMsg,PUMP_UPDATE_TRADES);
         break;
      case PUMP_UPDATE_ACTIVATION:
         m_logs.LogOut("PUMP_UPDATE_ACTIVATION");
         break;
      case PUMP_UPDATE_MARGINCALL:
         m_logs.LogOut("PUMP_UPDATE_MARGINCALL");
         m_margin.PostMessage(ExtPumpingMsg,PUMP_UPDATE_MARGINCALL);
         break;
      case PUMP_UPDATE_REQUESTS:
         m_logs.LogOut("PUMP_UPDATE_REQUESTS");
         m_requests.PostMessage(ExtPumpingMsg,PUMP_UPDATE_REQUESTS);
         break;
      case PUMP_UPDATE_PLUGINS:
         m_logs.LogOut("PUMP_UPDATE_PLUGINS");
         m_plugins.PostMessage(ExtPumpingMsg,PUMP_UPDATE_PLUGINS);
         break;
      case PUMP_UPDATE_NEWS:
         m_logs.LogOut("PUMP_UPDATE_NEWS");
         m_news.PostMessage(ExtPumpingMsg,PUMP_UPDATE_NEWS);
         break;
      case PUMP_UPDATE_MAIL:
         m_logs.LogOut("PUMP_UPDATE_MAIL");
         m_mailbox.PostMessage(ExtPumpingMsg,PUMP_UPDATE_MAIL);
         break;
      default: break;
     }
//---
   return(0);
  }
//+------------------------------------------------------------------+
//|                                                                  |
//+------------------------------------------------------------------+
void __stdcall CManagerSheet::PumpingFunc(int code)
  {
   if(hwndThis==NULL) return;
//---
   switch(code)
     {
      case PUMP_START_PUMPING:
         ::PostMessage(hwndThis,ExtPumpingMsg,PUMP_START_PUMPING,0);
         break;
      case PUMP_STOP_PUMPING:
         ::PostMessage(hwndThis,ExtPumpingMsg,PUMP_STOP_PUMPING,0);
         break;
      case PUMP_UPDATE_BIDASK:
         ::PostMessage(hwndThis,ExtPumpingMsg,PUMP_UPDATE_BIDASK,0);
         break;
      case PUMP_UPDATE_SYMBOLS:
         ::PostMessage(hwndThis,ExtPumpingMsg,PUMP_UPDATE_SYMBOLS,0);
         break;
      case PUMP_UPDATE_GROUPS:
         ::PostMessage(hwndThis,ExtPumpingMsg,PUMP_UPDATE_GROUPS,0);
         break;
      case PUMP_UPDATE_USERS:
         ::PostMessage(hwndThis,ExtPumpingMsg,PUMP_UPDATE_USERS,0);
         break;
      case PUMP_UPDATE_ONLINE:
         ::PostMessage(hwndThis,ExtPumpingMsg,PUMP_UPDATE_ONLINE,0);
         break;
      case PUMP_UPDATE_TRADES:
         ::PostMessage(hwndThis,ExtPumpingMsg,PUMP_UPDATE_TRADES,0);
         break;
      case PUMP_UPDATE_ACTIVATION:
         ::PostMessage(hwndThis,ExtPumpingMsg,PUMP_UPDATE_ACTIVATION,0);
         break;
      case PUMP_UPDATE_MARGINCALL:
         ::PostMessage(hwndThis,ExtPumpingMsg,PUMP_UPDATE_MARGINCALL,0);
         break;
      case PUMP_UPDATE_REQUESTS:
         ::PostMessage(hwndThis,ExtPumpingMsg,PUMP_UPDATE_REQUESTS,0);
         break;
      case PUMP_UPDATE_PLUGINS:
         ::PostMessage(hwndThis,ExtPumpingMsg,PUMP_UPDATE_PLUGINS,0);
         break;
      case PUMP_UPDATE_NEWS:
         ::PostMessage(hwndThis,ExtPumpingMsg,PUMP_UPDATE_NEWS,0);
         break;
      case PUMP_UPDATE_MAIL:
         ::PostMessage(hwndThis,ExtPumpingMsg,PUMP_UPDATE_MAIL,0);
         break;
      default: break;
     }
//---
  }
//+------------------------------------------------------------------+
//|                                                                  |
//+------------------------------------------------------------------+
