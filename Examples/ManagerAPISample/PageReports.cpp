//+------------------------------------------------------------------+
//|                                  MetaTrader 4 Manager API Sample |
//|                   Copyright 2001-2014, MetaQuotes Software Corp. |
//|                                        http://www.metaquotes.net |
//+------------------------------------------------------------------+
#include "stdafx.h"
#include "ManagerAPISample.h"
#include "PageReports.h"

//+------------------------------------------------------------------+
//|                                                                  |
//+------------------------------------------------------------------+
IMPLEMENT_DYNCREATE(CPageReports, CPropertyPageEx)
//+------------------------------------------------------------------+
//|                                                                  |
//+------------------------------------------------------------------+
CPageReports::CPageReports() : CPropertyPageEx(CPageReports::IDD),
   m_trades(NULL),m_trades_total(0)
  {
   //{{AFX_DATA_INIT(CPageReports)
   //}}AFX_DATA_INIT
   m_psp.dwFlags&=~PSP_HASHELP;
  }
//+------------------------------------------------------------------+
//|                                                                  |
//+------------------------------------------------------------------+
CPageReports::~CPageReports()
  {
  }
//+------------------------------------------------------------------+
//|                                                                  |
//+------------------------------------------------------------------+
void CPageReports::DoDataExchange(CDataExchange* pDX)
  {
   CPropertyPageEx::DoDataExchange(pDX);
   //{{AFX_DATA_MAP(CPageReports)
   DDX_Control(pDX, IDC_ORDERS, m_Orders);
   //}}AFX_DATA_MAP
  }
//+------------------------------------------------------------------+
//|                                                                  |
//+------------------------------------------------------------------+
BEGIN_MESSAGE_MAP(CPageReports, CPropertyPageEx)
   //{{AFX_MSG_MAP(CPageReports)
   ON_WM_DESTROY()
   ON_BN_CLICKED(IDC_REQUEST, OnRequest)
   ON_NOTIFY(LVN_GETDISPINFO, IDC_ORDERS, OnGetdispinfoOrders)
   //}}AFX_MSG_MAP
END_MESSAGE_MAP()
//+------------------------------------------------------------------+
//|                                                                  |
//+------------------------------------------------------------------+
BOOL CPageReports::OnInitDialog()
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
void CPageReports::OnDestroy()
  {
//---
   if(m_trades!=NULL) { ExtManager->MemFree(m_trades); m_trades=NULL; m_trades_total=0; }
//---
   CPropertyPageEx::OnDestroy();
  }
//+------------------------------------------------------------------+
//|                                                                  |
//+------------------------------------------------------------------+
void CPageReports::OnRequest()
  {
   ReportGroupRequest req={ "group",0,time(NULL),1000 };
   int logins[1000];
//---
   for(int i=0; i<req.total; i++) logins[i]=1000+i;
//---
   m_Orders.SetItemCount(0);
//---
   AfxGetApp()->BeginWaitCursor();
   if(m_trades!=NULL) { ExtManager->MemFree(m_trades); m_trades=NULL; m_trades_total=0; }
   m_trades=ExtManager->ReportsRequest(&req,logins,&m_trades_total);
   AfxGetApp()->EndWaitCursor();
//---
   m_Orders.SetItemCount(m_trades_total);
  }
//+------------------------------------------------------------------+
//|                                                                  |
//+------------------------------------------------------------------+
void CPageReports::OnGetdispinfoOrders(NMHDR *pNMHDR,LRESULT *pResult)
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
