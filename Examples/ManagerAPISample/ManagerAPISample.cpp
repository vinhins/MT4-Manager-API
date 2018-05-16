//+------------------------------------------------------------------+
//|                                  MetaTrader 4 Manager API Sample |
//|                   Copyright 2001-2014, MetaQuotes Software Corp. |
//|                                        http://www.metaquotes.net |
//+------------------------------------------------------------------+
#include "stdafx.h"
#include "ManagerAPISample.h"
#include "ManagerSheet.h"

//---
CManagerInterface *ExtManager    =NULL;
CManagerInterface *ExtDealer     =NULL;
CManagerInterface *ExtManagerPump=NULL;
volatile UINT      ExtPumpingMsg =0;
volatile UINT      ExtDealingMsg =0;
//+------------------------------------------------------------------+
//|                                                                  |
//+------------------------------------------------------------------+
BEGIN_MESSAGE_MAP(CManagerAPISampleApp, CWinApp)
   //{{AFX_MSG_MAP(CManagerAPISampleApp)
   //}}AFX_MSG
   ON_COMMAND(ID_HELP, CWinApp::OnHelp)
END_MESSAGE_MAP()
//+------------------------------------------------------------------+
//|                                                                  |
//+------------------------------------------------------------------+
CManagerAPISampleApp::CManagerAPISampleApp() : m_factory("..\\..\\mtmanapi.dll")
  {
  }
//+------------------------------------------------------------------+
//|                                                                  |
//+------------------------------------------------------------------+
CManagerAPISampleApp theApp;
//+------------------------------------------------------------------+
//|                                                                  |
//+------------------------------------------------------------------+
BOOL CManagerAPISampleApp::InitInstance()
  {
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
      AfxMessageBox("Failed to create manager interface.");
      return(FALSE);
     }
//---
   CManagerSheet dlg(IDS_TITLE);
   dlg.DoModal();
//---
   return(FALSE);
  }
//+------------------------------------------------------------------+
//|                                                                  |
//+------------------------------------------------------------------+
int CManagerAPISampleApp::ExitInstance()
  {
//---
   if(ExtManager    !=NULL) { ExtManager->Release();     ExtManager    =NULL; }
   if(ExtDealer     !=NULL) { ExtDealer->Release();      ExtDealer     =NULL; }
   if(ExtManagerPump!=NULL) { ExtManagerPump->Release(); ExtManagerPump=NULL; }
//---
   return CWinApp::ExitInstance();
  }
//+------------------------------------------------------------------+
