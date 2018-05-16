//+------------------------------------------------------------------+
//|                                  MetaTrader 4 Manager API Sample |
//|                   Copyright 2001-2014, MetaQuotes Software Corp. |
//|                                        http://www.metaquotes.net |
//+------------------------------------------------------------------+
#include "stdafx.h"
#include "..\ManagerAPISample.h"
#include "requestdlg.h"

//+------------------------------------------------------------------+
//|                                                                  |
//+------------------------------------------------------------------+
CRequestDlg::CRequestDlg(CWnd *pParent) : CDialog(CRequestDlg::IDD, pParent)
  {
   //{{AFX_DATA_INIT(CRequestDlg)
   //}}AFX_DATA_INIT
  }
//+------------------------------------------------------------------+
//|                                                                  |
//+------------------------------------------------------------------+
void CRequestDlg::DoDataExchange(CDataExchange* pDX)
  {
   CDialog::DoDataExchange(pDX);
   //{{AFX_DATA_MAP(CRequestDlg)
   DDX_Control(pDX, IDC_LOGIN, m_Int);
   DDX_Control(pDX, IDC_ALL, m_All);
   DDX_Control(pDX, IDC_SINGLE, m_Single);
   //}}AFX_DATA_MAP
  }
//+------------------------------------------------------------------+
//|                                                                  |
//+------------------------------------------------------------------+
BEGIN_MESSAGE_MAP(CRequestDlg, CDialog)
   //{{AFX_MSG_MAP(CRequestDlg)
   ON_BN_CLICKED(IDC_ALL, OnAllSingle)
   ON_BN_CLICKED(IDC_SINGLE, OnAllSingle)
   ON_WM_KEYUP()
   //}}AFX_MSG_MAP
END_MESSAGE_MAP()
//+------------------------------------------------------------------+
//|                                                                  |
//+------------------------------------------------------------------+
BOOL CRequestDlg::OnInitDialog()
  {
   CDialog::OnInitDialog();
//---
   m_All.SetCheck(BST_CHECKED);
   OnAllSingle();
//---
   return(TRUE);
  }
//+------------------------------------------------------------------+
//|                                                                  |
//+------------------------------------------------------------------+
void CRequestDlg::OnAllSingle()
  {
   m_Int.EnableWindow(m_Single.GetCheck());
  }
//+------------------------------------------------------------------+
//|                                                                  |
//+------------------------------------------------------------------+
void CRequestDlg::OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags)
  {
   CDialog::OnKeyUp(nChar,nRepCnt,nFlags);
   OnAllSingle();
  }
//+------------------------------------------------------------------+
//|                                                                  |
//+------------------------------------------------------------------+
void CRequestDlg::OnOK()
  {
//---
   if(m_All.GetCheck()==BST_CHECKED) m_int=0;
   else                              m_int=GetDlgItemInt(m_Int.GetDlgCtrlID(),NULL,FALSE);
//---
   CDialog::OnOK();
  }
//+------------------------------------------------------------------+
//|                                                                  |
//+------------------------------------------------------------------+
