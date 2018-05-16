//+------------------------------------------------------------------+
//|                                  MetaTrader 4 Manager API Sample |
//|                   Copyright 2001-2014, MetaQuotes Software Corp. |
//|                                        http://www.metaquotes.net |
//+------------------------------------------------------------------+
#include "stdafx.h"
#include "ManagerAPISample.h"
#include "PageMain.h"
#include "ManagerSheet.h"
#include "dialogs\MailSendDlg.h"
#include "dialogs\NewsSendDlg.h"

//+------------------------------------------------------------------+
//|                                                                  |
//+------------------------------------------------------------------+
IMPLEMENT_DYNCREATE(CPageMain, CPropertyPageEx)
//+------------------------------------------------------------------+
//|                                                                  |
//+------------------------------------------------------------------+
CPageMain::CPageMain() : CPropertyPageEx(CPageMain::IDD)
  {
   //{{AFX_DATA_INIT(CPageMain)
   //}}AFX_DATA_INIT
   m_psp.dwFlags&=~PSP_HASHELP;
  }
//+------------------------------------------------------------------+
//|                                                                  |
//+------------------------------------------------------------------+
CPageMain::~CPageMain()
  {
  }
//+------------------------------------------------------------------+
//|                                                                  |
//+------------------------------------------------------------------+
void CPageMain::DoDataExchange(CDataExchange* pDX)
  {
   CPropertyPageEx::DoDataExchange(pDX);
   //{{AFX_DATA_MAP(CPageMain)
   DDX_Control(pDX, IDC_GROUPS, m_Groups);
   DDX_Control(pDX, IDC_SERVER, m_Server);
   DDX_Control(pDX, IDC_PASSWORD, m_Password);
   DDX_Control(pDX, IDC_LOGIN, m_Login);
   //}}AFX_DATA_MAP
  }
//+------------------------------------------------------------------+
//|                                                                  |
//+------------------------------------------------------------------+
BEGIN_MESSAGE_MAP(CPageMain, CPropertyPageEx)
   //{{AFX_MSG_MAP(CPageMain)
   ON_BN_CLICKED(IDC_CONNECT, OnConnect)
   ON_BN_CLICKED(IDC_LOGINCMD, OnLogincmd)
   ON_BN_CLICKED(IDC_DISCONNECT, OnDisconnect)
   ON_BN_CLICKED(IDC_RIGHTS, OnRights)
   ON_BN_CLICKED(IDC_REQ_GROUPS, OnReqGroups)
   ON_BN_CLICKED(IDC_SEND_MAIL, OnSendMail)
   ON_BN_CLICKED(IDC_SEND_NEWS, OnSendNews)
   ON_BN_CLICKED(IDC_PUMPING, OnPumping)
   //}}AFX_MSG_MAP
END_MESSAGE_MAP()
//+------------------------------------------------------------------+
//|                                                                  |
//+------------------------------------------------------------------+
BOOL CPageMain::OnInitDialog()
  {
   CRect rc;
   int   cx;
//---
   CPropertyPageEx::OnInitDialog();
//---
   m_Server.SetWindowText("localhost:443");
   m_Login.SetWindowText("11");
   m_Password.SetWindowText("Manager11");
//---
   m_Groups.SetExtendedStyle(LVS_EX_FULLROWSELECT);
   m_Groups.GetClientRect(&rc); cx=rc.Width()/3;
   m_Groups.InsertColumn(0,"Group",  LVCFMT_LEFT,cx);
   m_Groups.InsertColumn(1,"Company",LVCFMT_LEFT,cx);
   m_Groups.InsertColumn(2,"MC / SO",LVCFMT_LEFT,cx);
//---
   return(TRUE);
  }
//+------------------------------------------------------------------+
//|                                                                  |
//+------------------------------------------------------------------+
void CPageMain::OnConnect()
  {
   char server[128]="";
//---
   m_Server.GetWindowText(server,sizeof(server)-1);
   int res=ExtManager->Connect(server);
//---
   MessageBox(ExtManager->ErrorDescription(res),"Connect");
  }
//+------------------------------------------------------------------+
//|                                                                  |
//+------------------------------------------------------------------+
void CPageMain::OnLogincmd()
  {
   int  login=0;
   char pass[16]="";
//---
   login=GetDlgItemInt(m_Login.GetDlgCtrlID(),NULL,FALSE);
   m_Password.GetWindowText(pass,sizeof(pass)-1);
   int res=ExtManager->Login(login,pass);
//---
   MessageBox(ExtManager->ErrorDescription(res),"Login");
  }
