//+------------------------------------------------------------------+
//|                                  MetaTrader 4 Manager API Sample |
//|                   Copyright 2001-2014, MetaQuotes Software Corp. |
//|                                        http://www.metaquotes.net |
//+------------------------------------------------------------------+
#include "stdafx.h"
#include "BalanceManager.h"
#include "Settings.h"

//+------------------------------------------------------------------+
//| Settings dialog                                                  |
//+------------------------------------------------------------------+
Settings::Settings(CWnd *pParent) : CDialog(Settings::IDD, pParent)
  {
   //{{AFX_DATA_INIT(Settings)
   //}}AFX_DATA_INIT
  }
//+------------------------------------------------------------------+
//|                                                                  |
//+------------------------------------------------------------------+
void Settings::DoDataExchange(CDataExchange* pDX)
  {
   CDialog::DoDataExchange(pDX);
   //{{AFX_DATA_MAP(Settings)
   DDX_Control(pDX, IDC_LOGIN, m_login);
   DDX_Control(pDX, IDC_PASSWORD, m_password);
   DDX_Control(pDX, IDC_SERVER, m_server);
   //}}AFX_DATA_MAP
  }
//+------------------------------------------------------------------+
//|                                                                  |
//+------------------------------------------------------------------+
BEGIN_MESSAGE_MAP(Settings, CDialog)
   //{{AFX_MSG_MAP(Settings)
   ON_WM_SHOWWINDOW()
   ON_WM_PAINT()
   //}}AFX_MSG_MAP
END_MESSAGE_MAP()
//+------------------------------------------------------------------+
//| Save settings to global variables                                |
//+------------------------------------------------------------------+
void Settings::OnOK()
  {
   m_server.GetWindowText(ExtSrv,sizeof(ExtSrv)-1);
   ExtLgn=GetDlgItemInt(m_login.GetDlgCtrlID(),NULL,FALSE);
   m_password.GetWindowText(ExtPwd,sizeof(ExtPwd)-1);
   CDialog::OnOK();
  }
//+------------------------------------------------------------------+
//| Get settings from global variables                               |
//+------------------------------------------------------------------+
void Settings::OnPaint()
  {
   CPaintDC dc(this); // device context for painting
//---
   SetDlgItemText(IDC_SERVER,ExtSrv);
   if(ExtLgn) SetDlgItemInt(IDC_LOGIN,ExtLgn,FALSE);
   SetDlgItemText(IDC_PASSWORD,ExtPwd);
  }
//+------------------------------------------------------------------+
