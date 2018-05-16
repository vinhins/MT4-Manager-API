//+------------------------------------------------------------------+
//|                                  MetaTrader 4 Manager API Sample |
//|                   Copyright 2001-2014, MetaQuotes Software Corp. |
//|                                        http://www.metaquotes.net |
//+------------------------------------------------------------------+
#include "stdafx.h"
#include "..\ManagerAPISample.h"
#include "userhistorydlg.h"

//+------------------------------------------------------------------+
//|                                                                  |
//+------------------------------------------------------------------+
CUserHistoryDlg::CUserHistoryDlg(CWnd *pParent) : CDialog(CUserHistoryDlg::IDD, pParent)
  {
   //{{AFX_DATA_INIT(CUserHistoryDlg)
   //}}AFX_DATA_INIT
   m_login=0;
   m_from=m_to=0;
  }
//+------------------------------------------------------------------+
//|                                                                  |
//+------------------------------------------------------------------+
void CUserHistoryDlg::DoDataExchange(CDataExchange* pDX)
  {
   CDialog::DoDataExchange(pDX);
   //{{AFX_DATA_MAP(CUserHistoryDlg)
   DDX_Control(pDX, IDC_TO, m_To);
   DDX_Control(pDX, IDC_LOGIN, m_Login);
   DDX_Control(pDX, IDC_FROM, m_From);
   //}}AFX_DATA_MAP
  }
//+------------------------------------------------------------------+
//|                                                                  |
//+------------------------------------------------------------------+
BEGIN_MESSAGE_MAP(CUserHistoryDlg, CDialog)
   //{{AFX_MSG_MAP(CUserHistoryDlg)
   //}}AFX_MSG_MAP
END_MESSAGE_MAP()
//+------------------------------------------------------------------+
//|                                                                  |
//+------------------------------------------------------------------+
BOOL CUserHistoryDlg::OnInitDialog()
  {
   CDialog::OnInitDialog();
//---
   CTime from(0);
   m_From.SetTime(&from);
   time_t ctm=time(NULL);
   ctm/=86400; ctm*=86400;
   CTime to(ctm);
   m_To.SetTime(&to);
//---
   return(TRUE);
  }
//+------------------------------------------------------------------+
//|                                                                  |
//+------------------------------------------------------------------+
void CUserHistoryDlg::OnOK()
  {
//---
   m_login=GetDlgItemInt(m_Login.GetDlgCtrlID(),NULL,FALSE);
   CTime ct;
   m_From.GetTime(ct);
   m_from=(__time32_t)ct.GetTime()-_timezone;
   m_To.GetTime(ct);
   m_to=(__time32_t)ct.GetTime()-_timezone;
//---
   if(m_login<=0 || m_from>=m_to) { ::MessageBeep(-1); return; }
//---
   CDialog::OnOK();
  }
//+------------------------------------------------------------------+
//|                                                                  |
//+------------------------------------------------------------------+
