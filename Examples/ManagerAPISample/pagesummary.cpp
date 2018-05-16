//+------------------------------------------------------------------+
//|                                  MetaTrader 4 Manager API Sample |
//|                   Copyright 2001-2014, MetaQuotes Software Corp. |
//|                                        http://www.metaquotes.net |
//+------------------------------------------------------------------+
#include "stdafx.h"
#include "ManagerAPISample.h"
#include "pagesummary.h"
//---
//+------------------------------------------------------------------+
//|                                                                  |
//+------------------------------------------------------------------+
IMPLEMENT_DYNCREATE(CPageSummary, CPropertyPageEx)
//+------------------------------------------------------------------+
//|                                                                  |
//+------------------------------------------------------------------+
CPageSummary::CPageSummary() : CPropertyPageEx(CPageSummary::IDD),
   m_summary(NULL),m_summary_total(0)
  {
   //{{AFX_DATA_INIT(CPageSummary)
   //}}AFX_DATA_INIT
   m_psp.dwFlags&=~PSP_HASHELP;
  }
//+------------------------------------------------------------------+
//|                                                                  |
//+------------------------------------------------------------------+
CPageSummary::~CPageSummary()
  {
  }
//+------------------------------------------------------------------+
//|                                                                  |
//+------------------------------------------------------------------+
void CPageSummary::DoDataExchange(CDataExchange* pDX)
  {
   CPropertyPageEx::DoDataExchange(pDX);
   //{{AFX_DATA_MAP(CPageSummary)
   DDX_Control(pDX, IDC_SUMMARY, m_Summary);
   //}}AFX_DATA_MAP
  }
//+------------------------------------------------------------------+
//|                                                                  |
//+------------------------------------------------------------------+
BEGIN_MESSAGE_MAP(CPageSummary, CPropertyPageEx)
   //{{AFX_MSG_MAP(CPageSummary)
   ON_NOTIFY(LVN_GETDISPINFO, IDC_SUMMARY, OnGetdispinfoSummary)
   ON_WM_DESTROY()
   //}}AFX_MSG_MAP
   ON_REGISTERED_MESSAGE(ExtPumpingMsg, OnPumpingMsg)
END_MESSAGE_MAP()
//+------------------------------------------------------------------+
//|                                                                  |
//+------------------------------------------------------------------+
BOOL CPageSummary::OnInitDialog()
  {
   CRect rc;
   int   cx=0;
//---
   CPropertyPageEx::OnInitDialog();
//---
   m_Summary.GetClientRect(&rc);
   cx=(rc.Width()-::GetSystemMetrics(SM_CXVSCROLL)-::GetSystemMetrics(SM_CXBORDER)*4)/4;
   m_Summary.SetExtendedStyle(LVS_EX_FULLROWSELECT);
   m_Summary.InsertColumn(0,"Symbol",   LVCFMT_LEFT, cx);
   m_Summary.InsertColumn(1,"Net Lots", LVCFMT_RIGHT,cx);
   m_Summary.InsertColumn(2,"Profit",   LVCFMT_RIGHT,cx);
   m_Summary.InsertColumn(3,"Uncovered",LVCFMT_RIGHT,cx);
//---
   return(TRUE);
  }
//+------------------------------------------------------------------+
//|                                                                  |
//+------------------------------------------------------------------+
void CPageSummary::OnDestroy()
  {
   if(m_summary!=NULL) { ExtManagerPump->MemFree(m_summary); m_summary=NULL; m_summary_total=0; }
   CPropertyPage::OnDestroy();
  }
//+------------------------------------------------------------------+
//|                                                                  |
//+------------------------------------------------------------------+
LRESULT CPageSummary::OnPumpingMsg(WPARAM wParam,LPARAM)
  {
//---
   switch(wParam)
     {
      case PUMP_UPDATE_SYMBOLS:
         UpdateSymbols();
         break;
      case PUMP_UPDATE_BIDASK:
      case PUMP_UPDATE_TRADES:
         m_Summary.Invalidate();
         break;
     }
//---
   return(0);
  }
//+------------------------------------------------------------------+
//|                                                                  |
//+------------------------------------------------------------------+
void CPageSummary::UpdateSymbols()
  {
   if(m_summary!=NULL) ExtManagerPump->MemFree(m_summary);
   m_summary=ExtManagerPump->SummaryGetAll(&m_summary_total);
   m_Summary.SetItemCount(m_summary_total);
  }
//+------------------------------------------------------------------+
//|                                                                  |
//+------------------------------------------------------------------+
void CPageSummary::OnGetdispinfoSummary(NMHDR *pNMHDR, LRESULT* pResult)
  {
   LV_DISPINFO *pDisp=(LV_DISPINFO*)pNMHDR;
   *pResult=0;
//---
   if(pDisp->item.iItem<0 || pDisp->item.iItem>=m_summary_total)  return;
   SymbolSummary *smy=&m_summary[pDisp->item.iItem];
   if(ExtManagerPump->SummaryGetByCount(smy->count,smy)!=RET_OK)  return;
   char tmp[256]="";
//---
   if(pDisp->item.mask&LVIF_TEXT)
     {
      switch(pDisp->item.iSubItem)
        {
         case 0: COPY_STR(tmp,smy->symbol); break;
         case 1:
            _snprintf(tmp,sizeof(tmp)-1,"%.02lf",(smy->buylots-smy->covbuylots-(smy->selllots-smy->covselllots))/100.0);
            break;
         case 2:
            _snprintf(tmp,sizeof(tmp)-1,"%.0lf",smy->profit);
            break;
         case 3:
            _snprintf(tmp,sizeof(tmp)-1,"%.0lf",smy->profit-smy->covprofit);
            break;
         default: break;
        }
      pDisp->item.pszText=tmp;
     }
//---
  }
//+------------------------------------------------------------------+
//|                                                                  |
//+------------------------------------------------------------------+
