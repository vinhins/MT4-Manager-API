//+------------------------------------------------------------------+
//|                                  MetaTrader 4 Manager API Sample |
//|                   Copyright 2001-2014, MetaQuotes Software Corp. |
//|                                        http://www.metaquotes.net |
//+------------------------------------------------------------------+
#pragma once
//+------------------------------------------------------------------+
//|                                                                  |
//+------------------------------------------------------------------+
class CPageSymbols : public CPropertyPageEx
  {
   DECLARE_DYNCREATE(CPageSymbols)
private:
   ConSymbol        *m_symbols;
   int               m_symbols_total;

public:
                     CPageSymbols();
                    ~CPageSymbols();

   //{{AFX_DATA(CPageSymbols)
   enum { IDD=IDD_MANAGER_SYMBOLS };
   CListCtrl         m_Symbols;
   //}}AFX_DATA

   //{{AFX_VIRTUAL(CPageSymbols)
protected:
   virtual void      DoDataExchange(CDataExchange* pDX);
   //}}AFX_VIRTUAL

protected:
   //{{AFX_MSG(CPageSymbols)
   virtual BOOL      OnInitDialog();
   afx_msg void      OnRefresh();
   afx_msg void      OnDestroy();
   afx_msg void      OnChange();
   afx_msg void      OnDblclkSymbols(NMHDR *pNMHDR,LRESULT *pResult);

   //}}AFX_MSG
   DECLARE_MESSAGE_MAP()
  };
//{{AFX_INSERT_LOCATION}}
//+------------------------------------------------------------------+
