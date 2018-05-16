//+------------------------------------------------------------------+
//|                                  MetaTrader 4 Manager API Sample |
//|                   Copyright 2001-2014, MetaQuotes Software Corp. |
//|                                        http://www.metaquotes.net |
//+------------------------------------------------------------------+
#pragma once

//+------------------------------------------------------------------+
//|                                                                  |
//+------------------------------------------------------------------+
class CUserGroupDlg : public CDialog
  {
private:
   GroupCommandInfo  m_info;
   int              *m_logins;

public:
                     CUserGroupDlg(const GroupCommandInfo *info,int *logins,CWnd *pParent=NULL);

   //{{AFX_DATA(CUserGroupDlg)
   enum { IDD=IDD_USER_GROUP };
   CListCtrl         m_Logins;
   CComboBox         m_Leverage;
   CComboBox         m_Group;
   //}}AFX_DATA

   //{{AFX_VIRTUAL(CUserGroupDlg)
protected:
   virtual void      DoDataExchange(CDataExchange* pDX);
   //}}AFX_VIRTUAL

protected:
   //{{AFX_MSG(CUserGroupDlg)
   virtual BOOL      OnInitDialog();
   afx_msg void      OnDelete();
   afx_msg void      OnDisable();
   afx_msg void      OnEnable();
   afx_msg void      OnSetgroup();
   afx_msg void      OnSetleverage();
   //}}AFX_MSG
   DECLARE_MESSAGE_MAP()
   //---
   void              GroupOp(int command);
  };
//{{AFX_INSERT_LOCATION}}
//+------------------------------------------------------------------+
