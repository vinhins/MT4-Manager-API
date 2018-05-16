//+------------------------------------------------------------------+
//|                                  MetaTrader 4 Manager API Sample |
//|                   Copyright 2001-2014, MetaQuotes Software Corp. |
//|                                        http://www.metaquotes.net |
//+------------------------------------------------------------------+
#include "stdafx.h"
#include "ManagerAPISample.h"
#include "PageExposure.h"
//---
//+------------------------------------------------------------------+
//|                                                                  |
//+------------------------------------------------------------------+
IMPLEMENT_DYNCREATE(CPageExposure, CPropertyPageEx)
//+------------------------------------------------------------------+
//|                                                                  |
//+------------------------------------------------------------------+
CPageExposure::CPageExposure() : CPropertyPageEx(CPageExposure::IDD),
   m_exposure(NULL),m_exposure_total(0)
  {
   //{{AFX_DATA_INIT(CPageExposure)
   //}}AFX_DATA_INIT
   m_psp.dwFlags&=~PSP_HASHELP;
  }
//+------------------------------------------------------------------+
//|                                                                  |
//+------------------------------------------------------------------+
CPageExposure::~CPageExposure()
  {
  }
//+------------------------------------------------------------------+
//|                                                                  |
//+------------------------------------------------------------------+
void CPageExposure::DoDataExchange(CDataExchange* pDX)
  {
   CPropertyPageEx::DoDataExchange(pDX);
   //{{AFX_DATA_MAP(CPageExposure)
   DDX_Control(pDX, IDC_EXPOSURE, m_Exposure);
   //}}AFX_DATA_MAP
  }
//+------------------------------------------------------------------+
//|                                                                  |
//+------------------------------------------------------------------+
BEGIN_MESSAGE_MAP(CPageExposure, CPropertyPageEx)
   //{{AFX_MSG_MAP(CPageExposure)
   ON_WM_DESTROY()
   ON_NOTIFY(LVN_GETDISPINFO, IDC_EXPOSURE, OnGetdispinfoExposure)
   //}}AFX_MSG_MAP
   ON_REGISTERED_MESSAGE(ExtPumpingMsg, OnPumpingMsg)
END_MESSAGE_MAP()
//+------------------------------------------------------------------+
//|                                                                  |
//+------------------------------------------------------------------+
BOOL CPageExposure::OnInitDialog()
  {
   CRect rc;
   int   cx=0;
//---
   CPropertyPageEx::OnInitDialog();
//---
   m_Exposure.GetClientRect(&rc);
   cx=(rc.Width()-::GetSystemMetrics(SM_CXVSCROLL)-::GetSystemMetrics(SM_CXBORDER)*4)/4;
   m_Exposure.SetExtendedStyle(LVS_EX_FULLROWSELECT);
   m_Exposure.InsertColumn(0,"Currency", LVCFMT_LEFT, cx);
   m_Exposure.InsertColumn(1,"Clients",  LVCFMT_RIGHT,cx);
   m_Exposure.InsertColumn(2,"Coverage", LVCFMT_RIGHT,cx);
   m_Exposure.InsertColumn(3,"Net Total",LVCFMT_RIGHT,cx);
//---
   return(TRUE);
  }
//+------------------------------------------------------------------+
//|                                                                  |
//+------------------------------------------------------------------+
void CPageExposure::OnDestroy()
  {
   if(m_exposure!=NULL) { ExtManagerPump->MemFree(m_exposure); m_exposure=NULL; m_exposure_total=0; }
   CPropertyPage::OnDestroy();
  }
//+------------------------------------------------------------------+
//|                                                                  |
//+------------------------------------------------------------------+
LRESULT CPageExposure::OnPumpingMsg(WPARAM wParam,LPARAM)
  {
//---
   if(wParam==PUMP_UPDATE_TRADES)
     {
      if(m_exposure!=NULL) ExtManagerPump->MemFree(m_exposure);
      m_exposure=ExtManagerPump->ExposureGet(&m_exposure_total);
      m_Exposure.SetItemCount(m_exposure_total);
     }
//---
   return(0);
  }
//+------------------------------------------------------------------+
//|                                                                  |
//+------------------------------------------------------------------+
void CPageExposure::OnGetdispinfoExposure(NMHDR *pNMHDR, LRESULT* pResult)
  {
   LV_DISPINFO *pDisp=(LV_DISPINFO*)pNMHDR;
   *pResult=0;
//---
   if(pDisp->item.iItem<0 || pDisp->item.iItem>=m_exposure_total)  return;
   const ExposureValue &exposure=m_exposure[pDisp->item.iItem];
   char tmp[256]="";
//---
   if(pDisp->item.mask&LVIF_TEXT)
     {
      switch(pDisp->item.iSubItem)
        {
         case 0: COPY_STR(tmp,exposure.currency); break;
         case 1: _snprintf(tmp,sizeof(tmp)-1,"%.0lf",exposure.clients);  break;
         case 2: _snprintf(tmp,sizeof(tmp)-1,"%.0lf",exposure.coverage); break;
         case 3: _snprintf(tmp,sizeof(tmp)-1,"%.0lf",exposure.clients-exposure.coverage); break;
         default: break;
        }
      pDisp->item.pszText=tmp;
     }
//---
  }
//+------------------------------------------------------------------+
//|                                                                  |
//+------------------------------------------------------------------+
