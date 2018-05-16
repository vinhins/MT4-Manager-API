//+------------------------------------------------------------------+
//|                                      MetaTrader Manager API Test |
//|                   Copyright 2001-2014, MetaQuotes Software Corp. |
//|                                        http://www.metaquotes.net |
//+------------------------------------------------------------------+
#include "stdafx.h"
#include "ManagerAPITest.h"
#include "ManagerAPITestDlg.h"
#include "NewPassDlg.h"
#include "common\Common.h"

//+------------------------------------------------------------------+
//|                                                                  |
//+------------------------------------------------------------------+
CManagerAPITestDlg::CManagerAPITestDlg(CWnd *pParent) : CDialog(CManagerAPITestDlg::IDD, pParent),
                    #ifdef _WIN64
                    //m_factory("..\\..\\API\\mtmanapi64.dll"),
                    m_factory("mtmanapi64.dll"),
                    #else
                    //m_factory("..\\..\\API\\mtmanapi.dll"),
                    m_factory("mtmanapi.dll"),
                    #endif
                    m_manager(NULL),
                    m_total(0),m_feeds(NULL),m_feed_log(NULL),
                    m_access(NULL),m_datasrv(NULL),m_holiday(NULL),m_symbols(NULL),m_groups(NULL),
                    m_managers(NULL),m_feeders(NULL),m_liveupdate(NULL),m_synchro(NULL),m_plugins(NULL),
                    m_gateway_accounts(NULL),m_gateway_markups(NULL),m_gateway_rules(NULL),
                    m_rates(NULL),m_digits(4),m_performance(NULL),m_backups(NULL),
                    m_users(NULL),m_trades(NULL)
  {
   //{{AFX_DATA_INIT(CManagerAPITestDlg)
   //}}AFX_DATA_INIT
   m_hIcon=AfxGetApp()->LoadIcon(IDR_MAINFRAME);
   memset(&m_common,0,sizeof(m_common));
   memset(&m_time,  0,sizeof(m_time));
   memset(&m_backup,0,sizeof(m_backup));
   memset(m_security,0,sizeof(m_security));
   memset(&m_chart,0,sizeof(m_chart));
   m_display_type=CONFIG_ALL;
  }
//+------------------------------------------------------------------+
//|                                                                  |
//+------------------------------------------------------------------+
void CManagerAPITestDlg::DoDataExchange(CDataExchange* pDX)
  {
   CDialog::DoDataExchange(pDX);
   //{{AFX_DATA_MAP(CManagerAPITestDlg)
   DDX_Control(pDX, IDC_BASE_GROUP, m_BaseGroup);
   DDX_Control(pDX, IDC_BACKUP, m_Backup);
   DDX_Control(pDX, IDC_PERIOD, m_Period);
   DDX_Control(pDX, IDC_SYMBOL, m_Symbol);
   DDX_Control(pDX, IDC_CONFIG, m_Config);
   DDX_Control(pDX, IDC_FEEDER, m_Feeder);
   DDX_Control(pDX, IDC_RESULTS, m_Results);
   DDX_Control(pDX, IDC_SERVER, m_Server);
   DDX_Control(pDX, IDC_PASSWORD, m_Password);
   DDX_Control(pDX, IDC_LOGIN, m_Login);
   //}}AFX_DATA_MAP
  }
//+------------------------------------------------------------------+
//|                                                                  |
//+------------------------------------------------------------------+
BEGIN_MESSAGE_MAP(CManagerAPITestDlg, CDialog)
   //{{AFX_MSG_MAP(CManagerAPITestDlg)
   ON_WM_PAINT()
   ON_WM_QUERYDRAGICON()
   ON_WM_DESTROY()
   ON_BN_CLICKED(IDC_CONNECT, OnConnect)
   ON_BN_CLICKED(IDC_LOGINCMD, OnLogincmd)
   ON_BN_CLICKED(IDC_DISCONNECT, OnDisconnect)
   ON_BN_CLICKED(IDC_PING, OnPing)
   ON_BN_CLICKED(IDC_PASS_CHANGE, OnPassChange)
   ON_BN_CLICKED(IDC_RESTART, OnRestart)
   ON_BN_CLICKED(IDC_CHARTSYNC, OnChartsync)
   ON_BN_CLICKED(IDC_LIVEUPDATE, OnLiveupdate)
   ON_BN_CLICKED(IDC_FEEDSRESET, OnFeedsreset)
   ON_BN_CLICKED(IDC_SRVFEEDS, OnSrvfeeds)
   ON_BN_CLICKED(IDC_FEEDERLOG, OnFeederlog)
   ON_BN_CLICKED(IDC_CONFIG_REQUEST, OnConfigRequest)
   ON_BN_CLICKED(IDC_CONFIG_UP, OnConfigUp)
   ON_BN_CLICKED(IDC_CONFIG_DOWN, OnConfigDown)
   ON_BN_CLICKED(IDC_CONFIG_UPDATE, OnConfigUpdate)
   ON_BN_CLICKED(IDC_CONFIG_DELETE, OnConfigDelete)
   ON_BN_CLICKED(IDC_CHART_REQUEST, OnChartRequest)
   ON_BN_CLICKED(IDC_CHART_UPDATE, OnChartUpdate)
   ON_BN_CLICKED(IDC_CHART_DELETE, OnChartDelete)
   ON_BN_CLICKED(IDC_CHART_ADD, OnChartAdd)
   ON_BN_CLICKED(IDC_PERFORMANCE, OnPerformance)
   ON_BN_CLICKED(IDC_BACKUP_USERS, OnBackupUsers)
   ON_BN_CLICKED(IDC_BACKUP_ORDERS, OnBackupOrders)
   ON_BN_CLICKED(IDC_BACKUP_REQUEST, OnBackupRequest)
   ON_BN_CLICKED(IDC_BACKUP_RESTORE, OnBackupRestore)
   ON_BN_CLICKED(IDC_BASE_USERS, OnBaseUsers)
   ON_BN_CLICKED(IDC_BASE_ORDERS, OnBaseOrders)
   ON_BN_CLICKED(IDC_USERS_CHECK, OnUsersCheck)
   ON_BN_CLICKED(IDC_USERS_FIX, OnUsersFix)
   ON_BN_CLICKED(IDC_ORDERS_MODIFY, OnOrdersModify)
   ON_BN_CLICKED(IDC_ORDERS_DELETE, OnOrdersDelete)
   //}}AFX_MSG_MAP
END_MESSAGE_MAP()
//+------------------------------------------------------------------+
//|                                                                  |
//+------------------------------------------------------------------+
BOOL CManagerAPITestDlg::OnInitDialog()
  {
   CDialog::OnInitDialog();
//---
   SetIcon(m_hIcon,TRUE);         // Set big icon
   SetIcon(m_hIcon,FALSE);         // Set small icon
//--- create manager api instance
   if(m_factory.IsValid()==FALSE || (m_manager=m_factory.Create(ManAPIVersion))==NULL)
     {
      MessageBox("Failed to create manager interface","Manager API Test");
      EndDialog(IDCANCEL);
      return(FALSE);
     }

   m_manager->LogsMode(LOG_MODE_DISABLED);
//---
   m_Server.SetWindowText("localhost:443");
   m_Login.SetWindowText("11");
   m_Password.SetWindowText("Manager11");
   m_Password.LimitText(16);
   m_Results.SetExtendedStyle(LVS_EX_FULLROWSELECT);
   m_Config.SetCurSel(0);
//---
   m_Period.SetItemData(0,PERIOD_M1);
   m_Period.SetItemData(1,PERIOD_M5);
   m_Period.SetItemData(2,PERIOD_M15);
   m_Period.SetItemData(3,PERIOD_M30);
   m_Period.SetItemData(4,PERIOD_H1);
   m_Period.SetItemData(5,PERIOD_H4);
   m_Period.SetItemData(6,PERIOD_D1);
   m_Period.SetItemData(7,PERIOD_W1);
   m_Period.SetItemData(8,PERIOD_MN1);
   m_Period.SetCurSel(4);
   m_chart.period=int(m_Period.GetItemData(4));
//---
   m_BaseGroup.SetCurSel(0);
//---
   return(TRUE);
  }
//+------------------------------------------------------------------+
//|                                                                  |
//+------------------------------------------------------------------+
void CManagerAPITestDlg::OnDestroy()
  {
   Free();
//---
   if(m_manager!=NULL)
     {
      if(m_manager->IsConnected()!=FALSE) m_manager->Disconnect();
      m_manager->Release();
      m_manager=NULL;
     }
//---
   CDialog::OnDestroy();
  }
//+------------------------------------------------------------------+
//| If you add a minimize button to your dialog, you will need the   |
//|  code below to draw the icon.  For MFC applications using        |
//|  the document/view model, this is automatically done             |
//|  for you by the framework.                                       |
//+------------------------------------------------------------------+
void CManagerAPITestDlg::OnPaint()
  {
   if(IsIconic())
     {
      CPaintDC dc(this); // device context for painting
      SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);
      // Center icon in client rectangle
      int cxIcon=GetSystemMetrics(SM_CXICON);
      int cyIcon=GetSystemMetrics(SM_CYICON);
      CRect rect;
      GetClientRect(&rect);
      int x=(rect.Width() -cxIcon+1)/2;
      int y=(rect.Height()-cyIcon+1)/2;
      // Draw the icon
      dc.DrawIcon(x, y, m_hIcon);
     }
   else
     {
      CDialog::OnPaint();
     }
  }
//+------------------------------------------------------------------+
//| The system calls this to obtain the cursor to display            |
//| while the user drags the minimized window.                       |
//+------------------------------------------------------------------+
HCURSOR CManagerAPITestDlg::OnQueryDragIcon()
  {
   return(HCURSOR)m_hIcon;
  }
//+------------------------------------------------------------------+
//|                                                                  |
//+------------------------------------------------------------------+
void CManagerAPITestDlg::DisplayRes(const int res,LPCSTR title)
  {
   if(m_manager && title)
      MessageBox(m_manager->ErrorDescription(res),title);
  }
