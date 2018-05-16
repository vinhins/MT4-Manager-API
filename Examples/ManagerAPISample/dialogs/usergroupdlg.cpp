//+------------------------------------------------------------------+
//|                                  MetaTrader 4 Manager API Sample |
//|                   Copyright 2001-2014, MetaQuotes Software Corp. |
//|                                        http://www.metaquotes.net |
//+------------------------------------------------------------------+
#include "stdafx.h"
#include "..\ManagerAPISample.h"
#include "usergroupdlg.h"

//+------------------------------------------------------------------+
//|                                                                  |
//+------------------------------------------------------------------+
CUserGroupDlg::CUserGroupDlg(const GroupCommandInfo *info,int *logins,CWnd *pParent) : CDialog(CUserGroupDlg::IDD, pParent)
  {
   //{{AFX_DATA_INIT(CUserGroupDlg)
   //}}AFX_DATA_INIT
   if(info!=NULL) memcpy(&m_info,info,sizeof(m_info));
   else           memset(&m_info,0,sizeof(m_info));
   m_logins=logins;
  }
//+------------------------------------------------------------------+
//|                                                                  |
//+------------------------------------------------------------------+
void CUserGroupDlg::DoDataExchange(CDataExchange* pDX)
  {
   CDialog::DoDataExchange(pDX);
   //{{AFX_DATA_MAP(CUserGroupDlg)
   DDX_Control(pDX, IDC_LOGINS, m_Logins);
   DDX_Control(pDX, IDC_LEVERAGE, m_Leverage);
   DDX_Control(pDX, IDC_GROUP, m_Group);
   //}}AFX_DATA_MAP
  }
//+------------------------------------------------------------------+
//|                                                                  |
//+------------------------------------------------------------------+
BEGIN_MESSAGE_MAP(CUserGroupDlg, CDialog)
   //{{AFX_MSG_MAP(CUserGroupDlg)
   ON_BN_CLICKED(IDC_DELETE, OnDelete)
   ON_BN_CLICKED(IDC_DISABLE, OnDisable)
   ON_BN_CLICKED(IDC_ENABLE, OnEnable)
   ON_BN_CLICKED(IDC_SETGROUP, OnSetgroup)
   ON_BN_CLICKED(IDC_SETLEVERAGE, OnSetleverage)
   //}}AFX_MSG_MAP
END_MESSAGE_MAP()
//+------------------------------------------------------------------+
//|                                                                  |
//+------------------------------------------------------------------+
BOOL CUserGroupDlg::OnInitDialog()
  {
   ConGroup *groups=NULL;
   int       total =0,i;
   CRect     rc;
   CString   str;
//---
   CDialog::OnInitDialog();
//---
   if(m_info.len<=0 || m_logins==NULL) { EndDialog(IDCANCEL); return(FALSE); }
//---
   groups=ExtManager->GroupsRequest(&total);
   for(i=0; i<total; i++) m_Group.AddString(groups[i].group);
   if(groups!=NULL) { ExtManager->MemFree(groups); groups=NULL; total=0; }
   m_Group.SetCurSel(0);
   m_Leverage.SetCurSel(1);
//---
   m_Logins.SetExtendedStyle(LVS_EX_FULLROWSELECT);
   m_Logins.GetClientRect(&rc);
   m_Logins.InsertColumn(0,NULL,LVCFMT_CENTER,rc.Width());
   for(i=0; i<m_info.len; i++) { str.Format("%d",m_logins[i]); m_Logins.InsertItem(i,str); }
//---
   return(TRUE);
  }
//+------------------------------------------------------------------+
//|                                                                  |
//+------------------------------------------------------------------+
void CUserGroupDlg::GroupOp(int command)
  {
//---
   m_info.command=command;
   if(command==GROUP_SETGROUP) m_Group.GetWindowText(m_info.newgroup,sizeof(m_info.newgroup)-1);
   else if(command==GROUP_LEVERAGE)
        {
         CString str;
         m_Leverage.GetWindowText(str);
         m_info.leverage=atoi(((LPCSTR)str)+4);
        }
//---
   int res=ExtManager->UsersGroupOp(&m_info,m_logins);
   MessageBox(ExtManager->ErrorDescription(res),"UsersGroupOp");
//---
   if(res==RET_OK) EndDialog(IDOK);
  }
//+------------------------------------------------------------------+
//|                                                                  |
//+------------------------------------------------------------------+
void CUserGroupDlg::OnDelete()      { GroupOp(GROUP_DELETE);   }
//+------------------------------------------------------------------+
//|                                                                  |
//+------------------------------------------------------------------+
void CUserGroupDlg::OnDisable()     { GroupOp(GROUP_DISABLE);  }
//+------------------------------------------------------------------+
//|                                                                  |
//+------------------------------------------------------------------+
void CUserGroupDlg::OnEnable()      { GroupOp(GROUP_ENABLE);   }
//+------------------------------------------------------------------+
//|                                                                  |
//+------------------------------------------------------------------+
void CUserGroupDlg::OnSetgroup()    { GroupOp(GROUP_SETGROUP); }
//+------------------------------------------------------------------+
//|                                                                  |
//+------------------------------------------------------------------+
void CUserGroupDlg::OnSetleverage() { GroupOp(GROUP_LEVERAGE); }
//+------------------------------------------------------------------+
//|                                                                  |
//+------------------------------------------------------------------+
