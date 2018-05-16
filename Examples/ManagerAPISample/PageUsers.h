//+------------------------------------------------------------------+
//|                                  MetaTrader 4 Manager API Sample |
//|                   Copyright 2001-2014, MetaQuotes Software Corp. |
//|                                        http://www.metaquotes.net |
//+------------------------------------------------------------------+
#pragma once

//+------------------------------------------------------------------+
//|                                                                  |
//+------------------------------------------------------------------+
class CPageUsers : public CPropertyPageEx
  {
   DECLARE_DYNCREATE(CPageUsers)
private:
   UserRecord       *m_users;
   int               m_users_total;

public:
                     CPageUsers();
                    ~CPageUsers();

   //{{AFX_DATA(CPageUsers)
   enum { IDD=IDD_MANAGER_USERS };
   CListCtrl         m_Users;
   //}}AFX_DATA

   //{{AFX_VIRTUAL(CPageUsers)
protected:
   virtual void      DoDataExchange(CDataExchange* pDX);
   //}}AFX_VIRTUAL

protected:
   //{{AFX_MSG(CPageUsers)
   virtual BOOL      OnInitDialog();
   afx_msg void      OnDestroy();
   afx_msg void      OnRequest();
   afx_msg void      OnGetdispinfoUsers(NMHDR *pNMHDR,LRESULT *pResult);
   afx_msg void      OnNew();
   afx_msg void      OnUpdate();
   afx_msg void      OnDblclkUsers(NMHDR *pNMHDR,LRESULT *pResult);
   afx_msg void      OnGroupop();
   afx_msg void      OnBalance();
   afx_msg void      OnUsersGet();
   afx_msg void      OnMargin();
   //}}AFX_MSG
   afx_msg LRESULT   OnPumpingMsg(WPARAM wParam,LPARAM lParam);
   DECLARE_MESSAGE_MAP()
  };
//{{AFX_INSERT_LOCATION}}
//+------------------------------------------------------------------+