//+------------------------------------------------------------------+
//|                                                                  |
//+------------------------------------------------------------------+
void CManagerAPITestDlg::Free()
  {
   if(m_feeds      !=NULL) { m_manager->MemFree(m_feeds);      m_feeds      =NULL; }
   if(m_feed_log   !=NULL) { m_manager->MemFree(m_feed_log);   m_feed_log   =NULL; }
   if(m_access     !=NULL) { m_manager->MemFree(m_access);     m_access     =NULL; }
   if(m_datasrv    !=NULL) { m_manager->MemFree(m_datasrv);    m_datasrv    =NULL; }
   if(m_holiday    !=NULL) { m_manager->MemFree(m_holiday);    m_holiday    =NULL; }
   if(m_symbols    !=NULL) { m_manager->MemFree(m_symbols);    m_symbols    =NULL; }
   if(m_groups     !=NULL) { m_manager->MemFree(m_groups);     m_groups     =NULL; }
   if(m_managers   !=NULL) { m_manager->MemFree(m_managers);   m_managers   =NULL; }
   if(m_feeders    !=NULL) { m_manager->MemFree(m_feeders);    m_feeders    =NULL; }
   if(m_liveupdate !=NULL) { m_manager->MemFree(m_liveupdate); m_liveupdate =NULL; }
   if(m_synchro    !=NULL) { m_manager->MemFree(m_synchro);    m_synchro    =NULL; }
   if(m_plugins    !=NULL)
     {
      for(int i=0;i<m_total;i++)
         if(m_plugins[i].params!=NULL)
           {
            m_manager->MemFree(m_plugins->params);
            m_plugins->params=NULL;
           }
      m_manager->MemFree(m_plugins);
      m_plugins=NULL;
     }
   if(m_gateway_accounts!=NULL) { m_manager->MemFree(m_gateway_accounts); m_gateway_accounts=NULL; }
   if(m_gateway_markups!=NULL)  { m_manager->MemFree(m_gateway_markups);  m_gateway_markups =NULL; }
   if(m_gateway_rules!=NULL)    { m_manager->MemFree(m_gateway_rules);    m_gateway_rules=NULL;    }
   if(m_rates      !=NULL) { m_manager->MemFree(m_rates);      m_rates      =NULL; }
   if(m_performance!=NULL) { m_manager->MemFree(m_performance);m_performance=NULL; }
   if(m_backups    !=NULL) { m_manager->MemFree(m_backups);    m_backups    =NULL; }
   if(m_users      !=NULL) { m_manager->MemFree(m_users);      m_users      =NULL; }
   if(m_trades     !=NULL) { m_manager->MemFree(m_trades);     m_trades     =NULL; }
   m_total=0;
  }
//+------------------------------------------------------------------+
//| Connect                                                          |
//+------------------------------------------------------------------+
void CManagerAPITestDlg::OnConnect()
  {
   char server[256]="";
   int  res=RET_ERROR;
//---
   m_Server.GetWindowText(server,sizeof(server)-1);
   if(server[0]==0) return;
   res=m_manager->Connect(server);
//---
   DisplayRes(res,"Connect");
  }
//+------------------------------------------------------------------+
//| Login                                                            |
//+------------------------------------------------------------------+
void CManagerAPITestDlg::OnLogincmd()
  {
   int  res=RET_ERROR,login=0;
   char pass[16]="";
   char tmp[256]="";
//---
   login=GetDlgItemInt(m_Login.GetDlgCtrlID(),NULL,FALSE);
   m_Password.GetWindowText(pass,sizeof(pass)-1);
   if(login<=0 || pass[0]==0) return;
   res=m_manager->Login(login,pass);
   if(res==RET_SECURITY_SESSION)
     {
      _snprintf(tmp,sizeof(tmp)-1,"%s\\rsa.key",ExtProgramPath);
      res=m_manager->LoginSecured(tmp);
     }
//---
   DisplayRes(res,"Login");
  }
//+------------------------------------------------------------------+
//| Disconnect                                                       |
//+------------------------------------------------------------------+
void CManagerAPITestDlg::OnDisconnect()
  {
//---
   int res=m_manager->Disconnect();
//---
   DisplayRes(res,"Disconnect");
  }
//+------------------------------------------------------------------+
//| Ping                                                             |
//+------------------------------------------------------------------+
void CManagerAPITestDlg::OnPing()
  {
//---
   int res=m_manager->Ping();
   DisplayRes(res,"Ping");
//---
  }
//+------------------------------------------------------------------+
//| Change self password                                             |
//+------------------------------------------------------------------+
void CManagerAPITestDlg::OnPassChange()
  {
   char        newpass[16];
   int         investor=FALSE,res=RET_ERROR;
   CNewPassDlg dlg;
//---
   if(dlg.DoModal()!=IDOK) return;
   investor=dlg.PassGet(newpass);
   res=m_manager->PasswordChange(newpass,investor);
   if(res==RET_OK) m_Password.SetWindowText(newpass);
//---
   DisplayRes(res,"PasswordChange");
  }
//+------------------------------------------------------------------+
//| Administration commands                                          |
//+------------------------------------------------------------------+
void CManagerAPITestDlg::OnRestart()
  {
//---
   int res=m_manager->SrvRestart();
   DisplayRes(res,"SrvRestart");
//---
  }
//+------------------------------------------------------------------+
//|                                                                  |
//+------------------------------------------------------------------+
void CManagerAPITestDlg::OnChartsync()
  {
//---
   int res=m_manager->SrvChartsSync();
   DisplayRes(res,"SrvChartsSync");
//---
  }
//+------------------------------------------------------------------+
//|                                                                  |
//+------------------------------------------------------------------+
void CManagerAPITestDlg::OnLiveupdate()
  {
//---
   int res=m_manager->SrvLiveUpdateStart();
   DisplayRes(res,"SrvLiveUpdateStart");
//---
  }
//+------------------------------------------------------------------+
//|                                                                  |
//+------------------------------------------------------------------+
void CManagerAPITestDlg::OnFeedsreset()
  {
//---
   int res=m_manager->SrvFeedsRestart();
   DisplayRes(res,"SrvFeedsRestart");
//---
  }
//+------------------------------------------------------------------+
//| Request server datafeeds                                         |
//+------------------------------------------------------------------+
void CManagerAPITestDlg::OnSrvfeeds()
  {
   Free();
   m_feeds=m_manager->SrvFeeders(&m_total);
   DisplayServerFeeds();
  }
//+------------------------------------------------------------------+
//| Display server datafeeds                                         |
//+------------------------------------------------------------------+
void CManagerAPITestDlg::DisplayServerFeeds()
  {
   CRect rc;
   int   cx=10;
//---
   if(m_feeds==NULL) return;
//---
   m_display_type=CONFIG_ALL;
   m_Results.GetClientRect(&rc);
   cx=(rc.Width()-::GetSystemMetrics(SM_CXVSCROLL))/3;
   m_Results.ModifyStyle(LVS_NOCOLUMNHEADER,0);
//---
   m_Results.DeleteAllItems();
   while(m_Results.DeleteColumn(0)!=0) ;
   m_Results.InsertColumn(0,"File",LVCFMT_LEFT,cx);
   m_Results.InsertColumn(1,"Name",LVCFMT_LEFT,cx);
   m_Results.InsertColumn(2,"Server",LVCFMT_LEFT,cx);
//---
   for(int i=0; i<m_total; i++)
     {
      m_Results.InsertItem(i,m_feeds[i].file);
      m_Results.SetItemText(i,1,m_feeds[i].feed.name);
      m_Results.SetItemText(i,2,m_feeds[i].feed.server);
     }
//---
  }
//+------------------------------------------------------------------+
//| Request datafeed log                                             |
//+------------------------------------------------------------------+
void CManagerAPITestDlg::OnFeederlog()
  {
   char  name[64]="",tmp[256]="",npad[256]="";
   char *logs=NULL;
   int   len=0;
   FILE *out=NULL;
//---
   Free();
//---
   m_Feeder.GetWindowText(name,sizeof(name)-1);
   if(name[0]==0) { ::MessageBeep(-1); return; }
//---
   logs=m_manager->SrvFeederLog(name,&len);
   if(len>0)
     {
      _snprintf(tmp,sizeof(tmp)-1,"%s\\logs\\%s.log",ExtProgramPath,name);
      if((out=fopen(tmp,"wb"))!=NULL)
        {
         fwrite(logs,1,len,out);
         fclose(out); out=NULL;
         //--- просмотр
         ::GetWindowsDirectory(npad,sizeof(npad)-1);
         strcat(npad,"\\notepad.exe");
         if(::ShellExecute(NULL,NULL,npad,tmp,NULL,SW_SHOW)<=(HINSTANCE)32)
           {
            _snprintf(tmp,sizeof(tmp)-1,"%s\\logs",ExtProgramPath);
            ::ShellExecute(NULL,NULL,tmp,NULL,NULL,SW_SHOW);
           }
        }
     }
   else
      MessageBox("Empty log",name);
//---
   if(logs!=NULL)
     {
      m_manager->MemFree(logs);
      logs=NULL;
      len=0;
     }
  }
