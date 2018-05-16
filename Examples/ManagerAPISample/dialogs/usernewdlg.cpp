//+------------------------------------------------------------------+
//|                                  MetaTrader 4 Manager API Sample |
//|                   Copyright 2001-2014, MetaQuotes Software Corp. |
//|                                        http://www.metaquotes.net |
//+------------------------------------------------------------------+
#include "stdafx.h"
#include "..\ManagerAPISample.h"
#include "usernewdlg.h"

//+------------------------------------------------------------------+
//|                                                                  |
//+------------------------------------------------------------------+
CUserNewDlg::CUserNewDlg(CWnd *pParent) : CDialog(CUserNewDlg::IDD, pParent)
  {
   //{{AFX_DATA_INIT(CUserNewDlg)
   //}}AFX_DATA_INIT
  }
//+------------------------------------------------------------------+
//|                                                                  |
//+------------------------------------------------------------------+
void CUserNewDlg::DoDataExchange(CDataExchange* pDX)
  {
   CDialog::DoDataExchange(pDX);
   //{{AFX_DATA_MAP(CUserNewDlg)
   DDX_Control(pDX, IDC_PASSWORD, m_Password);
   DDX_Control(pDX, IDC_NAME, m_Name);
   DDX_Control(pDX, IDC_LOGIN, m_Login);
   DDX_Control(pDX, IDC_GROUP, m_Group);
   DDX_Control(pDX, IDC_EMAIL, m_Email);
   //}}AFX_DATA_MAP
  }
//+------------------------------------------------------------------+
//|                                                                  |
//+------------------------------------------------------------------+
BEGIN_MESSAGE_MAP(CUserNewDlg, CDialog)
   //{{AFX_MSG_MAP(CUserNewDlg)
   //}}AFX_MSG_MAP
END_MESSAGE_MAP()
//+------------------------------------------------------------------+
//|                                                                  |
//+------------------------------------------------------------------+
BOOL CUserNewDlg::OnInitDialog()
  {
   ConGroup *groups=NULL;
   int       total =0;
//---
   CDialog::OnInitDialog();
//---
   groups=ExtManager->GroupsRequest(&total);
   for(int i=0; i<total; i++) m_Group.AddString(groups[i].group);
   if(groups!=NULL) { ExtManager->MemFree(groups); groups=NULL; total=0; }
//---
   m_Login.SetWindowText("next");
   m_Password.SetWindowText("NewUser");
   m_Group.SetCurSel(0);
//---
   return(TRUE);
  }
//+------------------------------------------------------------------+
//|                                                                  |
//+------------------------------------------------------------------+
void CUserNewDlg::OnOK()
  {
   int        res =RET_ERROR;
   UserRecord user={0};
   CString    str;
//---
   user.login=GetDlgItemInt(m_Login.GetDlgCtrlID(),NULL,FALSE);
   m_Password.GetWindowText(user.password,sizeof(user.password)-1);
   m_Name.GetWindowText(user.name,sizeof(user.name)-1);
   m_Group.GetWindowText(user.group,sizeof(user.group)-1);
   m_Email.GetWindowText(user.email,sizeof(user.email)-1);
   user.leverage    =100;
   user.enable      =TRUE;
   user.send_reports=TRUE;
   user.user_color  =USER_COLOR_NONE;
//---
   if(user.name[0]==0) { ::MessageBeep(-1); m_Name.SetFocus(); return; }
   res=ExtManager->UserRecordNew(&user);
   if(res!=RET_OK) { MessageBox(ExtManager->ErrorDescription(res),"UserRecordNew"); return; }
   str.Format("News user: '%d' ('%s')",user.login,user.name);
   MessageBox(str,"UserRecordNew");
//---
   CDialog::OnOK();
  }
//+------------------------------------------------------------------+
//|                                                                  |
//+------------------------------------------------------------------+
