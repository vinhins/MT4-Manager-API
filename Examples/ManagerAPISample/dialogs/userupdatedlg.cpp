//+------------------------------------------------------------------+
//|                                  MetaTrader 4 Manager API Sample |
//|                   Copyright 2001-2014, MetaQuotes Software Corp. |
//|                                        http://www.metaquotes.net |
//+------------------------------------------------------------------+
#include "stdafx.h"
#include "..\ManagerAPISample.h"
#include "userupdatedlg.h"

//+------------------------------------------------------------------+
//|                                                                  |
//+------------------------------------------------------------------+
CUserUpdateDlg::CUserUpdateDlg(const UserRecord *user,CWnd *pParent) : CDialog(CUserUpdateDlg::IDD, pParent)
  {
   //{{AFX_DATA_INIT(CUserUpdateDlg)
   //}}AFX_DATA_INIT
   if(user!=NULL) memcpy(&m_user,user,sizeof(m_user));
   else           memset(&m_user,0,sizeof(m_user));
  }
//+------------------------------------------------------------------+
//|                                                                  |
//+------------------------------------------------------------------+
void CUserUpdateDlg::DoDataExchange(CDataExchange* pDX)
  {
   CDialog::DoDataExchange(pDX);
   //{{AFX_DATA_MAP(CUserUpdateDlg)
   DDX_Control(pDX, IDC_NAME, m_Name);
   DDX_Control(pDX, IDC_LOGIN, m_Login);
   DDX_Control(pDX, IDC_GROUP, m_Group);
   DDX_Control(pDX, IDC_EMAIL, m_Email);
   //}}AFX_DATA_MAP
  }
//+------------------------------------------------------------------+
//|                                                                  |
//+------------------------------------------------------------------+
BEGIN_MESSAGE_MAP(CUserUpdateDlg, CDialog)
   //{{AFX_MSG_MAP(CUserUpdateDlg)
   //}}AFX_MSG_MAP
END_MESSAGE_MAP()
//+------------------------------------------------------------------+
//|                                                                  |
//+------------------------------------------------------------------+
BOOL CUserUpdateDlg::OnInitDialog()
  {
   ConGroup *groups=NULL;
   int       total =0;
//---
   CDialog::OnInitDialog();
//---
   if(m_user.login==0) { EndDialog(IDCANCEL); return(FALSE); }
//---
   groups=ExtManager->GroupsRequest(&total);
   for(int i=0; i<total; i++) m_Group.AddString(groups[i].group);
   if(groups!=NULL) { ExtManager->MemFree(groups); groups=NULL; total=0; }
//---
   SetDlgItemInt(m_Login.GetDlgCtrlID(),m_user.login);
   m_Name.SetWindowText(m_user.name);
   m_Group.SelectString(-1,m_user.group);
   m_Email.SetWindowText(m_user.email);
//---
   return(TRUE);
  }
//+------------------------------------------------------------------+
//|                                                                  |
//+------------------------------------------------------------------+
void CUserUpdateDlg::OnOK()
  {
   int res=RET_ERROR;
//---
   m_Name.GetWindowText(m_user.name,sizeof(m_user.name)-1);
   m_Group.GetWindowText(m_user.group,sizeof(m_user.group)-1);
   m_Email.GetWindowText(m_user.email,sizeof(m_user.email)-1);
//---
   res=ExtManager->UserRecordUpdate(&m_user);
   MessageBox(ExtManager->ErrorDescription(res),"UserRecordUpdate");
//---
   if(res==RET_OK) CDialog::OnOK();
  }
//+------------------------------------------------------------------+
//|                                                                  |
//+------------------------------------------------------------------+