//+------------------------------------------------------------------+
//|                                                                  |
//+------------------------------------------------------------------+
void CManagerAPITestDlg::OnConfigRequest()
  {
   int type=m_Config.GetCurSel()+1;
   int res=RET_ERROR;
//---
   Free();
//---
   switch(type)
     {
      case CONFIG_COMMON:      res=m_manager->CfgRequestCommon(&m_common);          DisplayCommon(res);   break;
      case CONFIG_TIME:        res=m_manager->CfgRequestTime(&m_time);              DisplayTime(res);     break;
      case CONFIG_BACKUP:      res=m_manager->CfgRequestBackup(&m_backup);          DisplayBackup(res);   break;
      case CONFIG_SYMB_GROUPS: res=m_manager->CfgRequestSymbolGroup(m_security);    DisplaySecurity(res); break;
      case CONFIG_ACCESS:      m_access =m_manager->CfgRequestAccess(&m_total);     DisplayAccess();      break;
      case CONFIG_SERVERS:     m_datasrv=m_manager->CfgRequestDataServer(&m_total); DisplayDataSrv();     break;
      case CONFIG_HOLIDAYS:    m_holiday=m_manager->CfgRequestHoliday(&m_total);    DisplayHoliday();     break;
      case CONFIG_SYMBOLS:     m_symbols=m_manager->CfgRequestSymbol(&m_total);     DisplaySymbols();     break;
      case CONFIG_GROUPS:      m_groups  =m_manager->CfgRequestGroup(&m_total);     DisplayGroups();      break;
      case CONFIG_MANAGERS:    m_managers=m_manager->CfgRequestManager(&m_total);   DisplayManagers();    break;
      case CONFIG_DATAFEEDS:   m_feeders =m_manager->CfgRequestFeeder(&m_total);    DisplayFeeders();     break;
      case CONFIG_PLUGINS:     m_plugins =m_manager->CfgRequestPlugin(&m_total);    DisplayPlugins();     break;
      case CONFIG_LIVEUPDATE:  m_liveupdate=m_manager->CfgRequestLiveUpdate(&m_total); DisplayLiveUpdate();  break;
      case CONFIG_SYNC:        m_synchro =m_manager->CfgRequestSync(&m_total);      DisplaySynchro();     break;
      case CONFIG_GATEWAY_ACCOUNTS:     m_gateway_accounts=m_manager->CfgRequestGatewayAccount(&m_total); DisplayAccounts();  break;
      case CONFIG_GATEWAY_MARKUPS:      m_gateway_markups =m_manager->CfgRequestGatewayMarkup(&m_total);  DisplayMarkups();   break;
      case CONFIG_GATEWAY_RULES:        m_gateway_rules   =m_manager->CfgRequestGatewayRule(&m_total);    DisplayRules();     break;

      default:
         break;
     }
//---
  }
//+------------------------------------------------------------------+
//|                                                                  |
//+------------------------------------------------------------------+
void CManagerAPITestDlg::DisplayCommon(const int res)
  {
   CRect   rc;
   int     cx=10;
   CString str;
//---
   if(res!=RET_OK) { DisplayRes(res,"ConCommon"); return; }
//---
   m_display_type=CONFIG_COMMON;
   m_Results.GetClientRect(&rc);
   cx=(rc.Width()-::GetSystemMetrics(SM_CXVSCROLL))/4;
   m_Results.ModifyStyle(LVS_NOCOLUMNHEADER,0);
//---
   m_Results.DeleteAllItems();
   while(m_Results.DeleteColumn(0)!=0) ;
   m_Results.InsertColumn(0,"Property",LVCFMT_LEFT,cx);
   m_Results.InsertColumn(1,"Value",LVCFMT_LEFT,cx*3);
//---
   m_Results.InsertItem(0,"Owner");   m_Results.SetItemText(0,1,m_common.owner);
   m_Results.InsertItem(1,"Name");    m_Results.SetItemText(1,1,m_common.name);
   m_Results.InsertItem(2,"Address"); str=inet_ntoa(*(in_addr*)&m_common.address); m_Results.SetItemText(2,1,str);
   m_Results.InsertItem(3,"Port");    str.Format("%d",m_common.port);    m_Results.SetItemText(3,1,str);
   m_Results.InsertItem(4,"Socket timeout"); str.Format("%u sec",m_common.timeout); m_Results.SetItemText(4,1,str);
   m_Results.InsertItem(5,"Time of demo");   str.Format("%d days",m_common.timeofdemo); m_Results.SetItemText(5,1,str);
   m_Results.InsertItem(6,"Type of demo");
   switch(m_common.typeofdemo)
     {
      case DEMO_DISABLED: m_Results.SetItemText(6,1,"Disabled");                    break;
      case DEMO_PROLONG:  m_Results.SetItemText(6,1,"Prolong from the last login"); break;
      case DEMO_FIXED:    m_Results.SetItemText(6,1,"With fixed period");           break;
     }
   m_Results.InsertItem(7,"Timezone");       str.Format("GMT%+.02d:00",m_common.timezone); m_Results.SetItemText(7,1,str);
   m_Results.InsertItem(8,"Daylight correction"); m_Results.SetItemText(8,1,m_common.daylightcorrection?"Yes":"No");
   m_Results.InsertItem(9,"End of day time"); str.Format("%02d:%02d",m_common.endhour,m_common.endminute); m_Results.SetItemText(9,1,str);
   m_Results.InsertItem(10,"Rollover mode");
   switch(m_common.rollovers_mode)
     {
      case ROLLOVER_NORMAL:                m_Results.SetItemText(10,1,"Normal");                break;
      case ROLLOVER_REOPEN_BY_CLOSE_PRICE: m_Results.SetItemText(10,1,"Reopen by close price"); break;
      case ROLLOVER_REOPEN_BY_BID:         m_Results.SetItemText(10,1,"Reopen by bid");         break;
     }
   m_Results.InsertItem(11,"Keep emails");   str.Format("%d days",m_common.keepemails); m_Results.SetItemText(11,1,str);
   m_Results.InsertItem(12,"Optimization time"); str.Format("%02d:%02d",m_common.optimization_time/60,m_common.optimization_time%60); m_Results.SetItemText(12,1,str);
   m_Results.InsertItem(13,"Min. client");   str.Format("%d",m_common.minclient); m_Results.SetItemText(13,1,str);
   m_Results.InsertItem(14,"Min. API");      str.Format("%d",m_common.minapi); m_Results.SetItemText(14,1,str);
   m_Results.InsertItem(15,"Antiflood");     m_Results.SetItemText(15,1,m_common.antiflood?"Yes":"No");
   m_Results.InsertItem(16,"Antiflood max"); str.Format("%d",m_common.floodcontrol); m_Results.SetItemText(16,1,str);
   m_Results.InsertItem(17,"Feeder timeout");   str.Format("%u sec",m_common.feeder_timeout); m_Results.SetItemText(17,1,str);
   m_Results.InsertItem(18,"LiveUpdate mode");
   switch(m_common.liveupdate_mode)
     {
      case LIVE_UPDATE_NO:        m_Results.SetItemText(18,1,"Disabled");       break;
      case LIVE_UPDATE_RELEASE:   m_Results.SetItemText(18,1,"Release");        break;
      case LIVE_UPDATE_NO_SERVER: m_Results.SetItemText(18,1,"Without server"); break;
      case LIVE_UPDATE_BETA:      m_Results.SetItemText(18,1,"Release and Beta"); break;
     }
   m_Results.InsertItem(19,"Time sync with");   m_Results.SetItemText(19,1,m_common.timesync);
   m_Results.InsertItem(20,"Database path"); m_Results.SetItemText(20,1,m_common.path_database);
   m_Results.InsertItem(21,"History path");  m_Results.SetItemText(21,1,m_common.path_history);
   m_Results.InsertItem(22,"Logs path");     m_Results.SetItemText(22,1,m_common.path_log);
   m_Results.InsertItem(23,"Network");       m_Results.SetItemText(23,1,m_common.adapters);
//---
  }
//+------------------------------------------------------------------+
//|                                                                  |
//+------------------------------------------------------------------+
void CManagerAPITestDlg::DisplayTime(const int res)
  {
   CRect   rc;
   int     cx=10;
   CString strTime;
   char    szHour[256];
   int     d,h,h1st;
//---
   if(res!=RET_OK) { DisplayRes(res,"ConTime"); return; }
//---
   m_display_type=CONFIG_TIME;
   m_Results.GetClientRect(&rc);
   cx=(rc.Width()-::GetSystemMetrics(SM_CXVSCROLL))/4;
   m_Results.ModifyStyle(LVS_NOCOLUMNHEADER,0);
//---
   m_Results.DeleteAllItems();
   while(m_Results.DeleteColumn(0)!=0) ;
   m_Results.InsertColumn(0,"Day",LVCFMT_LEFT,cx);
   m_Results.InsertColumn(1,"Time",LVCFMT_LEFT,cx*3);
//---
   m_Results.InsertItem(0,"Sunday");
   m_Results.InsertItem(1,"Monday");
   m_Results.InsertItem(2,"Tuesday");
   m_Results.InsertItem(3,"Wednesday");
   m_Results.InsertItem(4,"Thursday");
   m_Results.InsertItem(5,"Friday");
   m_Results.InsertItem(6,"Saturday");
//---
   for(d=0; d<7; d++)
     {
      strTime.Empty();
      szHour[0]=0;
      h=0; h1st=0;
      while(h<24)
        {
         for(; h<24; h++) if(m_time.days[d][h]) break;
         if(24<=h) break;
         h1st=h;
         _snprintf(szHour,sizeof(szHour)-1,"%02d:00",h);
         strTime+=szHour;
         for(++h; m_time.days[d][h] && h<24; h++)
            ;
         if(h1st!=h)
           {
            _snprintf(szHour,sizeof(szHour)-1,"-%02d:00",h);
            strTime+=szHour;
           }
         strTime+=", ";
        }
      if(strTime.GetLength()>0) strTime.SetAt(strTime.GetLength()-2,'\0');
      m_Results.SetItemText(d,1,(LPCTSTR)strTime);
     }
//---
  }
