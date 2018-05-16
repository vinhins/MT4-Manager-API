//+------------------------------------------------------------------+
//|                                  MetaTrader 4 Manager API Sample |
//|                   Copyright 2001-2014, MetaQuotes Software Corp. |
//|                                        http://www.metaquotes.net |
//+------------------------------------------------------------------+
#pragma once

//+------------------------------------------------------------------+
//|                                                                  |
//+------------------------------------------------------------------+
class CPageMain : public CPropertyPageEx
  {
   DECLARE_DYNCREATE(CPageMain)

public:
                     CPageMain();
                    ~CPageMain();

   //{{AFX_DATA(CPageMain)
   enum { IDD=IDD_MANAGER_MAIN };
   CListCtrl         m_Groups;
   CEdit             m_Server;
   CEdit             m_Password;
   CEdit             m_Login;
   //}}AFX_DATA

   //{{AFX_VIRTUAL(CPageMain)
protected:
   virtual void      DoDataExchange(CDataExchange* pDX);
   //}}AFX_VIRTUAL

protected:
   //{{AFX_MSG(CPageMain)
   virtual BOOL      OnInitDialog();
   afx_msg void      OnConnect();
   afx_msg void      OnLogincmd();
   afx_msg void      OnDisconnect();
   afx_msg void      OnRights();
   afx_msg void      OnReqGroups();
   afx_msg void      OnSendMail();
   afx_msg void      OnSendNews();
   afx_msg void      OnPumping();
   //}}AFX_MSG
   DECLARE_MESSAGE_MAP()
  };
//{{AFX_INSERT_LOCATION}}
//+------------------------------------------------------------------+
