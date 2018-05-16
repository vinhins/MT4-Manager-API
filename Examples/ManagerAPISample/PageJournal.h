//+------------------------------------------------------------------+
//|                                  MetaTrader 4 Manager API Sample |
//|                   Copyright 2001-2014, MetaQuotes Software Corp. |
//|                                        http://www.metaquotes.net |
//+------------------------------------------------------------------+
#pragma once

//+------------------------------------------------------------------+
//|                                                                  |
//+------------------------------------------------------------------+
class CPageJournal : public CPropertyPageEx
  {
   DECLARE_DYNCREATE(CPageJournal)
private:
   ServerLog        *m_logs;
   int               m_logs_total;

public:
                     CPageJournal();
                    ~CPageJournal();

   //{{AFX_DATA(CPageJournal)
   enum { IDD=IDD_MANAGER_JOURNAL };
   CListCtrl         m_Journal;
   CDateTimeCtrl     m_To;
   CComboBox         m_Mode;
   CDateTimeCtrl     m_From;
   //}}AFX_DATA

   //{{AFX_VIRTUAL(CPageJournal)
protected:
   virtual void      DoDataExchange(CDataExchange* pDX);
   //}}AFX_VIRTUAL

protected:
   //{{AFX_MSG(CPageJournal)
   virtual BOOL      OnInitDialog();
   afx_msg void      OnDestroy();
   afx_msg void      OnRequest();
   afx_msg void      OnGetdispinfoJournal(NMHDR *pNMHDR,LRESULT *pResult);

   //}}AFX_MSG
   DECLARE_MESSAGE_MAP()
  };
//{{AFX_INSERT_LOCATION}}
//+------------------------------------------------------------------+
