//+------------------------------------------------------------------+
//|                                  MetaTrader 4 Manager API Sample |
//|                   Copyright 2001-2014, MetaQuotes Software Corp. |
//|                                        http://www.metaquotes.net |
//+------------------------------------------------------------------+
#pragma once
//+------------------------------------------------------------------+
//|                                                                  |
//+------------------------------------------------------------------+
class CPageSummary : public CPropertyPageEx
  {
   DECLARE_DYNCREATE(CPageSummary)
private:
   SymbolSummary    *m_summary;
   int               m_summary_total;

public:
                     CPageSummary();
                    ~CPageSummary();

   //{{AFX_DATA(CPageSummary)
   enum { IDD=IDD_MANAGER_SUMMARY };
   CListCtrl         m_Summary;
   //}}AFX_DATA

   //{{AFX_VIRTUAL(CPageSummary)
protected:
   virtual void      DoDataExchange(CDataExchange* pDX);
   //}}AFX_VIRTUAL

protected:
   //{{AFX_MSG(CPageSummary)
   virtual BOOL      OnInitDialog();
   afx_msg void      OnGetdispinfoSummary(NMHDR *pNMHDR, LRESULT* pResult);
   afx_msg void      OnDestroy();
   //}}AFX_MSG
   afx_msg LRESULT   OnPumpingMsg(WPARAM wParam,LPARAM lParam);
   DECLARE_MESSAGE_MAP()
   //---
   void              UpdateSymbols();
  };
//{{AFX_INSERT_LOCATION}}
//+------------------------------------------------------------------+
