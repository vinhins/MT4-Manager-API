//+------------------------------------------------------------------+
//|                                      MetaTrader Manager API Test |
//|                   Copyright 2001-2014, MetaQuotes Software Corp. |
//|                                        http://www.metaquotes.net |
//+------------------------------------------------------------------+
#include "stdafx.h"
#include "ManagerAPITest.h"
#include "NewPassDlg.h"

//+------------------------------------------------------------------+
//|                                                                  |
//+------------------------------------------------------------------+
CNewPassDlg::CNewPassDlg(CWnd *pParent/*=NULL*/) : CDialog(CNewPassDlg::IDD,pParent)
  {
   //{{AFX_DATA_INIT(CNewPassDlg)
   //}}AFX_DATA_INIT
   m_newpass[0]=0;
   m_investor  =FALSE;
  }
//+------------------------------------------------------------------+
//|                                                                  |
//+------------------------------------------------------------------+
void CNewPassDlg::DoDataExchange(CDataExchange* pDX)
  {
   CDialog::DoDataExchange(pDX);
   //{{AFX_DATA_MAP(CNewPassDlg)
   DDX_Control(pDX, IDC_NEWPASS, m_NewPass);
   DDX_Control(pDX, IDC_INVESTOR, m_Investor);
   DDX_Control(pDX, IDC_CONFIRM, m_Confirm);
   //}}AFX_DATA_MAP
  }
//+------------------------------------------------------------------+
//|                                                                  |
//+------------------------------------------------------------------+
BEGIN_MESSAGE_MAP(CNewPassDlg, CDialog)
   //{{AFX_MSG_MAP(CNewPassDlg)
   //}}AFX_MSG_MAP
END_MESSAGE_MAP()
//+------------------------------------------------------------------+
//|                                                                  |
//+------------------------------------------------------------------+
int CNewPassDlg::PassGet(LPSTR pass) const
  {
   if(pass!=NULL) strcpy(pass,m_newpass);
   return(m_investor);
  }
//+------------------------------------------------------------------+
//|                                                                  |
//+------------------------------------------------------------------+
BOOL CNewPassDlg::OnInitDialog()
  {
   CDialog::OnInitDialog();
//---
   m_NewPass.LimitText(sizeof(m_newpass)-1);
   m_Confirm.LimitText(sizeof(m_newpass)-1);
//---
   return(TRUE);
  }
//+------------------------------------------------------------------+
//|                                                                  |
//+------------------------------------------------------------------+
void CNewPassDlg::OnOK()
  {
   char confirm[sizeof(m_newpass)];
//---
   m_NewPass.GetWindowText(m_newpass,sizeof(m_newpass)-1);
   m_Confirm.GetWindowText(confirm,sizeof(m_newpass)-1);
   m_investor=m_Investor.GetCheck()!=BST_CHECKED?FALSE:TRUE;
//---
   if(m_newpass[0]==0 || strcmp(m_newpass,confirm)!=0)
     {
      ::MessageBeep(-1);
      return;
     }
//---
   CDialog::OnOK();
  }
//+------------------------------------------------------------------+
//|                                                                  |
//+------------------------------------------------------------------+
