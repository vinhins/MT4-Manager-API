//+------------------------------------------------------------------+
//|                                  MetaTrader 4 Manager API Sample |
//|                   Copyright 2001-2014, MetaQuotes Software Corp. |
//|                                        http://www.metaquotes.net |
//+------------------------------------------------------------------+
#pragma once

//+------------------------------------------------------------------+
//|                                                                  |
//+------------------------------------------------------------------+
class CPageDaily : public CPropertyPageEx
  {
   DECLARE_DYNCREATE(CPageDaily)
private:
   DailyReport      *m_daily;
   int               m_daily_total;

public:
                     CPageDaily();
                    ~CPageDaily();

   //{{AFX_DATA(CPageDaily)
   enum { IDD=IDD_MANAGER_DAILY };
   CListCtrl         m_Daily;
   //}}AFX_DATA

   //{{AFX_VIRTUAL(CPageDaily)
protected:
   virtual void      DoDataExchange(CDataExchange* pDX);
   //}}AFX_VIRTUAL

protected:
   //{{AFX_MSG(CPageDaily)
   virtual BOOL      OnInitDialog();
   afx_msg void      OnDestroy();
   afx_msg void      OnRequest();
   afx_msg void      OnGetdispinfoDaily(NMHDR *pNMHDR,LRESULT *pResult);

   //}}AFX_MSG
   DECLARE_MESSAGE_MAP()
  };
//{{AFX_INSERT_LOCATION}}
//+------------------------------------------------------------------+