//+------------------------------------------------------------------+
//|                                                                  |
//+------------------------------------------------------------------+
void CManagerAPITestDlg::DisplayBackup(const int res)
  {
   static LPCSTR sfull[3]       ={ "1 hour","4 hours","1 day" };
   static LPCSTR sfull_store[4] ={ "1 month","3 months","6 months","1 year" };
   static LPCSTR sbrief[4]      ={ "5min","15 min","30 min","1 hour" };
   static LPCSTR sbrief_store[7]={ "1 day","3 days","1 week","2 weeks","1 month","3 months","6 months" };
   static LPCSTR sexternal[5]   ={ "1 min","5 min","15 min","30 min","1 hour" };
   CRect   rc;
   int     cx=10;
   CString str;
//---
   if(res!=RET_OK) { DisplayRes(res,"ConBackup"); return; }
//---
   m_display_type=CONFIG_BACKUP;
   m_Results.GetClientRect(&rc);
   cx=(rc.Width()-::GetSystemMetrics(SM_CXVSCROLL))/3;
   m_Results.ModifyStyle(LVS_NOCOLUMNHEADER,0);
//---
   m_Results.DeleteAllItems();
   while(m_Results.DeleteColumn(0)!=0) ;
   m_Results.InsertColumn(0,"Property",LVCFMT_LEFT,cx);
   m_Results.InsertColumn(1,"Value",LVCFMT_LEFT,cx*2);
//---
   m_Results.InsertItem(0,"Full backup to"); m_Results.SetItemText(0,1,m_backup.fullbackup_path);
   m_Results.InsertItem(1,"Full backup every"); m_Results.SetItemText(1,1,sfull[m_backup.fullbackup_period]);
   m_Results.InsertItem(2,"Full backup time"); str.Format(_T("%02d:%02d"),m_backup.fullbackup_shift/60,m_backup.fullbackup_shift%60); m_Results.SetItemText(2,1,str);
   m_Results.InsertItem(3,"Store full backup for"); m_Results.SetItemText(3,1,sfull_store[m_backup.fullbackup_store]);
   m_Results.InsertItem(4,"Last full backup"); FormatDateTime(m_backup.fullbackup_lasttime,str); m_Results.SetItemText(4,1,str);
   m_Results.InsertItem(5,"Archive backup every"); m_Results.SetItemText(5,1,sbrief[m_backup.archive_period]);
   m_Results.InsertItem(6,"Store archive backup for"); m_Results.SetItemText(6,1,sbrief_store[m_backup.archive_store]);
   m_Results.InsertItem(7,"Archive backup external processing"); m_Results.SetItemText(7,1,m_backup.external_path);
   m_Results.InsertItem(8,"Last archive backup");  FormatDateTime(m_backup.archive_lasttime,str); m_Results.SetItemText(8,1,str);
   m_Results.InsertItem(9,"Export securities");    m_Results.SetItemText(9,1,m_backup.export_securities);
   m_Results.InsertItem(10,"Export external processing period"); m_Results.SetItemText(10,1,sexternal[m_backup.export_period]);
   m_Results.InsertItem(11,"Export external processing");   m_Results.SetItemText(11,1,m_backup.export_path);
   m_Results.InsertItem(12,"Last export processing"); FormatDateTime(m_backup.export_lasttime,str); m_Results.SetItemText(12,1,str);
  }
//+------------------------------------------------------------------+
//|                                                                  |
//+------------------------------------------------------------------+
void CManagerAPITestDlg::DisplayAccess()
  {
   CRect   rc;
   int     cx=10;
   CString str;
   ULONG   ip=0;
//---
   if(m_access==NULL) return;
//---
   m_display_type=CONFIG_ACCESS;
   m_Results.GetClientRect(&rc); cx=(rc.Width()-::GetSystemMetrics(SM_CXVSCROLL))/3;
   m_Results.ModifyStyle(LVS_NOCOLUMNHEADER,0);
//---
   m_Results.DeleteAllItems();
   while(m_Results.DeleteColumn(0)!=0) ;
   m_Results.InsertColumn(0,"From",LVCFMT_LEFT,cx);
   m_Results.InsertColumn(1,"To",LVCFMT_LEFT,cx);
   m_Results.InsertColumn(2,"Comment",LVCFMT_LEFT,cx);
//---
   for(int i=0; i<m_total; i++)
     {
      ip=ntohl(m_access[i].from);
      str=inet_ntoa(*(in_addr*)&ip);
      m_Results.InsertItem(i,str);
      ip=ntohl(m_access[i].to);
      str=inet_ntoa(*(in_addr*)&ip);
      m_Results.SetItemText(i,1,str);
      m_Results.SetItemText(i,2,m_access[i].comment);
     }
//---
  }
//+------------------------------------------------------------------+
//|                                                                  |
//+------------------------------------------------------------------+
void CManagerAPITestDlg::DisplayDataSrv()
  {
   CRect   rc;
   int     cx=10;
   CString str;
//---
   if(m_datasrv==NULL) return;
//---
   m_display_type=CONFIG_SERVERS;
   m_Results.GetClientRect(&rc); cx=(rc.Width()-::GetSystemMetrics(SM_CXVSCROLL))/4;
   m_Results.ModifyStyle(LVS_NOCOLUMNHEADER,0);
//---
   m_Results.DeleteAllItems();
   while(m_Results.DeleteColumn(0)!=0) ;
   m_Results.InsertColumn(0,"Server",LVCFMT_LEFT,cx);
   m_Results.InsertColumn(1,"Description",LVCFMT_LEFT,cx);
   m_Results.InsertColumn(2,"Priority",LVCFMT_LEFT,cx);
   m_Results.InsertColumn(3,"Loading",LVCFMT_LEFT,cx);
//---
   for(int i=0; i<m_total; i++)
     {
      m_Results.InsertItem(i,m_datasrv[i].server);
      m_Results.SetItemText(i,1,m_datasrv[i].description);
      str.Format("%d",m_datasrv[i].priority); m_Results.SetItemText(i,2,str);
      if(m_datasrv[i].loading<0) str.Format("%u",m_datasrv[i].loading);
      else str="n/a";
      m_Results.SetItemText(i,3,str);
     }
//---
  }
//+------------------------------------------------------------------+
//|                                                                  |
//+------------------------------------------------------------------+
void CManagerAPITestDlg::DisplayHoliday()
  {
   CRect   rc;
   int     cx=10;
   CString str;
//---
   if(m_holiday==NULL) return;
//---
   m_display_type=CONFIG_HOLIDAYS;
   m_Results.GetClientRect(&rc); cx=(rc.Width()-::GetSystemMetrics(SM_CXVSCROLL))/3;
   m_Results.ModifyStyle(LVS_NOCOLUMNHEADER,0);
//---
   m_Results.DeleteAllItems();
   while(m_Results.DeleteColumn(0)!=0) ;
   m_Results.InsertColumn(0,"Day",LVCFMT_LEFT,cx);
   m_Results.InsertColumn(1,"Securities",LVCFMT_LEFT,cx);
   m_Results.InsertColumn(2,"Description",LVCFMT_LEFT,cx);
//---
   for(int i=0; i<m_total; i++)
     {
      if(m_holiday[i].year==0) str.Format("****.%02d.%02d",m_holiday[i].month,m_holiday[i].day);
      else                     str.Format("%04d.%02d.%02d",m_holiday[i].year,m_holiday[i].month,m_holiday[i].day);
      m_Results.InsertItem(i,str);
      m_Results.SetItemText(i,1,m_holiday[i].symbol);
      m_Results.SetItemText(i,2,m_holiday[i].description);
     }
//---
  }
//+------------------------------------------------------------------+
//|                                                                  |
//+------------------------------------------------------------------+
void CManagerAPITestDlg::DisplaySymbols()
  {
   static  LPCSTR modes[3]={ "No","Close only","Full" };
   CRect   rc;
   int     cx=10;
   CString str;
//---
   if(m_symbols==NULL) return;
//---
   m_display_type=CONFIG_SYMBOLS;
   m_Results.GetClientRect(&rc); cx=(rc.Width()-::GetSystemMetrics(SM_CXVSCROLL))/4;
   m_Results.ModifyStyle(LVS_NOCOLUMNHEADER,0);
//---
   m_Results.DeleteAllItems();
   while(m_Results.DeleteColumn(0)!=0) ;
   m_Results.InsertColumn(0,"Symbol",LVCFMT_LEFT,cx);
   m_Results.InsertColumn(1,"Type",LVCFMT_LEFT,cx);
   m_Results.InsertColumn(2,"Digits",LVCFMT_LEFT,cx);
   m_Results.InsertColumn(3,"Trade",LVCFMT_LEFT,cx);
//---
   while(m_Symbol.DeleteString(0)>0) ;
   for(int i=0; i<m_total; i++)
     {
      m_Results.InsertItem(i,m_symbols[i].symbol);
      str.Format("%d",m_symbols[i].type);   m_Results.SetItemText(i,1,str);
      str.Format("%d",m_symbols[i].digits); m_Results.SetItemText(i,2,str);
      m_Results.SetItemText(i,3,modes[m_symbols[i].trade]);
      //---
      m_Symbol.SetItemData(m_Symbol.AddString(m_symbols[i].symbol),m_symbols[i].digits);
     }
   m_Symbol.SetCurSel(0);
//---
  }
//+------------------------------------------------------------------+
//|                                                                  |
//+------------------------------------------------------------------+
void CManagerAPITestDlg::DisplaySecurity(const int res)
  {
   CRect   rc;
   int     cx=10;
//---
   if(res!=RET_OK) { DisplayRes(res,"ConSymbolGroup"); return; }
//---
   m_display_type=CONFIG_SYMB_GROUPS;
   m_Results.GetClientRect(&rc); cx=(rc.Width()-::GetSystemMetrics(SM_CXVSCROLL))/3;
   m_Results.ModifyStyle(LVS_NOCOLUMNHEADER,0);
//---
   m_Results.DeleteAllItems();
   while(m_Results.DeleteColumn(0)!=0) ;
   m_Results.InsertColumn(0,"Name",LVCFMT_LEFT,cx);
   m_Results.InsertColumn(1,"Description",LVCFMT_LEFT,cx*2);
//---
   for(int i=0; i<MAX_SEC_GROUPS; i++)
     {
      m_Results.InsertItem(i,m_security[i].name);
      m_Results.SetItemText(i,1,m_security[i].description);
     }
//---
  }
//+------------------------------------------------------------------+
//|                                                                  |
//+------------------------------------------------------------------+
void CManagerAPITestDlg::DisplayGroups()
  {
   CRect   rc;
   int     cx=10;
   CString str;
//---
   if(m_groups==NULL) return;
//---
   m_display_type=CONFIG_GROUPS;
   m_Results.GetClientRect(&rc); cx=(rc.Width()-::GetSystemMetrics(SM_CXVSCROLL))/3;
   m_Results.ModifyStyle(LVS_NOCOLUMNHEADER,0);
//---
   m_Results.DeleteAllItems();
   while(m_Results.DeleteColumn(0)!=0) ;
   m_Results.InsertColumn(0,"Group",LVCFMT_LEFT,cx);
   m_Results.InsertColumn(1,"Company",LVCFMT_LEFT,cx);
   m_Results.InsertColumn(2,"MC / SO",LVCFMT_LEFT,cx);
//---
   for(int i=0; i<m_total; i++)
     {
      m_Results.InsertItem(i,m_groups[i].group);
      m_Results.SetItemText(i,1,m_groups[i].company);
      str.Format("%d / %d ",m_groups[i].margin_call,m_groups[i].margin_stopout);
      if(m_groups[i].margin_type==MARGIN_TYPE_PERCENT)    str+="%";
      else                     /* MARGIN_TYPE_CURRENCY */ str+="$";
      m_Results.SetItemText(i,2,str);
      //---
      if(m_BaseGroup.FindStringExact(-1,m_groups[i].group)==CB_ERR)
         m_BaseGroup.AddString(m_groups[i].group);
     }
//---
  }
