//+------------------------------------------------------------------+
//|                                  MetaTrader 4 Manager API Sample |
//|                   Copyright 2001-2014, MetaQuotes Software Corp. |
//|                                        http://www.metaquotes.net |
//+------------------------------------------------------------------+
#include "stdafx.h"
#include "ManagerAPISample.h"
#include "PageOnline.h"

//+------------------------------------------------------------------+
//|                                                                  |
//+------------------------------------------------------------------+
IMPLEMENT_DYNCREATE(CPageOnline, CPropertyPageEx)
//+------------------------------------------------------------------+
//|                                                                  |
//+------------------------------------------------------------------+
CPageOnline::CPageOnline() : CPropertyPageEx(CPageOnline::IDD),
   m_users(NULL),m_users_total(0)
  {
   //{{AFX_DATA_INIT(CPageOnline)
   //}}AFX_DATA_INIT
   m_psp.dwFlags&=~PSP_HASHELP;
  }
//+------------------------------------------------------------------+
//|                                                                  |
//+------------------------------------------------------------------+
CPageOnline::~CPageOnline()
  {
  }
//+------------------------------------------------------------------+
//|                                                                  |
//+------------------------------------------------------------------+
void CPageOnline::DoDataExchange(CDataExchange* pDX)
  {
   CPropertyPageEx::DoDataExchange(pDX);
   //{{AFX_DATA_MAP(CPageOnline)
   DDX_Control(pDX, IDC_USERS, m_Users);
   //}}AFX_DATA_MAP
  }
//+------------------------------------------------------------------+
//|                                                                  |
//+------------------------------------------------------------------+
BEGIN_MESSAGE_MAP(CPageOnline, CPropertyPageEx)
   //{{AFX_MSG_MAP(CPageOnline)
   ON_WM_DESTROY()
   ON_BN_CLICKED(IDC_REQUEST, OnRequest)
   ON_NOTIFY(LVN_GETDISPINFO, IDC_USERS, OnGetdispinfoUsers)
   ON_BN_CLICKED(IDC_ONLINE_GET, OnOnlineGet)
   //}}AFX_MSG_MAP
   ON_REGISTERED_MESSAGE(ExtPumpingMsg, OnPumpingMsg)
END_MESSAGE_MAP()
//+------------------------------------------------------------------+
//|                                                                  |
//+------------------------------------------------------------------+
BOOL CPageOnline::OnInitDialog()
  {
   CRect rc;
   int   cx;
//---
   CPropertyPageEx::OnInitDialog();
//---
   m_Users.SetExtendedStyle(LVS_EX_FULLROWSELECT);
   m_Users.GetClientRect(&rc);
   cx=(rc.Width()-::GetSystemMetrics(SM_CXVSCROLL)-::GetSystemMetrics(SM_CXBORDER)*4)/3;
   m_Users.InsertColumn(0,"Login",LVCFMT_LEFT,cx);
   m_Users.InsertColumn(1,"Group",LVCFMT_LEFT,cx);
   m_Users.InsertColumn(2,"IP",LVCFMT_LEFT,cx);
//---
   return(TRUE);
  }
//+------------------------------------------------------------------+
//|                                                                  |
//+------------------------------------------------------------------+
void CPageOnline::OnDestroy()
  {
//---
   if(m_users!=NULL) { ExtManager->MemFree(m_users); m_users=NULL; m_users_total=0; }
//---
   CPropertyPageEx::OnDestroy();
  }
//+------------------------------------------------------------------+
//|                                                                  |
//+------------------------------------------------------------------+
LRESULT CPageOnline::OnPumpingMsg(WPARAM wParam,LPARAM)
  {
   if(wParam==PUMP_UPDATE_ONLINE) OnOnlineGet();
   return(0);
  }
//+------------------------------------------------------------------+
//|                                                                  |
//+------------------------------------------------------------------+
void CPageOnline::OnRequest()
  {
   m_Users.SetItemCount(0);
//---
   AfxGetApp()->BeginWaitCursor();
   if(m_users!=NULL) { ExtManager->MemFree(m_users); m_users=NULL; m_users_total=0; }
   m_users=ExtManager->OnlineRequest(&m_users_total);
   AfxGetApp()->EndWaitCursor();
//---
   m_Users.SetItemCount(m_users_total);
  }
//+------------------------------------------------------------------+
//|                                                                  |
//+------------------------------------------------------------------+
void CPageOnline::OnOnlineGet()
  {
//---
   if(m_users!=NULL) { ExtManager->MemFree(m_users); m_users=NULL; m_users_total=0; }
   m_users=ExtManagerPump->OnlineGet(&m_users_total);
//---
   m_Users.SetItemCount(m_users_total);
  }
//+------------------------------------------------------------------+
//|                                                                  |
//+------------------------------------------------------------------+
void CPageOnline::OnGetdispinfoUsers(NMHDR *pNMHDR,LRESULT *pResult)
  {
   LV_DISPINFO* pDI=(LV_DISPINFO*)pNMHDR;
   if(pResult!=NULL) *pResult=0;
//---
   char tmp[256]="";
   int  i=pDI->item.iItem;
   if(i<0 || i>=m_users_total) return;
//---
   if(pDI->item.mask&LVIF_TEXT)
     {
      switch(pDI->item.iSubItem)
        {
         case 0: _snprintf(tmp,sizeof(tmp)-1,"%d",m_users[i].login); break;
         case 1: COPY_STR(tmp,m_users[i].group); break;
         case 2:
            _snprintf(tmp,sizeof(tmp)-1,"%d.%d.%d.%d",
                      m_users[i].ip&255,(m_users[i].ip>>8)&255,(m_users[i].ip>>16)&255,m_users[i].ip>>24);
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
