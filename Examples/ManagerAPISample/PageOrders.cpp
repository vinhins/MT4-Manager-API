//+------------------------------------------------------------------+
//|                                  MetaTrader 4 Manager API Sample |
//|                   Copyright 2001-2014, MetaQuotes Software Corp. |
//|                                        http://www.metaquotes.net |
//+------------------------------------------------------------------+
#include "stdafx.h"
#include "ManagerAPISample.h"
#include "PageOrders.h"
#include "dialogs\RequestDlg.h"
#include "dialogs\UserHistoryDlg.h"

//+------------------------------------------------------------------+
//|                                                                  |
//+------------------------------------------------------------------+
IMPLEMENT_DYNCREATE(CPageOrders, CPropertyPageEx)
//+------------------------------------------------------------------+
//|                                                                  |
//+------------------------------------------------------------------+
CPageOrders::CPageOrders() : CPropertyPageEx(CPageOrders::IDD),
   m_trades(NULL),m_trades_total(0),m_show_pump(FALSE)
  {
   //{{AFX_DATA_INIT(CPageOrders)
   //}}AFX_DATA_INIT
   m_psp.dwFlags&=~PSP_HASHELP;
  }
//+------------------------------------------------------------------+
//|                                                                  |
//+------------------------------------------------------------------+
CPageOrders::~CPageOrders()
  {
  }
//+------------------------------------------------------------------+
//|                                                                  |
//+------------------------------------------------------------------+
void CPageOrders::DoDataExchange(CDataExchange* pDX)
  {
   CPropertyPageEx::DoDataExchange(pDX);
   //{{AFX_DATA_MAP(CPageOrders)
   DDX_Control(pDX, IDC_ORDERS, m_Orders);
   //}}AFX_DATA_MAP
  }
//+------------------------------------------------------------------+
//|                                                                  |
//+------------------------------------------------------------------+
BEGIN_MESSAGE_MAP(CPageOrders, CPropertyPageEx)
   //{{AFX_MSG_MAP(CPageOrders)
   ON_WM_DESTROY()
   ON_BN_CLICKED(IDC_REQUEST, OnRequest)
   ON_NOTIFY(LVN_GETDISPINFO, IDC_ORDERS, OnGetdispinfoOrders)
   ON_BN_CLICKED(IDC_HISTORY, OnHistory)
   ON_BN_CLICKED(IDC_ORDERS_GET, OnOrdersGet)
   //}}AFX_MSG_MAP
   ON_REGISTERED_MESSAGE(ExtPumpingMsg, OnPumpingMsg)
END_MESSAGE_MAP()
//+------------------------------------------------------------------+
//|                                                                  |
//+------------------------------------------------------------------+
BOOL CPageOrders::OnInitDialog()
  {
   CRect rc;
   int   cx=0;
//---
   CPropertyPageEx::OnInitDialog();
//---
   m_Orders.SetExtendedStyle(LVS_EX_FULLROWSELECT);
   m_Orders.GetWindowRect(&rc);
   cx=(rc.Width()-::GetSystemMetrics(SM_CXVSCROLL)-::GetSystemMetrics(SM_CXBORDER)*4)/5;
   m_Orders.InsertColumn(0,"Deal",  LVCFMT_LEFT,cx);
   m_Orders.InsertColumn(1,"Login", LVCFMT_LEFT,cx);
   m_Orders.InsertColumn(2,"Type",  LVCFMT_LEFT,cx);
   m_Orders.InsertColumn(3,"Symbol",LVCFMT_LEFT,cx);
   m_Orders.InsertColumn(4,"Profit",LVCFMT_RIGHT,cx);
//---
   return(TRUE);
  }
//+------------------------------------------------------------------+
//|                                                                  |
//+------------------------------------------------------------------+
void CPageOrders::OnDestroy()
  {
//---
   if(m_trades!=NULL) { ExtManager->MemFree(m_trades); m_trades=NULL; m_trades_total=0; }
//---
   CPropertyPageEx::OnDestroy();
  }
