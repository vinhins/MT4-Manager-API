//+------------------------------------------------------------------+
//|                                  MetaTrader 4 Manager API Sample |
//|                   Copyright 2001-2014, MetaQuotes Software Corp. |
//|                                        http://www.metaquotes.net |
//+------------------------------------------------------------------+
#pragma once
//+------------------------------------------------------------------+
//|                                                                  |
//+------------------------------------------------------------------+
class CPageOrders : public CPropertyPageEx
  {
   DECLARE_DYNCREATE(CPageOrders)
private:
   TradeRecord      *m_trades;
   int               m_trades_total;
   int               m_show_pump;

public:
                     CPageOrders();
                    ~CPageOrders();

   //{{AFX_DATA(CPageOrders)
   enum { IDD=IDD_MANAGER_ORDERS };
   CListCtrl         m_Orders;
   //}}AFX_DATA

   //{{AFX_VIRTUAL(CPageOrders)
protected:
   virtual void      DoDataExchange(CDataExchange* pDX);
   //}}AFX_VIRTUAL

protected:
   //{{AFX_MSG(CPageOrders)
   virtual BOOL      OnInitDialog();
   afx_msg void      OnDestroy();
   afx_msg void      OnRequest();
   afx_msg void      OnGetdispinfoOrders(NMHDR *pNMHDR,LRESULT *pResult);

   afx_msg void      OnHistory();
   afx_msg void      OnOrdersGet();
   //}}AFX_MSG
   afx_msg LRESULT   OnPumpingMsg(WPARAM wParam,LPARAM lParam);
   DECLARE_MESSAGE_MAP()
  };
//{{AFX_INSERT_LOCATION}}
//+------------------------------------------------------------------+
