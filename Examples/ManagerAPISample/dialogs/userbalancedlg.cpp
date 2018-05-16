//+------------------------------------------------------------------+
//|                                  MetaTrader 4 Manager API Sample |
//|                   Copyright 2001-2014, MetaQuotes Software Corp. |
//|                                        http://www.metaquotes.net |
//+------------------------------------------------------------------+
#include "stdafx.h"
#include "..\ManagerAPISample.h"
#include "userbalancedlg.h"

//+------------------------------------------------------------------+
//|                                                                  |
//+------------------------------------------------------------------+
CUserBalanceDlg::CUserBalanceDlg(const int login/*=0*/,CWnd *pParent) : CDialog(CUserBalanceDlg::IDD, pParent),m_login(login)
  {
   //{{AFX_DATA_INIT(CUserBalanceDlg)
   //}}AFX_DATA_INIT
  }
//+------------------------------------------------------------------+
//|                                                                  |
//+------------------------------------------------------------------+
void CUserBalanceDlg::DoDataExchange(CDataExchange* pDX)
  {
   CDialog::DoDataExchange(pDX);
   //{{AFX_DATA_MAP(CUserBalanceDlg)
   DDX_Control(pDX, IDC_LOGIN, m_Login);
   DDX_Control(pDX, IDC_VALUE, m_Value);
   DDX_Control(pDX, IDC_VALUE_DATE, m_ValueDate);
   DDX_Control(pDX, IDC_COMMENT, m_Comment);
   //}}AFX_DATA_MAP
  }
//+------------------------------------------------------------------+
//|                                                                  |
//+------------------------------------------------------------------+
BEGIN_MESSAGE_MAP(CUserBalanceDlg, CDialog)
   //{{AFX_MSG_MAP(CUserBalanceDlg)
   ON_BN_CLICKED(IDC_BALANCE, OnBalance)
   ON_BN_CLICKED(IDC_CREDIT, OnCredit)
   //}}AFX_MSG_MAP
END_MESSAGE_MAP()
//+------------------------------------------------------------------+
//|                                                                  |
//+------------------------------------------------------------------+
BOOL CUserBalanceDlg::OnInitDialog()
  {
   CDialog::OnInitDialog();
//---
   if(m_login>0) SetDlgItemInt(m_Login.GetDlgCtrlID(),m_login,FALSE);
//---
   return(TRUE);
  }
//+------------------------------------------------------------------+
//|                                                                  |
//+------------------------------------------------------------------+
void CUserBalanceDlg::OnBalance() { TradeTrans(OP_BALANCE); }
//+------------------------------------------------------------------+
//|                                                                  |
//+------------------------------------------------------------------+
void CUserBalanceDlg::OnCredit()  { TradeTrans(OP_CREDIT);  }
//+------------------------------------------------------------------+
//|                                                                  |
//+------------------------------------------------------------------+
void CUserBalanceDlg::TradeTrans(int cmd)
  {
   TradeTransInfo info={0};
   char           tmp[32];
//--- данные
   info.type   =TT_BR_BALANCE;
   info.cmd    =cmd;
   info.orderby=GetDlgItemInt(m_Login.GetDlgCtrlID(),NULL,FALSE);
   m_Value.GetWindowText(tmp,32);
   info.price=atof(tmp);
   if(cmd==OP_CREDIT)
     {
      CTime vt;
      m_ValueDate.GetTime(vt);
      info.expiration=(__time32_t)vt.GetTime()-_timezone;
     }
   m_Comment.GetWindowText(info.comment,sizeof(info.comment)-1);
//---
   if(info.orderby<=0) { ::MessageBeep(-1); m_Login.SetFocus(); return; }
//---
   int res=ExtManager->TradeTransaction(&info);
   MessageBox(ExtManager->ErrorDescription(res),"TradeTransaction");
//---
   if(res==RET_OK) EndDialog(IDOK);
  }
//+------------------------------------------------------------------+
//|                                                                  |
//+------------------------------------------------------------------+
