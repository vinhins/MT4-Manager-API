//+------------------------------------------------------------------+
//|                                      MetaTrader Manager API Test |
//|                   Copyright 2001-2014, MetaQuotes Software Corp. |
//|                                        http://www.metaquotes.net |
//+------------------------------------------------------------------+
#pragma once

//+------------------------------------------------------------------+
//|                                                                  |
//+------------------------------------------------------------------+
class CNewPassDlg : public CDialog
  {
protected:
   char              m_newpass[16];
   int               m_investor;
public:
                     CNewPassDlg(CWnd *pParent=NULL);

   int               PassGet(LPSTR pass) const;

   //{{AFX_DATA(CNewPassDlg)
   enum { IDD=IDD_PASS_CHANGE };
   CEdit             m_NewPass;
   CButton           m_Investor;
   CEdit             m_Confirm;
   //}}AFX_DATA

   //{{AFX_VIRTUAL(CNewPassDlg)
protected:
   virtual void      DoDataExchange(CDataExchange* pDX);
   //}}AFX_VIRTUAL

protected:
   //{{AFX_MSG(CNewPassDlg)
   virtual BOOL      OnInitDialog();
   virtual void      OnOK();
   //}}AFX_MSG
   DECLARE_MESSAGE_MAP()
  };
//{{AFX_INSERT_LOCATION}}
//+------------------------------------------------------------------+