//+------------------------------------------------------------------+
//|                                                                  |
//+------------------------------------------------------------------+
LRESULT CPageOrders::OnPumpingMsg(WPARAM wParam,LPARAM)
  {
   switch(wParam)
     {
      case PUMP_UPDATE_TRADES: OnOrdersGet(); break;
      default: break;
     }
   return(0);
  }
//+------------------------------------------------------------------+
//|                                                                  |
//+------------------------------------------------------------------+
void CPageOrders::OnRequest()
  {
   int order=0;
//---
   CRequestDlg dlg;
   if(dlg.DoModal()!=IDOK) return;
   order=dlg.GetInt();
//---
   AfxGetApp()->BeginWaitCursor();
   if(m_trades!=NULL) { ExtManager->MemFree(m_trades); m_trades=NULL; m_trades_total=0; }
   if(order==0) m_trades=ExtManager->TradesRequest(&m_trades_total);
   else       { m_trades_total=1; m_trades=ExtManager->TradeRecordsRequest(&order,&m_trades_total); }
   AfxGetApp()->EndWaitCursor();
//---
   m_show_pump=FALSE;
   m_Orders.SetItemCount(m_trades_total);
  }
//+------------------------------------------------------------------+
//|                                                                  |
//+------------------------------------------------------------------+
void CPageOrders::OnOrdersGet()
  {
//---
   if(m_trades!=NULL) { ExtManager->MemFree(m_trades); m_trades=NULL; m_trades_total=0; }
   m_trades=ExtManagerPump->TradesGet(&m_trades_total);
//---
   m_show_pump=TRUE;
   m_Orders.SetItemCount(m_trades_total);
  }
//+------------------------------------------------------------------+
//|                                                                  |
//+------------------------------------------------------------------+
void CPageOrders::OnHistory()
  {
   int    login=0;
   time_t from=0,to=0;
//---
   CUserHistoryDlg dlg;
   if(dlg.DoModal()!=IDOK) return;
   login=dlg.GetLogin();
   from =dlg.GetFrom();
   to   =dlg.GetTo();
//---
   AfxGetApp()->BeginWaitCursor();
   if(m_trades!=NULL) { ExtManager->MemFree(m_trades); m_trades=NULL; m_trades_total=0; }
   m_trades=ExtManager->TradesUserHistory(login,from,to,&m_trades_total);
   AfxGetApp()->EndWaitCursor();
//---
   m_show_pump=FALSE;
   m_Orders.SetItemCount(m_trades_total);
  }
//+------------------------------------------------------------------+
//|                                                                  |
//+------------------------------------------------------------------+
void CPageOrders::OnGetdispinfoOrders(NMHDR *pNMHDR,LRESULT *pResult)
  {
   static LPSTR types[]={ "buy","sell","buy limit","sell limit","buy stop","sell stop","balance","credit" };
   LV_DISPINFO* pDI=(LV_DISPINFO*)pNMHDR;
   if(pResult!=NULL) *pResult=0;
//---
   char tmp[256]="";
   int  i=pDI->item.iItem;
   if(i<0 || i>=m_trades_total) return;
//---
   if(pDI->item.mask&LVIF_TEXT)
     {
      switch(pDI->item.iSubItem)
        {
         case 0: _snprintf(tmp,sizeof(tmp)-1,"%d",m_trades[i].order); break;
         case 1: _snprintf(tmp,sizeof(tmp)-1,"%d",m_trades[i].login); break;
         case 2: COPY_STR(tmp,types[m_trades[i].cmd]); break;
         case 3: COPY_STR(tmp,m_trades[i].symbol);     break;
         case 4: _snprintf(tmp,sizeof(tmp)-1,"%.02lf",m_trades[i].profit); break;
         default: break;
        }
      pDI->item.pszText=tmp;
     }
//---
  }
//+------------------------------------------------------------------+
//|                                                                  |
//+------------------------------------------------------------------+
