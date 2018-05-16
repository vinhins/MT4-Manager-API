//+------------------------------------------------------------------+
//|                                  MetaTrader 4 Manager API Sample |
//|                   Copyright 2001-2014, MetaQuotes Software Corp. |
//|                                        http://www.metaquotes.net |
//+------------------------------------------------------------------+
#pragma once

//+------------------------------------------------------------------+
//|                                                                  |
//+------------------------------------------------------------------+
class CPageNews : public CPropertyPageEx
  {
   DECLARE_DYNCREATE(CPageNews)
public:
                     CPageNews();
                    ~CPageNews();

   //{{AFX_DATA(CPageNews)
   enum { IDD=IDD_MANAGER_NEWS };
   CListCtrl         m_News;
   //}}AFX_DATA

   //{{AFX_VIRTUAL(CPageNews)
protected:
   virtual void      DoDataExchange(CDataExchange* pDX);
   //}}AFX_VIRTUAL

protected:
   //{{AFX_MSG(CPageNews)
   virtual BOOL      OnInitDialog();
   afx_msg void      OnGetdispinfoNews(NMHDR *pNMHDR,LRESULT *pResult);

   //}}AFX_MSG
   afx_msg LRESULT   OnPumpingMsg(WPARAM wParam,LPARAM lParam);
   DECLARE_MESSAGE_MAP()
  };
//{{AFX_INSERT_LOCATION}}
//+------------------------------------------------------------------+