//+------------------------------------------------------------------+
//|                                                                  |
//+------------------------------------------------------------------+
//#define USE_PUMP_FUNC
//+------------------------------------------------------------------+
//|                                                                  |
//+------------------------------------------------------------------+
void CPageMain::OnPumping()
  {
   int  login=0,res=RET_ERROR;
   char server[128]="",pass[16]="";
//---
   m_Server.GetWindowText(server,sizeof(server)-1);
   login=GetDlgItemInt(m_Login.GetDlgCtrlID(),NULL,FALSE);
   m_Password.GetWindowText(pass,sizeof(pass)-1);
//---
   if(ExtManagerPump->IsConnected()!=FALSE) return;
   res=ExtManagerPump->Connect(server);
   if(res==RET_OK)
     {
      res=ExtManagerPump->Login(login,pass);
#ifdef USE_PUMP_FUNC
      if(res==RET_OK) res=ExtManagerPump->PumpingSwitch(CManagerSheet::PumpingFunc,NULL,0,0);
#else
      if(res==RET_OK) res=ExtManagerPump->PumpingSwitch(NULL,GetParent()->GetSafeHwnd(),ExtPumpingMsg,0);
#endif
     }
//---
   MessageBox(ExtManagerPump->ErrorDescription(res),"PumpingSwitch");
  }
//+------------------------------------------------------------------+
//|                                                                  |
//+------------------------------------------------------------------+
void CPageMain::OnDisconnect()
  {
   int res=ExtManager->Disconnect();
   if(ExtManagerPump->IsConnected()) res=ExtManagerPump->Disconnect();
   MessageBox(ExtManager->ErrorDescription(res),"Disconnect");
  }
//+------------------------------------------------------------------+
//|                                                                  |
//+------------------------------------------------------------------+
void CPageMain::OnRights()
  {
   ConManager man={0};
   CString    str;
//---
   int res=ExtManager->ManagerRights(&man);
   if(res!=RET_OK) { MessageBox(ExtManager->ErrorDescription(res),"ManagerRights"); return; }
//---
   if(man.admin  !=FALSE) str+="admin\n";
   if(man.manager!=FALSE) str+="manager\n";
   if(man.money  !=FALSE) str+="money\n";
   if(man.online !=FALSE) str+="online\n";
   if(man.riskman!=FALSE) str+="riskman\n";
   if(man.broker !=FALSE) str+="broker\n";
   if(man.logs   !=FALSE) str+="logs\n";
   if(man.reports!=FALSE) str+="reports\n";
   if(man.trades !=FALSE) str+="trades\n";
   if(man.news   !=FALSE) str+="news\n";
   if(man.email  !=FALSE) str+="email\n";
   if(man.market_watch!=FALSE) str+="market watch\n";
   if(man.see_trades  !=FALSE) str+="see trades\n";
//---
   MessageBox(str,"ManagerRights");
  }
//+------------------------------------------------------------------+
//|                                                                  |
//+------------------------------------------------------------------+
void CPageMain::OnReqGroups()
  {
   ConGroup *groups=NULL;
   int       total =0;
   CString   str;
//---
   groups=ExtManager->GroupsRequest(&total);
   if(groups==NULL || total==0) { MessageBox("No groups","GroupsRequest"); return; }
//---
   m_Groups.DeleteAllItems();
   for(int i=0; i<total; i++)
     {
      m_Groups.InsertItem(i,groups[i].group);
      m_Groups.SetItemText(i,1,groups[i].company);
      str.Format("%d%% / %d%%",groups[i].margin_call,groups[i].margin_stopout);
      m_Groups.SetItemText(i,2,str);
     }
//---
   ExtManager->MemFree(groups); groups=NULL;
  }
//+------------------------------------------------------------------+
//|                                                                  |
//+------------------------------------------------------------------+
void CPageMain::OnSendMail()
  {
   ConManager man={0};
//---
   if(ExtManager->ManagerRights(&man)!=RET_OK) return;
   if(man.login<=0 || man.email==FALSE)        return;
//---
   CMailSendDlg dlg(&man);
   dlg.DoModal();
//---
  }
//+------------------------------------------------------------------+
//|                                                                  |
//+------------------------------------------------------------------+
void CPageMain::OnSendNews()
  {
   ConManager man={0};
//---
   if(ExtManager->ManagerRights(&man)!=RET_OK || man.news==FALSE) return;
//---
   CNewsSendDlg dlg;
   dlg.DoModal();
//---
  }
//+------------------------------------------------------------------+
//|                                                                  |
//+------------------------------------------------------------------+