//+------------------------------------------------------------------+
//|                                                                  |
//+------------------------------------------------------------------+
void CManagerAPITestDlg::DisplayManagers()
  {
   CRect   rc;
   int     cx=10;
   CString str;
//---
   if(m_managers==NULL) return;
//---
   m_display_type=CONFIG_MANAGERS;
   m_Results.GetClientRect(&rc); cx=(rc.Width()-::GetSystemMetrics(SM_CXVSCROLL))/3;
   m_Results.ModifyStyle(LVS_NOCOLUMNHEADER,0);
//---
   m_Results.DeleteAllItems();
   while(m_Results.DeleteColumn(0)!=0) ;
   m_Results.InsertColumn(0,"Login",LVCFMT_LEFT,cx);
   m_Results.InsertColumn(1,"Mailbox",LVCFMT_LEFT,cx);
   m_Results.InsertColumn(2,"Groups",LVCFMT_LEFT,cx);
//---
   for(int i=0; i<m_total; i++)
     {
      str.Format("%d",m_managers[i].login); m_Results.InsertItem(i,str);
      m_Results.SetItemText(i,1,m_managers[i].mailbox);
      m_Results.SetItemText(i,2,m_managers[i].groups);
     }
//---
  }
//+------------------------------------------------------------------+
//|                                                                  |
//+------------------------------------------------------------------+
void CManagerAPITestDlg::DisplayFeeders()
  {
   static  LPCSTR modes[3]={ "Quotes","News","Quotes and News" };
   CRect   rc;
   int     cx=10;
//---
   if(m_feeders==NULL) return;
//---
   m_display_type=CONFIG_DATAFEEDS;
   m_Results.GetClientRect(&rc); cx=(rc.Width()-::GetSystemMetrics(SM_CXVSCROLL))/3;
   m_Results.ModifyStyle(LVS_NOCOLUMNHEADER,0);
//---
   m_Results.DeleteAllItems();
   while(m_Results.DeleteColumn(0)!=0) ;
   m_Results.InsertColumn(0,"Vendor",LVCFMT_LEFT,cx);
   m_Results.InsertColumn(1,"Source",LVCFMT_LEFT,cx);
   m_Results.InsertColumn(2,"Server",LVCFMT_LEFT,cx);
//---
   for(int i=0; i<m_total; i++)
     {
      m_Results.InsertItem(i,m_feeders[i].name);
      m_Results.SetItemText(i,1,modes[m_feeders[i].mode]);
      m_Results.SetItemText(i,2,m_feeders[i].server);
     }
//---
  }
//+------------------------------------------------------------------+
//|                                                                  |
//+------------------------------------------------------------------+
void CManagerAPITestDlg::DisplayLiveUpdate()
  {
   static  LPCSTR types[LIVE_UPDATE_LAST]=
                { "MetaTrader","Manager","Administrator","Data Server",
      "MetaTrader CE.ARM","MetaTrader CE.MIPS","MetaTrader CE.SH3" };
   CRect   rc;
   int     cx=10;
   CString str;
//---
   if(m_liveupdate==NULL) return;
//---
   m_display_type=CONFIG_LIVEUPDATE;
   m_Results.GetClientRect(&rc); cx=(rc.Width()-::GetSystemMetrics(SM_CXVSCROLL))/5;
   m_Results.ModifyStyle(LVS_NOCOLUMNHEADER,0);
//---
   m_Results.DeleteAllItems();
   while(m_Results.DeleteColumn(0)!=0) ;
   m_Results.InsertColumn(0,"Company",LVCFMT_LEFT,cx);
   m_Results.InsertColumn(1,"Type",LVCFMT_LEFT,cx);
   m_Results.InsertColumn(2,"Version",LVCFMT_LEFT,cx);
   m_Results.InsertColumn(3,"Path",LVCFMT_LEFT,cx);
   m_Results.InsertColumn(4,"Max",LVCFMT_LEFT,cx);
//---
   for(int i=0; i<m_total; i++)
     {
      m_Results.InsertItem(i,m_liveupdate[i].company);
      m_Results.SetItemText(i,1,types[m_liveupdate[i].type]);
      str.Format("%d.%d [%d files]",m_liveupdate[i].version,m_liveupdate[i].build,m_liveupdate[i].totalfiles);
      m_Results.SetItemText(i,2,str);
      m_Results.SetItemText(i,3,m_liveupdate[i].path);
      str.Format("%d",m_liveupdate[i].maxconnect); m_Results.SetItemText(i,4,str);
     }
//---
  }
//+------------------------------------------------------------------+
//|                                                                  |
//+------------------------------------------------------------------+
void CManagerAPITestDlg::DisplaySynchro()
  {
   static  LPCSTR modes[3]={ "Add","Update","Replace" };
   CRect   rc;
   int     cx=10;
//---
   if(m_synchro==NULL) return;
//---
   m_display_type=CONFIG_SYNC;
   m_Results.GetClientRect(&rc); cx=(rc.Width()-::GetSystemMetrics(SM_CXVSCROLL))/3;
   m_Results.ModifyStyle(LVS_NOCOLUMNHEADER,0);
//---
   m_Results.DeleteAllItems();
   while(m_Results.DeleteColumn(0)!=0) ;
   m_Results.InsertColumn(0,"Server",LVCFMT_LEFT,cx);
   m_Results.InsertColumn(1,"Mode",LVCFMT_LEFT,cx);
   m_Results.InsertColumn(2,"Symbols",LVCFMT_LEFT,cx);
//---
   for(int i=0; i<m_total; i++)
     {
      m_Results.InsertItem(i,m_synchro[i].server);
      m_Results.SetItemText(i,1,modes[m_synchro[i].mode]);
      m_Results.SetItemText(i,2,m_synchro[i].securities);
     }
//---
  }
//+------------------------------------------------------------------+
//|                                                                  |
//+------------------------------------------------------------------+
void CManagerAPITestDlg::DisplayPlugins()
  {
   static  LPCSTR enabled[2]={ "No","Yes" };
   CRect   rc;
   int     cx=10;
   CString str;
//---
   if(m_plugins==NULL) return;
//---
   m_display_type=CONFIG_PLUGINS;
   m_Results.GetClientRect(&rc); cx=(rc.Width()-::GetSystemMetrics(SM_CXVSCROLL))/5;
   m_Results.ModifyStyle(LVS_NOCOLUMNHEADER,0);
//---
   m_Results.DeleteAllItems();
   while(m_Results.DeleteColumn(0)!=0) ;
   m_Results.InsertColumn(0,"Enabled",LVCFMT_LEFT,cx);
   m_Results.InsertColumn(1,"Name",LVCFMT_LEFT,cx);
   m_Results.InsertColumn(2,"Version",LVCFMT_LEFT,cx);
   m_Results.InsertColumn(3,"File",LVCFMT_LEFT,cx);
   m_Results.InsertColumn(4,"Params",LVCFMT_LEFT,cx);
//---
   for(int i=0; i<m_total; i++)
     {
      m_Results.InsertItem(i,enabled[m_plugins[i].plugin.enabled]);
      m_Results.SetItemText(i,1,m_plugins[i].plugin.info.name);
      str.Format("%d.%02d",m_plugins[i].plugin.info.version/100,m_plugins[i].plugin.info.version%100);
      m_Results.SetItemText(i,2,str);
      m_Results.SetItemText(i,3,m_plugins[i].plugin.file);
      str.Format("%d",m_plugins[i].total);
      m_Results.SetItemText(i,4,str);
     }
//---
  }
//+------------------------------------------------------------------+
//|                                                                  |
//+------------------------------------------------------------------+
void CManagerAPITestDlg::DisplayAccounts()
  {
   CRect   rc;
   int     cx=10;
   CString str;
//---
   if(m_gateway_accounts==NULL) return;
//---
   m_display_type=CONFIG_GATEWAY_ACCOUNTS;
   m_Results.GetClientRect(&rc); cx=(rc.Width()-::GetSystemMetrics(SM_CXVSCROLL))/3;
   m_Results.ModifyStyle(LVS_NOCOLUMNHEADER,0);
//---
   m_Results.DeleteAllItems();
   while(m_Results.DeleteColumn(0)!=0) ;
   m_Results.InsertColumn(0,"Name",LVCFMT_LEFT,cx);
   m_Results.InsertColumn(1,"Login",LVCFMT_LEFT,cx);
   m_Results.InsertColumn(2,"Address",LVCFMT_LEFT,cx);
//---
   for(int i=0; i<m_total; i++)
     {
      m_Results.InsertItem(i,m_gateway_accounts[i].name);
      str.Format("%d",m_gateway_accounts[i].login);
      m_Results.SetItemText(i,1,str);
      m_Results.SetItemText(i,2,m_gateway_accounts[i].address);
     }
//---
  }
//+------------------------------------------------------------------+
//|                                                                  |
//+------------------------------------------------------------------+
void CManagerAPITestDlg::DisplayMarkups()
  {
   CRect   rc;
   int     cx=10;
   CString str;
//---
   if(m_gateway_markups==NULL) return;
//---
   m_display_type=CONFIG_GATEWAY_MARKUPS;
   m_Results.GetClientRect(&rc); cx=(rc.Width()-::GetSystemMetrics(SM_CXVSCROLL))/4;
   m_Results.ModifyStyle(LVS_NOCOLUMNHEADER,0);
//---
   m_Results.DeleteAllItems();
   while(m_Results.DeleteColumn(0)!=0) ;
   m_Results.InsertColumn(0,"Source",LVCFMT_LEFT,cx);
   m_Results.InsertColumn(1,"Symbol",LVCFMT_LEFT,cx);
   m_Results.InsertColumn(2,"Markup Bid",LVCFMT_LEFT,cx);
   m_Results.InsertColumn(3,"Markup Ask",LVCFMT_LEFT,cx);
//---
   for(int i=0; i<m_total; i++)
     {
      m_Results.InsertItem(i,m_gateway_markups[i].source);
      m_Results.SetItemText(i,1,m_gateway_markups[i].symbol);
      str.Format("%d",m_gateway_markups[i].bid_markup);
      m_Results.SetItemText(i,2,str);
      str.Format("%d",m_gateway_markups[i].ask_markup);
      m_Results.SetItemText(i,3,str);
     }
//---
  }
