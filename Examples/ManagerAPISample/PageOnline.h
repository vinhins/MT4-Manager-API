//+------------------------------------------------------------------+
//|                                  MetaTrader 4 Manager API Sample |
//|                   Copyright 2001-2014, MetaQuotes Software Corp. |
//|                                        http://www.metaquotes.net |
//+------------------------------------------------------------------+
#pragma once

class CPageOnline : public CPropertyPageEx
  {
   DECLARE_DYNCREATE(CPageOnline)
private:
   OnlineRecord     *m_users;
   int               m_users_total;

public:
                     CPageOnline();
                    ~CPageOnline();

   //{{AFX_DATA(CPageOnline)
   enum { IDD=IDD_MANAGER_ONLINE };
   CListCtrl         m_Users;
   //}}AFX_DATA

   //{{AFX_VIRTUAL(CPageOnline)
protected:
   virtual void      DoDataExchange(CDataExchange* pDX);
   //}}AFX_VIRTUAL

protected:
   //{{AFX_MSG(CPageOnline)
   virtual BOOL      OnInitDialog();
   afx_msg void      OnDestroy();
   afx_msg void      OnRequest();
   afx_msg void      OnGetdispinfoUsers(NMHDR *pNMHDR,LRESULT *pResult);

   afx_msg void      OnOnlineGet();
   //}}AFX_MSG
   afx_msg LRESULT   OnPumpingMsg(WPARAM wParam,LPARAM lParam);
   DECLARE_MESSAGE_MAP()
  };
//{{AFX_INSERT_LOCATION}}
//+------------------------------------------------------------------+
