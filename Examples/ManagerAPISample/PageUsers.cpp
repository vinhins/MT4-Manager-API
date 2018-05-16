//+------------------------------------------------------------------+
//|                                  MetaTrader 4 Manager API Sample |
//|                   Copyright 2001-2014, MetaQuotes Software Corp. |
//|                                        http://www.metaquotes.net |
//+------------------------------------------------------------------+
#include "stdafx.h"
#include "ManagerAPISample.h"
#include "PageUsers.h"
#include "dialogs\RequestDlg.h"
#include "dialogs\UserUpdateDlg.h"
#include "dialogs\UserNewDlg.h"
#include "dialogs\UserGroupDlg.h"
#include "dialogs\UserBalanceDlg.h"

//+------------------------------------------------------------------+
//|                                                                  |
//+------------------------------------------------------------------+
IMPLEMENT_DYNCREATE(CPageUsers, CPropertyPageEx)
//+------------------------------------------------------------------+
//|                                                                  |
//+------------------------------------------------------------------+
CPageUsers::CPageUsers() : CPropertyPageEx(CPageUsers::IDD),
   m_users(NULL),m_users_total(0)
  {
   //{{AFX_DATA_INIT(CPageUsers)
   //}}AFX_DATA_INIT
   m_psp.dwFlags&=~PSP_HASHELP;
  }
//+------------------------------------------------------------------+
//|                                                                  |
//+------------------------------------------------------------------+
CPageUsers::~CPageUsers()
  {
  }
//+------------------------------------------------------------------+
//|                                                                  |
//+------------------------------------------------------------------+
void CPageUsers::DoDataExchange(CDataExchange* pDX)
  {
   CPropertyPageEx::DoDataExchange(pDX);
   //{{AFX_DATA_MAP(CPageUsers)
   DDX_Control(pDX, IDC_USERS, m_Users);
   //}}AFX_DATA_MAP
  }
//+------------------------------------------------------------------+
//|                                                                  |
//+------------------------------------------------------------------+
BEGIN_MESSAGE_MAP(CPageUsers, CPropertyPageEx)
   //{{AFX_MSG_MAP(CPageUsers)
   ON_WM_DESTROY()
   ON_BN_CLICKED(IDC_REQUEST, OnRequest)
   ON_NOTIFY(LVN_GETDISPINFO, IDC_USERS, OnGetdispinfoUsers)
   ON_BN_CLICKED(IDC_NEW, OnNew)
   ON_BN_CLICKED(IDC_UPDATE, OnUpdate)
   ON_NOTIFY(NM_DBLCLK, IDC_USERS, OnDblclkUsers)
   ON_BN_CLICKED(IDC_GROUPOP, OnGroupop)
   ON_BN_CLICKED(IDC_BALANCE, OnBalance)
   ON_BN_CLICKED(IDC_USERS_GET, OnUsersGet)
   ON_BN_CLICKED(IDC_MARGIN, OnMargin)
   //}}AFX_MSG_MAP
   ON_REGISTERED_MESSAGE(ExtPumpingMsg, OnPumpingMsg)
END_MESSAGE_MAP()
//+------------------------------------------------------------------+
//|                                                                  |
//+------------------------------------------------------------------+
BOOL CPageUsers::OnInitDialog()
  {
   CRect rc;
   int   cx=0;
//---
   CPropertyPageEx::OnInitDialog();
//---
   m_Users.SetExtendedStyle(LVS_EX_FULLROWSELECT);
   m_Users.GetWindowRect(&rc);
   cx=(rc.Width()-::GetSystemMetrics(SM_CXVSCROLL)-::GetSystemMetrics(SM_CXBORDER)*4)/5;
   m_Users.InsertColumn(0,"Login",   LVCFMT_LEFT,cx);
   m_Users.InsertColumn(1,"Name",    LVCFMT_LEFT,cx);
   m_Users.InsertColumn(2,"Group",   LVCFMT_LEFT,cx);
   m_Users.InsertColumn(3,"Leverage",LVCFMT_LEFT,cx);
   m_Users.InsertColumn(4,"Balance", LVCFMT_RIGHT,cx);
//---
   return(TRUE);
  }
//+------------------------------------------------------------------+
//|                                                                  |
//+------------------------------------------------------------------+
void CPageUsers::OnDestroy()
  {
//---
   if(m_users!=NULL) { ExtManager->MemFree(m_users); m_users=NULL; m_users_total=0; }
//---
   CPropertyPageEx::OnDestroy();
  }
//+------------------------------------------------------------------+
//|                                                                  |
//+------------------------------------------------------------------+
LRESULT CPageUsers::OnPumpingMsg(WPARAM wParam,LPARAM)
  {
   if(wParam==PUMP_UPDATE_USERS) OnUsersGet();
   return(0);
  }
