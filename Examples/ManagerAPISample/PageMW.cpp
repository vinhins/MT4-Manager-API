//+------------------------------------------------------------------+
//|                                  MetaTrader 4 Manager API Sample |
//|                   Copyright 2001-2014, MetaQuotes Software Corp. |
//|                                        http://www.metaquotes.net |
//+------------------------------------------------------------------+
#include "stdafx.h"
#include "ManagerAPISample.h"
#include "PageMW.h"

//+------------------------------------------------------------------+
//|                                                                  |
//+------------------------------------------------------------------+
IMPLEMENT_DYNCREATE(CPageMW, CPropertyPageEx)
//+------------------------------------------------------------------+
//|                                                                  |
//+------------------------------------------------------------------+
CPageMW::CPageMW() : CPropertyPageEx(CPageMW::IDD)
  {
   //{{AFX_DATA_INIT(CPageMW)
   //}}AFX_DATA_INIT
   m_psp.dwFlags&=~PSP_HASHELP;
  }
//+------------------------------------------------------------------+
//|                                                                  |
//+------------------------------------------------------------------+
CPageMW::~CPageMW()
  {
  }
//+------------------------------------------------------------------+
//|                                                                  |
//+------------------------------------------------------------------+
void CPageMW::DoDataExchange(CDataExchange* pDX)
  {
   CPropertyPageEx::DoDataExchange(pDX);
   //{{AFX_DATA_MAP(CPageMW)
   DDX_Control(pDX, IDC_SYMBOLS, m_Symbols);
   //}}AFX_DATA_MAP
  }
//+------------------------------------------------------------------+
//|                                                                  |
//+------------------------------------------------------------------+
BEGIN_MESSAGE_MAP(CPageMW, CPropertyPageEx)
   //{{AFX_MSG_MAP(CPageMW)
   //}}AFX_MSG_MAP
   ON_REGISTERED_MESSAGE(ExtPumpingMsg,OnPumpingMsg)
END_MESSAGE_MAP()
//+------------------------------------------------------------------+
//|                                                                  |
//+------------------------------------------------------------------+
BOOL CPageMW::OnInitDialog()
  {
   CRect rc;
   int   cx=0;
//---
   CPropertyPageEx::OnInitDialog();
//---
   m_Symbols.SetExtendedStyle(LVS_EX_FULLROWSELECT);
   m_Symbols.GetClientRect(&rc);
   cx=(rc.Width()-::GetSystemMetrics(SM_CXVSCROLL)-::GetSystemMetrics(SM_CXBORDER)*4)/3;
   m_Symbols.InsertColumn(0,"Symbol",LVCFMT_LEFT, cx);
   m_Symbols.InsertColumn(1,"Bid",   LVCFMT_RIGHT,cx);
   m_Symbols.InsertColumn(2,"Ask",   LVCFMT_RIGHT,cx);
//---
   return(TRUE);
  }
//+------------------------------------------------------------------+
//|                                                                  |
//+------------------------------------------------------------------+
LRESULT CPageMW::OnPumpingMsg(WPARAM wParam,LPARAM)
  {
//---
   switch(wParam)
     {
      case PUMP_START_PUMPING:
      case PUMP_UPDATE_SYMBOLS: OnUpdateSymbols(); break;
      case PUMP_UPDATE_BIDASK:  OnUpdateBidAsk();  break;
      default: break;
     }
//---
   return(0);
  }
//+------------------------------------------------------------------+
//|                                                                  |
//+------------------------------------------------------------------+
void CPageMW::OnUpdateSymbols()
  {
   ConSymbol *cs   =NULL;
   int        total=0,i;
//---
   cs=ExtManagerPump->SymbolsGetAll(&total);
   m_Symbols.DeleteAllItems();
   for(i=0; i<total; i++)
     {
      ExtManagerPump->SymbolAdd(cs[i].symbol);
      m_Symbols.InsertItem(i,cs[i].symbol);
     }
   if(cs!=NULL) { ExtManagerPump->MemFree(cs); cs=NULL; total=0; }
//---
  }
//+------------------------------------------------------------------+
//|                                                                  |
//+------------------------------------------------------------------+
void CPageMW::OnUpdateBidAsk()
  {
   SymbolInfo si[32];
   int        total=0,pos=-1;
   LVFINDINFO lvfi={ LVFI_STRING };
   CString    sFormat,sPrice;
//---
   while((total=ExtManagerPump->SymbolInfoUpdated(si,32))>0)
     {
      for(int i=0; i<total; i++)
        {
         lvfi.psz=si[i].symbol;
         if((pos=m_Symbols.FindItem(&lvfi))<0) continue;
         sFormat.Format(_T("%%.%dlf"),si[i].digits);
         sPrice.Format(sFormat,si[i].bid);
         m_Symbols.SetItemText(pos,1,sPrice);
         sPrice.Format(sFormat,si[i].ask);
         m_Symbols.SetItemText(pos,2,sPrice);
        }
     }
//---
  }
//+------------------------------------------------------------------+
//|                                                                  |
//+------------------------------------------------------------------+
