//+------------------------------------------------------------------+
//|                                  MetaTrader 4 Manager API Sample |
//|                   Copyright 2001-2014, MetaQuotes Software Corp. |
//|                                        http://www.metaquotes.net |
//+------------------------------------------------------------------+
#pragma once

//+------------------------------------------------------------------+
//|                                                                  |
//+------------------------------------------------------------------+
class CUserUpdateDlg : public CDialog
  {
private:
   UserRecord        m_user;

public:
                     CUserUpdateDlg(const UserRecord *user,CWnd *pParent=NULL);

   //{{AFX_DATA(CUserUpdateDlg)
   enum { IDD=IDD_USER_UPDATE };
   CEdit             m_Name;
   CEdit             m_Login;
   CComboBox         m_Group;
   CEdit             m_Email;
   //}}AFX_DATA

   //{{AFX_VIRTUAL(CUserUpdateDlg)
protected:
   virtual void      DoDataExchange(CDataExchange* pDX);
   //}}AFX_VIRTUAL

protected:
   //{{AFX_MSG(CUserUpdateDlg)
   virtual BOOL      OnInitDialog();
   virtual void      OnOK();
   //}}AFX_MSG
   DECLARE_MESSAGE_MAP()
  };
//{{AFX_INSERT_LOCATION}}
//+------------------------------------------------------------------+
