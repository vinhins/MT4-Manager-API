//+------------------------------------------------------------------+
//|                                  MetaTrader 4 Manager API Sample |
//|                   Copyright 2001-2014, MetaQuotes Software Corp. |
//|                                        http://www.metaquotes.net |
//+------------------------------------------------------------------+
#pragma once
//---
#include "PageMain.h"
#include "PageMW.h"
#include "PageSymbols.h"
#include "PageUsers.h"
#include "PageOnline.h"
#include "PageOrders.h"
#include "PageSummary.h"
#include "PageExposure.h"
#include "PageMargin.h"
#include "PageRequests.h"
#include "PagePlugins.h"
#include "PageDealer.h"
#include "PageMailbox.h"
#include "PageNews.h"
#include "PageReports.h"
#include "PageDaily.h"
#include "PageJournal.h"
#include "PageLogs.h"
//+------------------------------------------------------------------+
//|                                                                  |
//+------------------------------------------------------------------+
class CManagerSheet : public CPropertySheetEx
  {
   DECLARE_DYNAMIC(CManagerSheet)
protected:
   CPageMain         m_main;
   CPageMW           m_mw;
   CPageSymbols      m_symbols;
   CPageUsers        m_users;
   CPageOnline       m_online;
   CPageOrders       m_orders;
   CPageSummary      m_summary;
   CPageExposure     m_exposure;
   CPageMargin       m_margin;
   CPageRequests     m_requests;
   CPagePlugins      m_plugins;
   CPageDealer       m_dealer;
   CPageMailbox      m_mailbox;
   CPageNews         m_news;
   CPageReports      m_reports;
   CPageDaily        m_daily;
   CPageJournal      m_journal;
   CPageLogs         m_logs;
   //---
   static HWND       hwndThis;

public:
                     CManagerSheet(UINT nIDCaption, CWnd *pParentWnd=NULL, UINT iSelectPage=0);
   virtual          ~CManagerSheet();

   //{{AFX_VIRTUAL(CManagerSheet)
public:
   virtual BOOL      OnInitDialog();
   //}}AFX_VIRTUAL

   static void __stdcall PumpingFunc(int code);

protected:
   //{{AFX_MSG(CManagerSheet)
   afx_msg void      OnDestroy();
   //}}AFX_MSG
   afx_msg LRESULT   OnPumpingMsg(WPARAM wParam,LPARAM lParam);
   DECLARE_MESSAGE_MAP()
  };
//{{AFX_INSERT_LOCATION}}
//+------------------------------------------------------------------+
