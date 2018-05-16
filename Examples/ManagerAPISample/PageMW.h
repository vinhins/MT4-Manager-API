//+------------------------------------------------------------------+
//|                                  MetaTrader 4 Manager API Sample |
//|                   Copyright 2001-2014, MetaQuotes Software Corp. |
//|                                        http://www.metaquotes.net |
//+------------------------------------------------------------------+
#pragma once

//+------------------------------------------------------------------+
//|                                                                  |
//+------------------------------------------------------------------+
class CPageMW : public CPropertyPageEx
  {
   DECLARE_DYNCREATE(CPageMW)

public:
                     CPageMW();
                    ~CPageMW();

   //{{AFX_DATA(CPageMW)
   enum { IDD=IDD_MANAGER_MW };
   CListCtrl         m_Symbols;
   //}}AFX_DATA

   //{{AFX_VIRTUAL(CPageMW)
protected:
   virtual void      DoDataExchange(CDataExchange* pDX);
   //}}AFX_VIRTUAL

protected:
   //{{AFX_MSG(CPageMW)
   virtual BOOL      OnInitDialog();
   //}}AFX_MSG
   afx_msg LRESULT   OnPumpingMsg(WPARAM wParam,LPARAM lParam);
   DECLARE_MESSAGE_MAP()
   //---
   void              OnUpdateSymbols();
   void              OnUpdateBidAsk();
  };
//{{AFX_INSERT_LOCATION}}
//+------------------------------------------------------------------+
