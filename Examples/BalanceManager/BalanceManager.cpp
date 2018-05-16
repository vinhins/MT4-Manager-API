//+------------------------------------------------------------------+
//|                                  MetaTrader 4 Manager API Sample |
//|                   Copyright 2001-2014, MetaQuotes Software Corp. |
//|                                        http://www.metaquotes.net |
//+------------------------------------------------------------------+
#include "stdafx.h"
#include "BalanceManager.h"
#include "BalanceManagerDlg.h"

//+------------------------------------------------------------------+
//|                                                                  |
//+------------------------------------------------------------------+
CManagerInterface *ExtManager    =NULL;
CManagerInterface *ExtDealer     =NULL;
CManagerInterface *ExtManagerPump=NULL;
volatile UINT      ExtPumpingMsg =0;
volatile UINT      ExtDealingMsg =0;
char               ExtSrv[256];
int                ExtLgn;
char               ExtPwd[17];
//+------------------------------------------------------------------+
//| CBalanceManagerApp                                               |
//+------------------------------------------------------------------+
BEGIN_MESSAGE_MAP(CBalanceManagerApp, CWinApp)
   //{{AFX_MSG_MAP(CBalanceManagerApp)
   //}}AFX_MSG
   ON_COMMAND(ID_HELP, CWinApp::OnHelp)
END_MESSAGE_MAP()
//+------------------------------------------------------------------+
//|                                                                  |
//+------------------------------------------------------------------+
CBalanceManagerApp::CBalanceManagerApp() : m_factory("..\\..\\mtmanapi.dll")
  {
  }
//+------------------------------------------------------------------+
//| The one and only CBalanceManagerApp object                       |
//+------------------------------------------------------------------+
CBalanceManagerApp theApp;
//+------------------------------------------------------------------+
//| CBalanceManagerApp initialization                                |
//+------------------------------------------------------------------+
BOOL CBalanceManagerApp::InitInstance()
  {
   char *cp;
//---
   if(!AfxSocketInit())
     {
      AfxMessageBox(IDP_SOCKETS_INIT_FAILED);
      return(FALSE);
     }
//--- internal message
   ExtPumpingMsg=RegisterWindowMessage("MetaTrader4_Pumping_Message");
   ExtDealingMsg=RegisterWindowMessage("MetaTrader4_Dealing_Message");
//--- create manager api instance
   if(m_factory.IsValid()==FALSE
      || (ExtManager    =m_factory.Create(ManAPIVersion))==NULL
      || (ExtManagerPump=m_factory.Create(ManAPIVersion))==NULL
      || (ExtDealer     =m_factory.Create(ManAPIVersion))==NULL)
     {
      AfxMessageBox("Failed to create MetaTrader 4 Manager API interface.");
      return(FALSE);
     }
//--- create dialog
   CBalanceManagerDlg dlg;
   m_pMainWnd=&dlg;
//--- get application path
   GetModuleFileName(NULL,dlg.m_path,sizeof(dlg.m_path)-1);
   if((cp=strrchr(dlg.m_path, '\\'))!=NULL) *cp=0;
   int nResponse=dlg.DoModal();
//---
   return(FALSE);
  }
//+------------------------------------------------------------------+
//|                                                                  |
//+------------------------------------------------------------------+
int CBalanceManagerApp::ExitInstance()
  {
//---
   if(ExtManager    !=NULL) { ExtManager->Release();     ExtManager    =NULL; }
   if(ExtDealer     !=NULL) { ExtDealer->Release();      ExtDealer     =NULL; }
   if(ExtManagerPump!=NULL) { ExtManagerPump->Release(); ExtManagerPump=NULL; }
//---
   return CWinApp::ExitInstance();
  }
//+------------------------------------------------------------------+
//|                                                                  |
//+------------------------------------------------------------------+

