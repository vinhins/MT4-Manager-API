//+------------------------------------------------------------------+
//|                                  MetaTrader 4 Manager API Sample |
//|                   Copyright 2001-2014, MetaQuotes Software Corp. |
//|                                        http://www.metaquotes.net |
//+------------------------------------------------------------------+
#pragma once
//+------------------------------------------------------------------+
//|                                                                  |
//+------------------------------------------------------------------+
class CPageDealer : public CPropertyPageEx
  {
   DECLARE_DYNCREATE(CPageDealer)
protected:
   RequestInfo       m_req;

public:
                     CPageDealer();
                    ~CPageDealer();

   //{{AFX_DATA(CPageDealer)
   enum { IDD=IDD_MANAGER_DEALER };
   CButton           m_Return;
   CButton           m_Reject;
   CButton           m_Confirm;
   CEdit             m_Server;
   CStatic           m_Request;
   CEdit             m_Password;
   CEdit             m_Login;
   //}}AFX_DATA

   //{{AFX_VIRTUAL(CPageDealer)
protected:
   virtual void      DoDataExchange(CDataExchange* pDX);
   //}}AFX_VIRTUAL

protected:
   //{{AFX_MSG(CPageDealer)
   virtual BOOL      OnInitDialog();
   afx_msg void      OnDestroy();
   afx_msg void      OnConnect();
   afx_msg void      OnDisconnect();
   afx_msg void      OnConfirm();
   afx_msg void      OnReject();
   afx_msg void      OnReturn();
   //}}AFX_MSG
   afx_msg LRESULT   OnDealingMsg(WPARAM wParam,LPARAM lParam);
   DECLARE_MESSAGE_MAP()
   //---
   void              ShowRequest();
   void              EnableAnswer(BOOL enable);
  };
//{{AFX_INSERT_LOCATION}}
//+------------------------------------------------------------------+