//+------------------------------------------------------------------+
//|                                                                  |
//+------------------------------------------------------------------+
void CManagerAPITestDlg::DisplayRules()
  {
   CRect   rc;
   int     cx=10;
   CString str;
//---
   if(m_gateway_rules==NULL) return;
//---
   m_display_type=CONFIG_GATEWAY_RULES;
   m_Results.GetClientRect(&rc); cx=(rc.Width()-::GetSystemMetrics(SM_CXVSCROLL))/4;
   m_Results.ModifyStyle(LVS_NOCOLUMNHEADER,0);
//---
   m_Results.DeleteAllItems();
   while(m_Results.DeleteColumn(0)!=0) ;
   m_Results.InsertColumn(0,"Name",LVCFMT_LEFT,cx);
   m_Results.InsertColumn(1,"Symbol",LVCFMT_LEFT,cx);
   m_Results.InsertColumn(1,"Group",LVCFMT_LEFT,cx);
   m_Results.InsertColumn(2,"Account",LVCFMT_LEFT,cx);
//---
   for(int i=0; i<m_total; i++)
     {
      m_Results.InsertItem(i,m_gateway_rules[i].name);
      m_Results.SetItemText(i,1,m_gateway_rules[i].request_symbol);
      m_Results.SetItemText(i,2,m_gateway_rules[i].request_group);
      m_Results.SetItemText(i,3,m_gateway_rules[i].exe_account_name);
     }
//---
  }
//+------------------------------------------------------------------+
//|                                                                  |
//+------------------------------------------------------------------+
void CManagerAPITestDlg::OnConfigUp()   { ConfigShift(-1); }
//+------------------------------------------------------------------+
//|                                                                  |
//+------------------------------------------------------------------+
void CManagerAPITestDlg::OnConfigDown() { ConfigShift(1);  }
//+------------------------------------------------------------------+
//|                                                                  |
//+------------------------------------------------------------------+
void CManagerAPITestDlg::ConfigShift(const int shift)
  {
   int      res=RET_ERROR,i;
   POSITION pos=m_Results.GetFirstSelectedItemPosition();
//---
   if(pos==NULL || (i=m_Results.GetNextSelectedItem(pos))<0) return;
//---
   switch(m_display_type)
     {
      case CONFIG_ACCESS:     res=m_manager->CfgShiftAccess(i,shift);     break;
      case CONFIG_SERVERS:    res=m_manager->CfgShiftDataServer(i,shift); break;
      case CONFIG_HOLIDAYS:   res=m_manager->CfgShiftHoliday(i,shift);    break;
      case CONFIG_SYMBOLS:    res=m_manager->CfgShiftSymbol(i,shift);     break;
      case CONFIG_GROUPS:     res=m_manager->CfgShiftGroup(i,shift);      break;
      case CONFIG_MANAGERS:   res=m_manager->CfgShiftManager(i,shift);    break;
      case CONFIG_DATAFEEDS:  res=m_manager->CfgShiftFeeder(i,shift);     break;
      case CONFIG_LIVEUPDATE: res=m_manager->CfgShiftLiveUpdate(i,shift); break;
      case CONFIG_SYNC:       res=m_manager->CfgShiftSync(i,shift);       break;
      case CONFIG_PLUGINS:    res=m_manager->CfgShiftPlugin(i,shift);     break;
      case CONFIG_GATEWAY_ACCOUNTS: res=m_manager->CfgShiftGatewayAccount(i,shift); break;
      case CONFIG_GATEWAY_MARKUPS : res=m_manager->CfgShiftGatewayMarkup(i,shift);  break;
      case CONFIG_GATEWAY_RULES   : res=m_manager->CfgShiftGatewayRule(i,shift);    break;
      default: return;
     }
   if(res==RET_OK)
     {
      m_Config.SetCurSel(m_display_type-1);
      OnConfigRequest();
     }
   else DisplayRes(res,"CfgShift");
//---
  }
//+------------------------------------------------------------------+
//|                                                                  |
//+------------------------------------------------------------------+
void CManagerAPITestDlg::OnConfigUpdate()
  {
   int      res=RET_ERROR,i=-1,j;
   POSITION pos=m_Results.GetFirstSelectedItemPosition();
//---
   if(pos!=NULL) i=m_Results.GetNextSelectedItem(pos);
//---
   switch(m_display_type)
     {
      case CONFIG_COMMON:
         m_common.timeofdemo=m_common.timeofdemo==14?30:14;
         res=m_manager->CfgUpdateCommon(&m_common);
         break;

      case CONFIG_TIME:
         for(j=0; j<24; j++) m_time.days[0][j]=!m_time.days[0][j];
         res=m_manager->CfgUpdateTime(&m_time);
         break;

      case CONFIG_ACCESS:
         if(i<0) return;
         if(m_access[i].comment[0]!=0) m_access[i].comment[0]=0;
         else _snprintf(m_access[i].comment,sizeof(m_access[i].comment)-1,"Rule_%d",i);
         res=m_manager->CfgUpdateAccess(&m_access[i],i);
         break;

      case CONFIG_SERVERS:
         if(i<0) return;
         if(m_datasrv[i].description[0]!=0) m_datasrv[i].description[0]=0;
         else _snprintf(m_datasrv[i].description,sizeof(m_datasrv[i].description)-1,"DataServer_%d",i);
         res=m_manager->CfgUpdateDataServer(&m_datasrv[i],i);
         break;

      case CONFIG_HOLIDAYS:
         if(i<0) return;
         if(m_holiday[i].description[0]!=0) m_holiday[i].description[0]=0;
         else _snprintf(m_holiday[i].description,sizeof(m_holiday[i].description)-1,"Holiday_%d",i);
         res=m_manager->CfgUpdateHoliday(&m_holiday[i],i);
         break;

      case CONFIG_SYMBOLS:
         if(i<0) return;
         m_symbols[i].trade=m_symbols[i].trade==TRADE_FULL?TRADE_CLOSE:TRADE_FULL;
         res=m_manager->CfgUpdateSymbol(&m_symbols[i]);
         break;

      case CONFIG_SYMB_GROUPS:
         if(i<0) return;
         if(m_security[i].description[0]!=0) m_security[i].description[0]=0;
         else _snprintf(m_security[i].description,sizeof(m_security[i].description)-1,"Securities_%d",i);
         res=m_manager->CfgUpdateSymbolGroup(&m_security[i],i);
         break;

      case CONFIG_GROUPS:
         if(i<0) return;
         m_groups[i].margin_stopout=m_groups[i].margin_stopout>0?0:50;
         res=m_manager->CfgUpdateGroup(&m_groups[i]);
         break;

      case CONFIG_MANAGERS:
         if(i<0) return;
         if(m_managers[i].mailbox[0]!=0) m_managers[i].mailbox[0]=0;
         else COPY_STR(m_managers[i].mailbox,"Tech Support");
         res=m_manager->CfgUpdateManager(&m_managers[i]);
         break;

      case CONFIG_DATAFEEDS:
         if(i<0) return;
         m_feeders[i].mode=m_feeders[i].mode==FEED_QUOTES?FEED_QUOTESNEWS:FEED_QUOTES;
         res=m_manager->CfgUpdateFeeder(&m_feeders[i]);
         break;

      case CONFIG_BACKUP:
         m_backup.fullbackup_period=m_backup.fullbackup_period==BACKUP_1DAY?BACKUP_4HOURS:BACKUP_1DAY;
         res=m_manager->CfgUpdateBackup(&m_backup);
         break;

      case CONFIG_LIVEUPDATE:
         m_liveupdate[i].maxconnect=m_liveupdate[i].maxconnect>10?10:30;
         res=m_manager->CfgUpdateLiveUpdate(&m_liveupdate[i]);
         break;

      case CONFIG_SYNC:
         if(i<0) return;
         m_synchro[i].mode=m_synchro[i].mode==HB_ADD?HB_UPDATE:HB_ADD;
         res=m_manager->CfgUpdateSync(&m_synchro[i]);
         break;

      case CONFIG_PLUGINS:
         if(i<0) return;
         m_plugins[i].plugin.enabled=!m_plugins[i].plugin.enabled;
         res=m_manager->CfgUpdatePlugin(&m_plugins[i].plugin,m_plugins[i].params,m_plugins[i].total);
         break;

      case CONFIG_GATEWAY_ACCOUNTS:
         if(i<0) return;
         m_gateway_accounts[i].enable=!m_gateway_accounts[i].enable;
         res=m_manager->CfgUpdateGatewayAccount(&m_gateway_accounts[i]);
         break;

      case CONFIG_GATEWAY_MARKUPS:
         if(i<0) return;
         m_gateway_markups[i].enable=!m_gateway_markups[i].enable;
         res=m_manager->CfgUpdateGatewayMarkup(&m_gateway_markups[i]);
         break;

      case CONFIG_GATEWAY_RULES:
         if(i<0) return;
         m_gateway_rules[i].enable=!m_gateway_rules[i].enable;
         res=m_manager->CfgUpdateGatewayRule(&m_gateway_rules[i]);
         break;

      default:
         return;
     }
   if(res==RET_OK)
     {
      m_Config.SetCurSel(m_display_type-1);
      OnConfigRequest();
     }
   else
      DisplayRes(res,"CfgUpdate");
//---
  }
