//+------------------------------------------------------------------+
//|                                  MetaTrader 4 Manager API Sample |
//|                   Copyright 2001-2014, MetaQuotes Software Corp. |
//|                                        http://www.metaquotes.net |
//+------------------------------------------------------------------+
#pragma once

//+------------------------------------------------------------------+
//|                                                                  |
//+------------------------------------------------------------------+
class CUserBalanceDlg : public CDialog
  {
private:
   int               m_login;

public:
                     CUserBalanceDlg(const int login=0,CWnd *pParent=NULL);

   //{{AFX_DATA(CUserBalanceDlg)
   enum { IDD=IDD_USER_BALANCE };
   CEdit             m_Login;
   CEdit             m_Value;
   CDateTimeCtrl     m_ValueDate;
   CEdit             m_Comment;
   //}}AFX_DATA

   //{{AFX_VIRTUAL(CUserBalanceDlg)
protected:
   virtual void      DoDataExchange(CDataExchange* pDX);
   //}}AFX_VIRTUAL

protected:
   //{{AFX_MSG(CUserBalanceDlg)
   virtual BOOL      OnInitDialog();
   afx_msg void      OnBalance();
   afx_msg void      OnCredit();
   //}}AFX_MSG
   DECLARE_MESSAGE_MAP()
   //---
   void              TradeTrans(int cmd);
  };
//{{AFX_INSERT_LOCATION}}
//+------------------------------------------------------------------+
