//+------------------------------------------------------------------+
//|                                  MetaTrader 4 Manager API Sample |
//|                   Copyright 2001-2014, MetaQuotes Software Corp. |
//|                                        http://www.metaquotes.net |
//+------------------------------------------------------------------+
#pragma once

//+------------------------------------------------------------------+
//|                                                                  |
//+------------------------------------------------------------------+
class CSymbolChangeDlg : public CDialog
  {
private:
   SymbolProperties  m_prop;
public:
                     CSymbolChangeDlg(const SymbolProperties *prop,CWnd *pParent=NULL);

   //{{AFX_DATA(CSymbolChangeDlg)
   enum { IDD=IDD_SYMBOL_CHANGE };
   CEdit             m_Stops;
   CEdit             m_Spread;
   CComboBox         m_ExeMode;
   //}}AFX_DATA

   //{{AFX_VIRTUAL(CSymbolChangeDlg)
protected:
   virtual void      DoDataExchange(CDataExchange* pDX);
   //}}AFX_VIRTUAL

protected:
   //{{AFX_MSG(CSymbolChangeDlg)
   virtual BOOL      OnInitDialog();
   virtual void      OnOK();
   //}}AFX_MSG
   DECLARE_MESSAGE_MAP()
  };
//{{AFX_INSERT_LOCATION}}
//+------------------------------------------------------------------+
