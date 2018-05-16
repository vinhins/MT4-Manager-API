//+------------------------------------------------------------------+
//|                                      MetaTrader Manager API Test |
//|                   Copyright 2001-2014, MetaQuotes Software Corp. |
//|                                        http://www.metaquotes.net |
//+------------------------------------------------------------------+
#include "stdafx.h"
#include "ManagerAPITest.h"
#include "ManagerAPITestDlg.h"

//---
char               ExtProgramPath[256]="";
CManagerAPITestApp theApp;
//+------------------------------------------------------------------+
//|                                                                  |
//+------------------------------------------------------------------+
BEGIN_MESSAGE_MAP(CManagerAPITestApp, CWinApp)
   //{{AFX_MSG_MAP(CManagerAPITestApp)
   //}}AFX_MSG
   ON_COMMAND(ID_HELP, CWinApp::OnHelp)
END_MESSAGE_MAP()
//+------------------------------------------------------------------+
//|                                                                  |
//+------------------------------------------------------------------+
CManagerAPITestApp::CManagerAPITestApp()
  {
  }
//+------------------------------------------------------------------+
//|                                                                  |
//+------------------------------------------------------------------+
BOOL CManagerAPITestApp::InitInstance()
  {
   char *cp;
//--- parse current folder
   GetModuleFileName((HMODULE)m_hInstance,ExtProgramPath,sizeof(ExtProgramPath)-1);
   if((cp=strrchr(ExtProgramPath,'\\'))!=NULL) *cp=0;
//---
   if(!AfxSocketInit())
     {
      AfxMessageBox(IDP_SOCKETS_INIT_FAILED);
      return(FALSE);
     }
   AfxEnableControlContainer();
//---
   CManagerAPITestDlg dlg;
   m_pMainWnd=&dlg;
   dlg.DoModal();
//---
   return(FALSE);
  }
//+------------------------------------------------------------------+
