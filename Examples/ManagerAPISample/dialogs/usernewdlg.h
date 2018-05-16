//+------------------------------------------------------------------+
//|                                  MetaTrader 4 Manager API Sample |
//|                   Copyright 2001-2014, MetaQuotes Software Corp. |
//|                                        http://www.metaquotes.net |
//+------------------------------------------------------------------+
#pragma once

//+------------------------------------------------------------------+
//|                                                                  |
//+------------------------------------------------------------------+
class CUserNewDlg : public CDialog
  {
public:
                     CUserNewDlg(CWnd *pParent=NULL);

   //{{AFX_DATA(CUserNewDlg)
   enum { IDD=IDD_USER_NEW };
   CEdit             m_Password;
   CEdit             m_Name;
   CEdit             m_Login;
   CComboBox         m_Group;
   CEdit             m_Email;
   //}}AFX_DATA

   //{{AFX_VIRTUAL(CUserNewDlg)
protected:
   virtual void      DoDataExchange(CDataExchange* pDX);
   //}}AFX_VIRTUAL

protected:
   //{{AFX_MSG(CUserNewDlg)
   virtual BOOL      OnInitDialog();
   virtual void      OnOK();
   //}}AFX_MSG
   DECLARE_MESSAGE_MAP()
  };
//{{AFX_INSERT_LOCATION}}
//+------------------------------------------------------------------+
