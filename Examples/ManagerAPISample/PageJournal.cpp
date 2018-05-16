//+------------------------------------------------------------------+
//|                                  MetaTrader 4 Manager API Sample |
//|                   Copyright 2001-2014, MetaQuotes Software Corp. |
//|                                        http://www.metaquotes.net |
//+------------------------------------------------------------------+
#include "stdafx.h"
#include "ManagerAPISample.h"
#include "PageJournal.h"

//+------------------------------------------------------------------+
//|                                                                  |
//+------------------------------------------------------------------+
IMPLEMENT_DYNCREATE(CPageJournal, CPropertyPageEx)
//+------------------------------------------------------------------+
//|                                                                  |
//+------------------------------------------------------------------+
CPageJournal::CPageJournal() : CPropertyPageEx(CPageJournal::IDD),
   m_logs(NULL),m_logs_total(0)
  {
   //{{AFX_DATA_INIT(CPageJournal)
   //}}AFX_DATA_INIT
   m_psp.dwFlags&=~PSP_HASHELP;
  }
//+------------------------------------------------------------------+
//|                                                                  |
//+------------------------------------------------------------------+
CPageJournal::~CPageJournal()
  {
  }
//+------------------------------------------------------------------+
//|                                                                  |
//+------------------------------------------------------------------+
void CPageJournal::DoDataExchange(CDataExchange* pDX)
  {
   CPropertyPageEx::DoDataExchange(pDX);
   //{{AFX_DATA_MAP(CPageJournal)
   DDX_Control(pDX, IDC_JOURNAL, m_Journal);
   DDX_Control(pDX, IDC_TO, m_To);
   DDX_Control(pDX, IDC_MODE, m_Mode);
   DDX_Control(pDX, IDC_FROM, m_From);
   //}}AFX_DATA_MAP
  }
//+------------------------------------------------------------------+
//|                                                                  |
//+------------------------------------------------------------------+
BEGIN_MESSAGE_MAP(CPageJournal, CPropertyPageEx)
   //{{AFX_MSG_MAP(CPageJournal)
   ON_WM_DESTROY()
   ON_BN_CLICKED(IDC_REQUEST, OnRequest)
   ON_NOTIFY(LVN_GETDISPINFO, IDC_JOURNAL, OnGetdispinfoJournal)
   //}}AFX_MSG_MAP
END_MESSAGE_MAP()
//+------------------------------------------------------------------+
//|                                                                  |
//+------------------------------------------------------------------+
BOOL CPageJournal::OnInitDialog()
  {
   CRect rc;
   int   cx=0;
//---
   CPropertyPage::OnInitDialog();
//---
   m_Mode.SetCurSel(0);
   m_Journal.GetClientRect(&rc); cx=(rc.Width()-::GetSystemMetrics(SM_CXVSCROLL))/4;
   m_Journal.SetExtendedStyle(LVS_EX_FULLROWSELECT);
   m_Journal.InsertColumn(0,"Time",   LVCFMT_LEFT,cx);
   m_Journal.InsertColumn(1,"IP",     LVCFMT_LEFT,cx);
   m_Journal.InsertColumn(2,"Message",LVCFMT_LEFT,cx*2);
//---
   return(TRUE);
  }
//+------------------------------------------------------------------+
//|                                                                  |
//+------------------------------------------------------------------+
void CPageJournal::OnDestroy()
  {
//---
   if(m_logs!=NULL)
     {
      ExtManager->MemFree(m_logs);
      m_logs=NULL;
      m_logs_total=0;
     }
//---
   CPropertyPage::OnDestroy();
  }
//+------------------------------------------------------------------+
//|                                                                  |
//+------------------------------------------------------------------+
void CPageJournal::OnRequest()
  {
   int    mode=0;
   time_t from=0,to=0;
   CTime  ct;
//---
   mode=m_Mode.GetCurSel();
   m_From.GetTime(ct);
   from=(__time32_t)ct.GetTime()-_timezone;
   from/=86400;
   from*=86400;
   m_To.GetTime(ct);
   to=(__time32_t)ct.GetTime()-_timezone;
   to/=86400;
   to*=86400;
   to+=86400;
//---
   m_Journal.SetItemCount(0);
//---
   AfxGetApp()->BeginWaitCursor();
   if(m_logs!=NULL)
     {
      ExtManager->MemFree(m_logs);
      m_logs=NULL;
      m_logs_total=0;
     }
   m_logs=ExtManager->JournalRequest(mode,from,to,"",&m_logs_total);
   AfxGetApp()->EndWaitCursor();
//---
   m_Journal.SetItemCount(m_logs_total);
//---
  }
//+------------------------------------------------------------------+
//|                                                                  |
//+------------------------------------------------------------------+
void CPageJournal::OnGetdispinfoJournal(NMHDR *pNMHDR,LRESULT *pResult)
  {
   LV_DISPINFO* pDI=(LV_DISPINFO*)pNMHDR;
   if(pResult!=NULL) *pResult=0;
//---
   char tmp[256]="";
   int  i=pDI->item.iItem;
   if(i<0 || i>=m_logs_total) return;
//---
   if(pDI->item.mask&LVIF_TEXT)
     {
      switch(pDI->item.iSubItem)
        {
         case 0: COPY_STR(tmp,m_logs[i].time);    break;
         case 1: COPY_STR(tmp,m_logs[i].ip);      break;
         case 2: COPY_STR(tmp,m_logs[i].message); break;
         default:
            break;
        }
      pDI->item.pszText=tmp;
     }
//---
  }
//+------------------------------------------------------------------+
//|                                                                  |
//+------------------------------------------------------------------+