//+------------------------------------------------------------------+
//|                                                                  |
//+------------------------------------------------------------------+
void CManagerAPITestDlg::OnConfigDelete()
  {
   int      res=RET_ERROR,i;
   POSITION pos=m_Results.GetFirstSelectedItemPosition();
//---
   if(pos==NULL || (i=m_Results.GetNextSelectedItem(pos))<0) return;
//---
   switch(m_display_type)
     {
      case CONFIG_ACCESS:     res=m_manager->CfgDeleteAccess(i);     break;
      case CONFIG_SERVERS:    res=m_manager->CfgDeleteDataServer(i); break;
      case CONFIG_HOLIDAYS:   res=m_manager->CfgDeleteHoliday(i);    break;
      case CONFIG_SYMBOLS:    res=m_manager->CfgDeleteSymbol(i);     break;
      case CONFIG_GROUPS:     res=m_manager->CfgDeleteGroup(i);      break;
      case CONFIG_MANAGERS:   res=m_manager->CfgDeleteManager(i);    break;
      case CONFIG_DATAFEEDS:  res=m_manager->CfgDeleteFeeder(i);     break;
      case CONFIG_LIVEUPDATE: res=m_manager->CfgDeleteLiveUpdate(i); break;
      case CONFIG_SYNC:       res=m_manager->CfgDeleteSync(i);       break;
      case CONFIG_PLUGINS:    res=RET_OK;                            break;
      case CONFIG_GATEWAY_ACCOUNTS: res=m_manager->CfgDeleteGatewayAccount(i); break;
      case CONFIG_GATEWAY_MARKUPS:  res=m_manager->CfgDeleteGatewayMarkup(i);  break;
      case CONFIG_GATEWAY_RULES:    res=m_manager->CfgDeleteGatewayRule(i);    break;
      default:
         return;
     }
   if(res==RET_OK)
     {
      m_Config.SetCurSel(m_display_type-1);
      OnConfigRequest();
     }
   else
      DisplayRes(res,"CfgDelete");
//---
  }
//+------------------------------------------------------------------+
//|                                                                  |
//+------------------------------------------------------------------+
void CManagerAPITestDlg::OnChartRequest()
  {
   int    pos=-1;
   __time32_t stamp=0;
//--- проверки
   if((pos=m_Symbol.GetCurSel())<0) return;
   m_digits=int(m_Symbol.GetItemData(pos));
//---
   Free();
//--- запрос за последние сутки
   m_Symbol.GetLBText(pos,m_chart.symbol);
   m_chart.period=int(m_Period.GetItemData(m_Period.GetCurSel()));
   m_chart.end   =(_time32(NULL)/86400)*86400+86400;
   m_chart.start =m_chart.end-86400;
   m_chart.mode  =CHART_RANGE_IN;
//--- запрашиваем
   m_rates=m_manager->ChartRequest(&m_chart,&stamp,&m_total);
   DisplayRates();
//---
  }
//+------------------------------------------------------------------+
//|                                                                  |
//+------------------------------------------------------------------+
void CManagerAPITestDlg::DisplayRates()
  {
   CRect   rc;
   int     cx;
   CString str;
//---
   if(m_rates==NULL) return;
//---
   m_display_type=DISPLAY_CHART;
   m_Results.GetClientRect(&rc);
   cx=(rc.Width()-::GetSystemMetrics(SM_CXVSCROLL))/7;
   m_Results.ModifyStyle(LVS_NOCOLUMNHEADER,0);
//---
   m_Results.DeleteAllItems();
   while(m_Results.DeleteColumn(0)!=0) ;
   m_Results.InsertColumn(0,"Time",LVCFMT_LEFT,cx*2);
   m_Results.InsertColumn(1,"Open",LVCFMT_LEFT,cx);
   m_Results.InsertColumn(2,"High",LVCFMT_LEFT,cx);
   m_Results.InsertColumn(3,"Low",LVCFMT_LEFT,cx);
   m_Results.InsertColumn(4,"Close",LVCFMT_LEFT,cx);
   m_Results.InsertColumn(5,"Volume",LVCFMT_LEFT,cx);
//---
   for(int i=0; i<m_total; i++)
     {
      FormatDateTime(m_rates[i].ctm,str); m_Results.InsertItem(i,str);
      FormatDouble(m_rates[i].open,m_digits,str); m_Results.SetItemText(i,1,str);
      FormatDouble(m_rates[i].open+m_rates[i].high, m_digits,str); m_Results.SetItemText(i,2,str);
      FormatDouble(m_rates[i].open+m_rates[i].low,  m_digits,str); m_Results.SetItemText(i,3,str);
      FormatDouble(m_rates[i].open+m_rates[i].close,m_digits,str); m_Results.SetItemText(i,4,str);
      str.Format("%.0lf",m_rates[i].vol); m_Results.SetItemText(i,5,str);
     }
//---
  }
//+------------------------------------------------------------------+
//|                                                                  |
//+------------------------------------------------------------------+
void CManagerAPITestDlg::OnChartUpdate()
  {
   int      res=RET_ERROR,i=-1,count=1;
   POSITION pos=m_Results.GetFirstSelectedItemPosition();
   RateInfo rate={0};
//---
   if(m_display_type!=DISPLAY_CHART || m_rates==NULL || pos==NULL || (i=m_Results.GetNextSelectedItem(pos))<0) return;
//--- increment volume
   memcpy(&rate,&m_rates[i],sizeof(rate));
   rate.vol+=1.0;
   res=m_manager->ChartUpdate(m_chart.symbol,m_chart.period,&rate,&count);
//---
   if(res==RET_OK)
     {
      m_Symbol.SelectString(-1,m_chart.symbol);
      count=m_Period.GetCount();
      for(i=0; i<count; i++)
         if(m_Period.GetItemData(i)==(DWORD)m_chart.period)
           {
            m_Period.SetCurSel(i);
            break;
           }
      OnChartRequest();
     }
   else DisplayRes(res,"ChartUpdate");
  }
//+------------------------------------------------------------------+
//|                                                                  |
//+------------------------------------------------------------------+
void CManagerAPITestDlg::OnChartDelete()
  {
   int      res=RET_ERROR,i=-1,count=1;
   POSITION pos=m_Results.GetFirstSelectedItemPosition();
//---
   if(m_display_type!=DISPLAY_CHART || m_rates==NULL || pos==NULL || (i=m_Results.GetNextSelectedItem(pos))<0) return;
//--- delete rate
   res=m_manager->ChartDelete(m_chart.symbol,m_chart.period,&m_rates[i],&count);
//---
   if(res==RET_OK)
     {
      m_Symbol.SelectString(-1,m_chart.symbol);
      count=m_Period.GetCount();
      for(i=0; i<count; i++)
         if(m_Period.GetItemData(i)==(DWORD)m_chart.period)
           {
            m_Period.SetCurSel(i);
            break;
           }
      OnChartRequest();
     }
   else
      DisplayRes(res,"ChartDelete");
  }
//+------------------------------------------------------------------+
//|                                                                  |
//+------------------------------------------------------------------+
void CManagerAPITestDlg::OnChartAdd()
  {
   int      res=RET_ERROR,i=-1,count=1;
   POSITION pos=m_Results.GetFirstSelectedItemPosition();
   RateInfo rate={0};
//---
   if(m_display_type!=DISPLAY_CHART || m_rates==NULL || pos==NULL || (i=m_Results.GetNextSelectedItem(pos))<0) return;
//--- add rate next to selected
   memcpy(&rate,&m_rates[i],sizeof(rate));
   rate.ctm+=m_chart.period*60;
   res=m_manager->ChartUpdate(m_chart.symbol,m_chart.period,&rate,&count);
//---
   if(res==RET_OK)
     {
      m_Symbol.SelectString(-1,m_chart.symbol);
      count=m_Period.GetCount();
      for(i=0; i<count; i++)
         if(m_Period.GetItemData(i)==(DWORD)m_chart.period)
           {
            m_Period.SetCurSel(i);
            break;
           }
      OnChartRequest();
     }
   else
      DisplayRes(res,"ChartAdd");
  }
//+------------------------------------------------------------------+
//|                                                                  |
//+------------------------------------------------------------------+
void CManagerAPITestDlg::OnPerformance()
  {
   __time32_t from=0;
//---
   Free();
//--- запрос за последние сутки
   from=(_time32(NULL)/86400)*86400;
//--- запрашиваем
   m_performance=m_manager->PerformaneRequest(from,&m_total);
   DisplayPerformance();
//---
  }
//+------------------------------------------------------------------+
//|                                                                  |
//+------------------------------------------------------------------+
void CManagerAPITestDlg::DisplayPerformance()
  {
   CRect   rc;
   int     cx=10;
   CString str;
//---
   if(m_performance==NULL) return;
//---
   m_display_type=DISPLAY_PERFORMANCE;
   m_Results.GetClientRect(&rc);
   cx=(rc.Width()-::GetSystemMetrics(SM_CXVSCROLL))/5;
   m_Results.ModifyStyle(LVS_NOCOLUMNHEADER,0);
//---
   m_Results.DeleteAllItems();
   while(m_Results.DeleteColumn(0)!=0) ;

   m_Results.InsertColumn(0,"Time",LVCFMT_LEFT,cx);
   m_Results.InsertColumn(1,"Connections",LVCFMT_LEFT,cx);
   m_Results.InsertColumn(2,"CPU (%)",LVCFMT_LEFT,cx);
   m_Results.InsertColumn(3,"Memory (Kb)",LVCFMT_LEFT,cx);
   m_Results.InsertColumn(4,"Network (Kb/s)",LVCFMT_LEFT,cx);
//---
   for(int i=0; i<m_total; i++)
     {
      FormatDateTime(m_performance[i].ctm,str);  m_Results.InsertItem(i,str);
      str.Format("%d",m_performance[i].users);   m_Results.SetItemText(i,1,str);
      str.Format("%d",m_performance[i].cpu);     m_Results.SetItemText(i,2,str);
      str.Format("%d",m_performance[i].freemem); m_Results.SetItemText(i,3,str);
      str.Format("%d",m_performance[i].network); m_Results.SetItemText(i,4,str);
     }
//---
  }
//+------------------------------------------------------------------+
//|                                                                  |
//+------------------------------------------------------------------+
void CManagerAPITestDlg::OnBackupUsers()
  {
   Free();
//--- последние 50 штук
   m_total=50;
//--- запрашиваем
   m_backups=m_manager->BackupInfoUsers(BACKUPS_ALL,&m_total);
   DisplayBackups();
//---
  }
//+------------------------------------------------------------------+
//|                                                                  |
//+------------------------------------------------------------------+
void CManagerAPITestDlg::OnBackupOrders()
  {
   Free();
//--- последние 50 штук
   m_total=50;
//--- запрашиваем
   m_backups=m_manager->BackupInfoOrders(BACKUPS_ALL,&m_total);
   DisplayBackups();
//---
  }