//+------------------------------------------------------------------+
//|                                                                  |
//+------------------------------------------------------------------+
void CPageUsers::OnRequest()
  {
   int login=0;
//---
   CRequestDlg dlg;
   if(dlg.DoModal()!=IDOK) return;
   login=dlg.GetInt();
//---
   m_Users.SetItemCount(0);
//---
   AfxGetApp()->BeginWaitCursor();
   if(m_users!=NULL) { ExtManager->MemFree(m_users); m_users=NULL; m_users_total=0; }
   if(login==0)   m_users=ExtManager->UsersRequest(&m_users_total);
   else         { m_users_total=1; m_users=ExtManager->UserRecordsRequest(&login,&m_users_total); }
   AfxGetApp()->EndWaitCursor();
//---
   m_Users.SetItemCount(m_users_total);
  }
//+------------------------------------------------------------------+
//|                                                                  |
//+------------------------------------------------------------------+
void CPageUsers::OnUsersGet()
  {
//---
   if(m_users!=NULL) { ExtManager->MemFree(m_users); m_users=NULL; m_users_total=0; }
   m_users=ExtManagerPump->UsersGet(&m_users_total);
//---
   m_Users.SetItemCount(m_users_total);
  }
//+------------------------------------------------------------------+
//|                                                                  |
//+------------------------------------------------------------------+
void CPageUsers::OnGetdispinfoUsers(NMHDR *pNMHDR,LRESULT *pResult)
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
         case 1: COPY_STR(tmp,m_users[i].name);  break;
         case 2: COPY_STR(tmp,m_users[i].group); break;
         case 3: if(m_users[i].leverage>0) _snprintf(tmp,sizeof(tmp)-1,"1 : %d",m_users[i].leverage); break;
         case 4: _snprintf(tmp,sizeof(tmp)-1,"%.02lf",m_users[i].balance); break;
         default: break;
        }
      pDI->item.pszText=tmp;
     }
//---
  }
//+------------------------------------------------------------------+
//|                                                                  |
//+------------------------------------------------------------------+
void CPageUsers::OnNew()
  {
   CUserNewDlg dlg;
   dlg.DoModal();
  }
//+------------------------------------------------------------------+
//|                                                                  |
//+------------------------------------------------------------------+
void CPageUsers::OnUpdate()
  {
   POSITION pos=m_Users.GetFirstSelectedItemPosition();
   int      i=-1;
//---
   if(pos==NULL || (i=m_Users.GetNextSelectedItem(pos))<0 || i>=m_users_total)
     {
      MessageBox("Select user","Update user");
      return;
     }
//---
   CUserUpdateDlg dlg(&m_users[i]);
   dlg.DoModal();
  }
//+------------------------------------------------------------------+
//|                                                                  |
//+------------------------------------------------------------------+
void CPageUsers::OnDblclkUsers(NMHDR *pNMHDR,LRESULT *pResult)
  {
   if(pResult!=NULL) *pResult=0;
   OnUpdate();
  }
//+------------------------------------------------------------------+
//|                                                                  |
//+------------------------------------------------------------------+
void CPageUsers::OnGroupop()
  {
   GroupCommandInfo info={0};
   int i,count=0,*logins=NULL;
//---
   if((count=m_Users.GetSelectedCount())<=0) { MessageBox("Select users", "UsersGroupOp"); return; }
   if((logins=new int[count])==NULL)         { MessageBox("Out of memory","UsersGroupOp"); return; }
//---
   for(i=m_Users.GetNextItem(-1,LVNI_SELECTED); i>=0 && i<m_users_total && info.len<=count;
       i=m_Users.GetNextItem(i,LVNI_SELECTED)) logins[info.len++]=m_users[i].login;
//---
   CUserGroupDlg dlg(&info,logins);
   dlg.DoModal();
//---
   delete[] logins; logins=NULL;
  }
//+------------------------------------------------------------------+
//|                                                                  |
//+------------------------------------------------------------------+
void CPageUsers::OnBalance()
  {
   POSITION pos=m_Users.GetFirstSelectedItemPosition();
   int      login=0,i=-1;
//---
   if(pos!=NULL && (i=m_Users.GetNextSelectedItem(pos))>=0 && i<m_users_total)
      login=m_users[i].login;
//---
   CUserBalanceDlg dlg(login);
   dlg.DoModal();
//---
  }
//+------------------------------------------------------------------+
//|                                                                  |
//+------------------------------------------------------------------+
void CPageUsers::OnMargin()
  {
   POSITION    pos  =m_Users.GetFirstSelectedItemPosition();
   int         res  =RET_ERROR,i=-1;
   MarginLevel level={0};
   char        tmp[256]="";
//---
   if(pos==NULL || (i=m_Users.GetNextSelectedItem(pos))<0 || i>=m_users_total) return;
   res=ExtManagerPump->MarginLevelGet(m_users[i].login,m_users[i].group,&level);
   if(res!=RET_OK) MessageBox("No margin requirements");
   else
     {
      _snprintf(tmp,sizeof(tmp)-1,"%d, %s\n%.02lf\n%.02lf\n%.02lf",
                level.login,level.group,level.margin,level.margin_free,level.margin_level);
      MessageBox(tmp);
     }
//---
  }
//+------------------------------------------------------------------+
//|                                                                  |
//+------------------------------------------------------------------+
