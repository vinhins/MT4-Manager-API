//+------------------------------------------------------------------+
//|                                  MetaTrader 4 Manager API Sample |
//|                   Copyright 2001-2014, MetaQuotes Software Corp. |
//|                                        http://www.metaquotes.net |
//+------------------------------------------------------------------+
#pragma once

//+------------------------------------------------------------------+
//|                                                                  |
//+------------------------------------------------------------------+
class CPageReports : public CPropertyPageEx
  {
   DECLARE_DYNCREATE(CPageReports)
private:
   TradeRecord      *m_trades;
   int               m_trades_total;

public:
                     CPageReports();
                    ~CPageReports();

   //{{AFX_DATA(CPageReports)
   enum { IDD=IDD_MANAGER_REPORTS };
   CListCtrl         m_Orders;
   //}}AFX_DATA

   //{{AFX_VIRTUAL(CPageReports)
protected:
   virtual void      DoDataExchange(CDataExchange* pDX);
   //}}AFX_VIRTUAL

protected:

   //{{AFX_MSG(CPageReports)
   virtual BOOL      OnInitDialog();
   afx_msg void      OnDestroy();
   afx_msg void      OnRequest();
   afx_msg void      OnGetdispinfoOrders(NMHDR *pNMHDR,LRESULT *pResult);

   //}}AFX_MSG
   DECLARE_MESSAGE_MAP()
  };
//{{AFX_INSERT_LOCATION}}
//+------------------------------------------------------------------+