//+------------------------------------------------------------------+
//|                                                                  |
//+------------------------------------------------------------------+
void CManagerAPITestDlg::DisplayBackups()
  {
   if(m_backups==NULL) return;
//---
   while(m_Backup.DeleteString(0)>0) ;
   for(int i=0; i<m_total; i++)
      m_Backup.AddString(m_backups[i].file);

   if(m_Backup.GetCount()>0)
     {
      m_Backup.SetCurSel(0);
      m_Backup.ShowDropDown();
     }
//---
  }
//+------------------------------------------------------------------+
//|                                                                  |
//+------------------------------------------------------------------+
void CManagerAPITestDlg::OnBackupRequest()
  {
   char file[256]="";
//---
   Free();
//---
   m_Backup.GetWindowText(file,sizeof(file)-1);
   if(file[0]==0) return;
//---
   AfxGetApp()->BeginWaitCursor();
   if(strstr(file,"users_")==file)
     {
      m_users =m_manager->BackupRequestUsers(file,"demoforex",&m_total);
      DisplayUsers(DISPLAY_BACKUP_USERS);
     }
   else
      if(strstr(file,"orders_")==file)
        {
         m_trades=m_manager->BackupRequestOrders(file,"demoforex",&m_total);
         DisplayOrders(DISPLAY_BACKUP_TRADES);
        }
   AfxGetApp()->EndWaitCursor();
//---
  }
//+------------------------------------------------------------------+
//|                                                                  |
//+------------------------------------------------------------------+
void CManagerAPITestDlg::DisplayUsers(const int type)
  {
   CRect   rc;
   int     cx=10;
   CString str;
//---
   if(m_users==NULL) return;
//---
   m_display_type=type;
   m_Results.GetClientRect(&rc); cx=(rc.Width()-::GetSystemMetrics(SM_CXVSCROLL))/4;
   m_Results.ModifyStyle(LVS_NOCOLUMNHEADER,0);
//---
   m_Results.DeleteAllItems();
   while(m_Results.DeleteColumn(0)!=0) ;

   m_Results.InsertColumn(0,"Login",LVCFMT_LEFT,cx);
   m_Results.InsertColumn(1,"Name",LVCFMT_LEFT,cx);
   m_Results.InsertColumn(2,"Group",LVCFMT_LEFT,cx);
   m_Results.InsertColumn(3,"Balance",LVCFMT_RIGHT,cx);
//---
   for(int i=0; i<m_total && i<100; i++)
     {
      str.Format("%d",m_users[i].login); m_Results.InsertItem(i,str);
      m_Results.SetItemText(i,1,m_users[i].name);
      m_Results.SetItemText(i,2,m_users[i].group);
      str.Format("%.02lf",m_users[i].balance); m_Results.SetItemText(i,3,str);
     }
//---
  }
//+------------------------------------------------------------------+
//|                                                                  |
//+------------------------------------------------------------------+
void CManagerAPITestDlg::DisplayOrders(const int type)
  {
   CRect   rc;
   int     cx=10;
   char    tmp[256]="";
//---
   if(m_trades==NULL) return;
//---
   m_display_type=type;
   m_Results.GetClientRect(&rc); cx=(rc.Width()-::GetSystemMetrics(SM_CXVSCROLL))/6;
   m_Results.ModifyStyle(LVS_NOCOLUMNHEADER,0);
//---
   m_Results.DeleteAllItems();
   while(m_Results.DeleteColumn(0)!=0) ;
   m_Results.InsertColumn(0,"Order",LVCFMT_LEFT,cx);
   m_Results.InsertColumn(1,"Login",LVCFMT_LEFT,cx);
   m_Results.InsertColumn(2,"Type",LVCFMT_LEFT,cx);
   m_Results.InsertColumn(3,"Symbol",LVCFMT_LEFT,cx);
   m_Results.InsertColumn(4,"Price",LVCFMT_RIGHT,cx);
   m_Results.InsertColumn(5,"Profit",LVCFMT_RIGHT,cx);
//---
   for(int i=0; i<m_total && i<100; i++)
     {
      _snprintf(tmp,sizeof(tmp)-1,"%d",m_trades[i].order);
      m_Results.InsertItem(i,tmp);
      _snprintf(tmp,sizeof(tmp)-1,"%d",m_trades[i].login);
      m_Results.SetItemText(i,1,tmp);
      m_Results.SetItemText(i,2,GetCmd(m_trades[i].cmd));
      m_Results.SetItemText(i,3,m_trades[i].symbol);
      ToSym(tmp,m_trades[i].open_price,m_trades[i].digits);
      m_Results.SetItemText(i,4,tmp);
      _snprintf(tmp,sizeof(tmp)-1,"%.02lf",m_trades[i].profit);
      m_Results.SetItemText(i,5,tmp);
     }
//---
  }
//+------------------------------------------------------------------+
//|                                                                  |
//+------------------------------------------------------------------+
void CManagerAPITestDlg::OnBackupRestore()
  {
   int      res=RET_ERROR,i=-1,total=1;
   POSITION pos=m_Results.GetFirstSelectedItemPosition();
   TradeRestoreResult *trr=NULL;
//---
   if(pos==NULL || (i=m_Results.GetNextSelectedItem(pos))<0) return;
//---
   switch(m_display_type)
     {
      case DISPLAY_BACKUP_USERS:
         if(m_users==NULL) return;
         res=m_manager->BackupRestoreUsers(&m_users[i],1);
         DisplayRes(res,"BackupRestoreUsers");
         break;

      case DISPLAY_BACKUP_TRADES:
         if(m_trades==NULL) return;
         trr=m_manager->BackupRestoreOrders(&m_trades[i],&total);

         if(total<=0) MessageBox("Zero results","BackupRestoreOrders");
         else
            if(trr[0].res==RET_OK) MessageBox("Order restored","BackupRestoreOrders");
            else
               if(trr[0].res==RET_INVALID_DATA) MessageBox("Existent order restored","BackupRestoreOrders");
               else
                  MessageBox("Error restoring order","BackupRestoreOrders");
         if(trr!=NULL)
           {
            m_manager->MemFree(trr);
            trr=NULL;
           }
         break;
      default:
         break;
     }
//---
  }
//+------------------------------------------------------------------+
//|                                                                  |
//+------------------------------------------------------------------+
void CManagerAPITestDlg::OnBaseUsers()
  {
   char group[64]="";
//---
   Free();
//---
   m_BaseGroup.GetWindowText(group,sizeof(group)-1);
   AfxGetApp()->BeginWaitCursor();
   m_users=m_manager->AdmUsersRequest(group,&m_total);
   DisplayUsers(DISPLAY_BASE_USERS);
   AfxGetApp()->EndWaitCursor();
//---
  }
//+------------------------------------------------------------------+
//|                                                                  |
//+------------------------------------------------------------------+
void CManagerAPITestDlg::OnBaseOrders()
  {
   char group[128]="";
//---
   Free();
//---
   m_BaseGroup.GetWindowText(group,sizeof(group)-1);
   AfxGetApp()->BeginWaitCursor();
   m_trades=m_manager->AdmTradesRequest(group,FALSE,&m_total);
   DisplayOrders(DISPLAY_BASE_TRADES);
   AfxGetApp()->EndWaitCursor();
//---
  }
//+------------------------------------------------------------------+
//|                                                                  |
//+------------------------------------------------------------------+
void CManagerAPITestDlg::OnUsersCheck()
  {
   int      res=RET_ERROR,i=-1,login=0,total=1;
   POSITION pos=m_Results.GetFirstSelectedItemPosition();
   CString  str;
//---
   if(m_display_type!=DISPLAY_BASE_USERS) return;
   if(pos==NULL || (i=m_Results.GetNextSelectedItem(pos))<0) return;
//---
   login=m_users[i].login;
   res=m_manager->AdmBalanceCheck(&login,&total);
   if(res!=RET_OK) DisplayRes(res,"UsersBalanceCheck");
   else
     {
      str.Format("%d wrong balances",total);
      MessageBox(str,"UsersBalanceCheck");
     }
//---
  }
//+------------------------------------------------------------------+
//|                                                                  |
//+------------------------------------------------------------------+
void CManagerAPITestDlg::OnUsersFix()
  {
   int      res=RET_ERROR,i=-1,login=0,total=1;
   POSITION pos=m_Results.GetFirstSelectedItemPosition();
   CString  str;
//---
   if(m_display_type!=DISPLAY_BASE_USERS) return;
   if(pos==NULL || (i=m_Results.GetNextSelectedItem(pos))<0) return;
//---
   login=m_users[i].login;
   res=m_manager->AdmBalanceFix(&login,total);
   DisplayRes(res,"UsersBalanceFix");
//---
  }
//+------------------------------------------------------------------+
//|                                                                  |
//+------------------------------------------------------------------+
void CManagerAPITestDlg::OnOrdersModify()
  {
   int      res=RET_ERROR,i=-1;
   POSITION pos=m_Results.GetFirstSelectedItemPosition();
   CString  str;
//---
   if(m_display_type!=DISPLAY_BASE_TRADES) return;
   if(pos==NULL || (i=m_Results.GetNextSelectedItem(pos))<0) return;
//---
   m_trades[i].open_price+=1.0/pow(10.0,m_trades[i].digits);
   res=m_manager->AdmTradeRecordModify(&m_trades[i]);
   DisplayRes(res,"AdmTradeRecordModify");
//---
  }
//+------------------------------------------------------------------+
//|                                                                  |
//+------------------------------------------------------------------+
void CManagerAPITestDlg::OnOrdersDelete()
  {
   int      res=RET_ERROR,i=-1;
   POSITION pos=m_Results.GetFirstSelectedItemPosition();
   CString  str;
//---
   if(m_display_type!=DISPLAY_BASE_TRADES) return;
   if(pos==NULL || (i=m_Results.GetNextSelectedItem(pos))<0) return;
//---
   res=m_manager->AdmTradesDelete(&m_trades[i].order,1);
   DisplayRes(res,"AdmTradesDelete");
//---
  }
//+------------------------------------------------------------------+
//|                                                                  |
//+------------------------------------------------------------------+
