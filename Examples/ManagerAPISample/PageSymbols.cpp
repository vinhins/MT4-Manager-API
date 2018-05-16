//+------------------------------------------------------------------+
//|                                  MetaTrader 4 Manager API Sample |
//|                   Copyright 2001-2014, MetaQuotes Software Corp. |
//|                                        http://www.metaquotes.net |
//+------------------------------------------------------------------+
#include "stdafx.h"
#include "ManagerAPISample.h"
#include "PageSymbols.h"
#include "dialogs\SymbolChangeDlg.h"

//+------------------------------------------------------------------+
//|                                                                  |
//+------------------------------------------------------------------+
IMPLEMENT_DYNCREATE(CPageSymbols, CPropertyPageEx)
//+------------------------------------------------------------------+
//|                                                                  |
//+------------------------------------------------------------------+
CPageSymbols::CPageSymbols() : CPropertyPageEx(CPageSymbols::IDD),
   m_symbols(NULL),m_symbols_total(0)
  {
   //{{AFX_DATA_INIT(CPageSymbols)
   //}}AFX_DATA_INIT
   m_psp.dwFlags&=~PSP_HASHELP;
  }
//+------------------------------------------------------------------+
//|                                                                  |
//+------------------------------------------------------------------+
CPageSymbols::~CPageSymbols()
  {
  }
//+------------------------------------------------------------------+
//|                                                                  |
//+------------------------------------------------------------------+
void CPageSymbols::DoDataExchange(CDataExchange* pDX)
  {
   CPropertyPageEx::DoDataExchange(pDX);
   //{{AFX_DATA_MAP(CPageSymbols)
   DDX_Control(pDX, IDC_SYMBOLS, m_Symbols);
   //}}AFX_DATA_MAP
  }
//+------------------------------------------------------------------+
//|                                                                  |
//+------------------------------------------------------------------+
BEGIN_MESSAGE_MAP(CPageSymbols, CPropertyPageEx)
   //{{AFX_MSG_MAP(CPageSymbols)
   ON_BN_CLICKED(IDC_REFRESH, OnRefresh)
   ON_WM_DESTROY()
   ON_BN_CLICKED(IDC_CHANGE, OnChange)
   ON_NOTIFY(NM_DBLCLK, IDC_SYMBOLS, OnDblclkSymbols)
   //}}AFX_MSG_MAP
END_MESSAGE_MAP()
//+------------------------------------------------------------------+
//|                                                                  |
//+------------------------------------------------------------------+
BOOL CPageSymbols::OnInitDialog()
  {
   CRect rc;
   int   cx;
//---
   CPropertyPageEx::OnInitDialog();
//---
   m_Symbols.SetExtendedStyle(LVS_EX_FULLROWSELECT);
   m_Symbols.GetClientRect(&rc);
   cx=(rc.Width()-::GetSystemMetrics(SM_CXVSCROLL)-::GetSystemMetrics(SM_CXBORDER)*4)/4;
   m_Symbols.InsertColumn(0,"Symbol",     LVCFMT_LEFT,cx);
   m_Symbols.InsertColumn(1,"Execution",  LVCFMT_LEFT,cx);
   m_Symbols.InsertColumn(2,"Stops Level",LVCFMT_LEFT,cx);
   m_Symbols.InsertColumn(3,"Spread",     LVCFMT_LEFT,cx);
//---
   return(TRUE);
  }
//+------------------------------------------------------------------+
//|                                                                  |
//+------------------------------------------------------------------+
void CPageSymbols::OnDestroy()
  {
//---
   if(m_symbols!=NULL) { ExtManager->MemFree(m_symbols); m_symbols=NULL; m_symbols_total=0; }
//---
   CPropertyPageEx::OnDestroy();
  }
//+------------------------------------------------------------------+
//|                                                                  |
//+------------------------------------------------------------------+
void CPageSymbols::OnRefresh()
  {
   static LPCSTR exeModes[3]={ "Request","Instant","Market" };
   CString str;
   int     res=RET_ERROR;
//---
   if(m_symbols!=NULL) { ExtManager->MemFree(m_symbols); m_symbols=NULL; m_symbols_total=0; }
//---
   res=ExtManager->SymbolsRefresh();
   if(res!=RET_OK) { MessageBox(ExtManager->ErrorDescription(res),"SymbolsRefresh"); return; }
   m_symbols=ExtManager->SymbolsGetAll(&m_symbols_total);
//---
   m_Symbols.DeleteAllItems();
   for(int i=0; i<m_symbols_total; i++)
     {
      m_Symbols.InsertItem(i,m_symbols[i].symbol);
      m_Symbols.SetItemText(i,1,exeModes[m_symbols[i].exemode]);
      str.Format("%d",m_symbols[i].stops_level);
      m_Symbols.SetItemText(i,2,str);
      str.Format("%d",m_symbols[i].spread);
      m_Symbols.SetItemText(i,3,str);
     }
//---
  }
//+------------------------------------------------------------------+
//|                                                                  |
//+------------------------------------------------------------------+
void CPageSymbols::OnChange()
  {
   POSITION pos=m_Symbols.GetFirstSelectedItemPosition();
   int      i=-1;
   SymbolProperties prop={""};
//---
   if(pos==NULL || (i=m_Symbols.GetNextSelectedItem(pos))<0 || i>=m_symbols_total)
     {
      MessageBox("Select symbol","Change Symbol");
      return;
     }
//---
   COPY_STR(prop.symbol,m_symbols[i].symbol);
   prop.exemode       =m_symbols[i].exemode;
   prop.stops_level   =m_symbols[i].stops_level;
   prop.spread        =m_symbols[i].spread;
   prop.spread_balance=m_symbols[i].spread_balance;
   prop.color         =m_symbols[i].background_color;
//---
   CSymbolChangeDlg dlg(&prop);
   dlg.DoModal();
//---
  }
//+------------------------------------------------------------------+
//|                                                                  |
//+------------------------------------------------------------------+

//+------------------------------------------------------------------+
//|                                                                  |
//+------------------------------------------------------------------+
void CPageSymbols::OnDblclkSymbols(NMHDR *pNMHDR,LRESULT *pResult)
  {
   if(pResult!=NULL) *pResult=0;
   OnChange();
  }
//+------------------------------------------------------------------+
//|                                                                  |
//+------------------------------------------------------------------+
