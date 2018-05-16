//+------------------------------------------------------------------+
//|                                      MetaTrader Manager API Test |
//|                   Copyright 2001-2014, MetaQuotes Software Corp. |
//|                                        http://www.metaquotes.net |
//+------------------------------------------------------------------+
#pragma once
//---
#include "..\..\API\MT4ManagerAPI.h"
//---
  enum { DISPLAY_CHART=CONFIG_END,DISPLAY_PERFORMANCE,
   DISPLAY_BACKUP_USERS,DISPLAY_BACKUP_TRADES,
  DISPLAY_BASE_USERS,  DISPLAY_BASE_TRADES };
//+------------------------------------------------------------------+
//|                                                                  |
//+------------------------------------------------------------------+
class CManagerAPITestDlg : public CDialog
  {
protected:
   CManagerFactory   m_factory;
   CManagerInterface *m_manager;
   //---
   int               m_total;
   ConCommon         m_common;
   ConTime           m_time;
   ConBackup         m_backup;
   ConAccess        *m_access;
   ConDataServer    *m_datasrv;
   ConHoliday       *m_holiday;
   ConSymbol        *m_symbols;
   ConSymbolGroup    m_security[MAX_SEC_GROUPS];
   ConGroup         *m_groups;
   ConManager       *m_managers;
   ConFeeder        *m_feeders;
   ConLiveUpdate    *m_liveupdate;
   ConSync          *m_synchro;
   ConPluginParam   *m_plugins;
   ConGatewayAccount *m_gateway_accounts;
   ConGatewayMarkup *m_gateway_markups;
   ConGatewayRule   *m_gateway_rules;
   //---
   ServerFeed       *m_feeds;
   LPSTR             m_feed_log;
   //---
   ChartInfo         m_chart;
   int               m_digits;
   RateInfo         *m_rates;
   //---
   PerformanceInfo  *m_performance;
   //---
   BackupInfo       *m_backups;
   //---
   UserRecord       *m_users;
   TradeRecord      *m_trades;
   //---
   int               m_display_type;
public:
                     CManagerAPITestDlg(CWnd *pParent=NULL);

   //{{AFX_DATA(CManagerAPITestDlg)
   enum { IDD=IDD_MANAGERAPITEST };
   CComboBox         m_BaseGroup;
   CComboBox         m_Backup;
   CComboBox         m_Period;
   CComboBox         m_Symbol;
   CComboBox         m_Config;
   CEdit             m_Feeder;
   CListCtrl         m_Results;
   CEdit             m_Server;
   CEdit             m_Password;
   CEdit             m_Login;
   //}}AFX_DATA

   //{{AFX_VIRTUAL(CManagerAPITestDlg)
protected:
   virtual void      DoDataExchange(CDataExchange* pDX);
   //}}AFX_VIRTUAL

protected:
   HICON             m_hIcon;

   //{{AFX_MSG(CManagerAPITestDlg)
   virtual BOOL      OnInitDialog();
   afx_msg void      OnPaint();
   afx_msg HCURSOR   OnQueryDragIcon();
   afx_msg void      OnDestroy();
   afx_msg void      OnConnect();
   afx_msg void      OnLogincmd();
   afx_msg void      OnDisconnect();
   afx_msg void      OnPing();
   afx_msg void      OnPassChange();
   afx_msg void      OnRestart();
   afx_msg void      OnChartsync();
   afx_msg void      OnLiveupdate();
   afx_msg void      OnFeedsreset();
   afx_msg void      OnSrvfeeds();
   afx_msg void      OnFeederlog();
   afx_msg void      OnConfigRequest();
   afx_msg void      OnConfigUp();
   afx_msg void      OnConfigDown();
   afx_msg void      OnConfigUpdate();
   afx_msg void      OnConfigDelete();
   afx_msg void      OnChartRequest();
   afx_msg void      OnChartUpdate();
   afx_msg void      OnChartDelete();
   afx_msg void      OnChartAdd();
   afx_msg void      OnPerformance();
   afx_msg void      OnBackupUsers();
   afx_msg void      OnBackupOrders();
   afx_msg void      OnBackupRequest();
   afx_msg void      OnBackupRestore();
   afx_msg void      OnBaseUsers();
   afx_msg void      OnBaseOrders();
   afx_msg void      OnUsersCheck();
   afx_msg void      OnUsersFix();
   afx_msg void      OnOrdersModify();
   afx_msg void      OnOrdersDelete();
   //}}AFX_MSG
   DECLARE_MESSAGE_MAP()
   //---
   void              DisplayRes(const int res,LPCSTR title);
   void              Free();
   void              DisplayServerFeeds();
   void              DisplayCommon(const int res);
   void              DisplayTime(const int res);
   void              DisplayBackup(const int res);
   void              DisplaySecurity(const int res);
   void              DisplayAccess();
   void              DisplayDataSrv();
   void              DisplayHoliday();
   void              DisplaySymbols();
   void              DisplayGroups();
   void              DisplayManagers();
   void              DisplayFeeders();
   void              DisplayLiveUpdate();
   void              DisplaySynchro();
   void              DisplayPlugins();
   void              DisplayAccounts();
   void              DisplayMarkups();
   void              DisplayRules();
   //---
   void              DisplayRates();
   void              DisplayPerformance();
   void              DisplayBackups();
   void              DisplayUsers(const int type);
   void              DisplayOrders(const int type);
   //---
   void              ConfigShift(const int shift);
  };
//{{AFX_INSERT_LOCATION}}
//+------------------------------------------------------------------+
