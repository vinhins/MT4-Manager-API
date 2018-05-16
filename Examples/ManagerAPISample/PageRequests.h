//+------------------------------------------------------------------+
//|                                  MetaTrader 4 Manager API Sample |
//|                   Copyright 2001-2014, MetaQuotes Software Corp. |
//|                                        http://www.metaquotes.net |
//+------------------------------------------------------------------+
#pragma once
//+------------------------------------------------------------------+
//|                                                                  |
//+------------------------------------------------------------------+
class CPageRequests : public CPropertyPageEx
  {
   DECLARE_DYNCREATE(CPageRequests)

public:
                     CPageRequests();
                    ~CPageRequests();

   //{{AFX_DATA(CPageRequests)
   enum { IDD=IDD_MANAGER_REQUESTS };
   CListCtrl         m_Requests;
   //}}AFX_DATA

   //{{AFX_VIRTUAL(CPageRequests)
protected:
   virtual void      DoDataExchange(CDataExchange* pDX);
   //}}AFX_VIRTUAL

protected:
   //{{AFX_MSG(CPageRequests)
   virtual BOOL      OnInitDialog();
   //}}AFX_MSG
   afx_msg LRESULT   OnPumpingMsg(WPARAM wParam,LPARAM lParam);
   DECLARE_MESSAGE_MAP()
  };
//{{AFX_INSERT_LOCATION}}
//+------------------------------------------------------------------+
