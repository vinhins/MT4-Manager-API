//+------------------------------------------------------------------+
//|                                  MetaTrader 4 Manager API Sample |
//|                   Copyright 2001-2014, MetaQuotes Software Corp. |
//|                                        http://www.metaquotes.net |
//+------------------------------------------------------------------+
#pragma once
//+------------------------------------------------------------------+
//|                                                                  |
//+------------------------------------------------------------------+
class CPageMargin : public CPropertyPageEx
  {
   DECLARE_DYNCREATE(CPageMargin)
private:
   MarginLevel      *m_levels;
   int               m_levels_total;

public:
                     CPageMargin();
                    ~CPageMargin();

   //{{AFX_DATA(CPageMargin)
   enum { IDD=IDD_MANAGER_MARGIN };
   CListCtrl         m_Users;
   //}}AFX_DATA

   //{{AFX_VIRTUAL(CPageMargin)
protected:
   virtual void      DoDataExchange(CDataExchange* pDX);
   //}}AFX_VIRTUAL

protected:
   //{{AFX_MSG(CPageMargin)
   virtual BOOL      OnInitDialog();
   afx_msg void      OnGetdispinfoUsers(NMHDR *pNMHDR,LRESULT *pResult);
   afx_msg void      OnDestroy();
   //}}AFX_MSG
   afx_msg LRESULT   OnPumpingMsg(WPARAM wParam,LPARAM lParam);
   DECLARE_MESSAGE_MAP()
  };
//{{AFX_INSERT_LOCATION}}
//+------------------------------------------------------------------+
