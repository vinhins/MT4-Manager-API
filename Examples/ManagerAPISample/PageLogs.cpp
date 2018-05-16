//+------------------------------------------------------------------+
//|                                  MetaTrader 4 Manager API Sample |
//|                   Copyright 2001-2014, MetaQuotes Software Corp. |
//|                                        http://www.metaquotes.net |
//+------------------------------------------------------------------+
#include "stdafx.h"
#include "ManagerAPISample.h"
#include "PageLogs.h"

//+------------------------------------------------------------------+
//|                                                                  |
//+------------------------------------------------------------------+
IMPLEMENT_DYNCREATE(CPageLogs, CPropertyPageEx)
//+------------------------------------------------------------------+
//|                                                                  |
//+------------------------------------------------------------------+
CPageLogs::CPageLogs() : CPropertyPageEx(CPageLogs::IDD)
  {
   //{{AFX_DATA_INIT(CPageLogs)
   //}}AFX_DATA_INIT
   m_psp.dwFlags&=~PSP_HASHELP;
  }
//+------------------------------------------------------------------+
//|                                                                  |
//+------------------------------------------------------------------+
CPageLogs::~CPageLogs()
  {
  }
//+------------------------------------------------------------------+
//|                                                                  |
//+------------------------------------------------------------------+
void CPageLogs::DoDataExchange(CDataExchange* pDX)
  {
   CPropertyPageEx::DoDataExchange(pDX);
   //{{AFX_DATA_MAP(CPageLogs)
   DDX_Control(pDX, IDC_LOGS, m_Logs);
   //}}AFX_DATA_MAP
  }
//+------------------------------------------------------------------+
//|                                                                  |
//+------------------------------------------------------------------+
BEGIN_MESSAGE_MAP(CPageLogs, CPropertyPageEx)
   //{{AFX_MSG_MAP(CPageLogs)
   //}}AFX_MSG_MAP
END_MESSAGE_MAP()
//+------------------------------------------------------------------+
//|                                                                  |
//+------------------------------------------------------------------+
BOOL CPageLogs::OnInitDialog()
  {
   CRect rc;
   int   cx=0;
//---
   CPropertyPageEx::OnInitDialog();
//---
   m_Logs.GetClientRect(&rc); cx=(rc.Width()-::GetSystemMetrics(SM_CXVSCROLL)-4)/4;
   m_Logs.SetExtendedStyle(LVS_EX_FULLROWSELECT);
   m_Logs.InsertColumn(0,"Time",   LVCFMT_LEFT,cx);
   m_Logs.InsertColumn(1,"Message",LVCFMT_LEFT,cx*3);
//---
   return(TRUE);
  }
//+------------------------------------------------------------------+
//|                                                                  |
//+------------------------------------------------------------------+
void CPageLogs::LogOut(LPCSTR str)
  {
   char   tmp[256]="";
   time_t ctm=time(NULL);
   tm    *ptm=localtime(&ctm);
//---
   if(GetSafeHwnd()==NULL) return;
//---
   if(ptm!=NULL) _snprintf(tmp,sizeof(tmp)-1,"%.04d.%.02d.%.02d %.02d:%.02d:%.02d",
                           ptm->tm_yday+1900,ptm->tm_mon+1,ptm->tm_mday,ptm->tm_hour,ptm->tm_min,ptm->tm_sec);
   m_Logs.InsertItem(0,tmp);
   m_Logs.SetItemText(0,1,str);
//---
  }
//+------------------------------------------------------------------+
//|                                                                  |
//+------------------------------------------------------------------+
