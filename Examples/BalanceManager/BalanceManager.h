//+------------------------------------------------------------------+
//|                                  MetaTrader 4 Manager API Sample |
//|                   Copyright 2001-2014, MetaQuotes Software Corp. |
//|                                        http://www.metaquotes.net |
//+------------------------------------------------------------------+
#pragma once
#ifndef __AFXWIN_H__
   #error include 'stdafx.h' before including this file for PCH
#endif
#include "resource.h"
#include "..\MT4ManagerAPI.h"
//+------------------------------------------------------------------+
//| Global Variables                                                 |
//+------------------------------------------------------------------+
extern CManagerInterface *ExtManager;
extern CManagerInterface *ExtDealer;
extern CManagerInterface *ExtManagerPump;
extern volatile UINT      ExtPumpingMsg;
extern volatile UINT      ExtDealingMsg;
extern char               ExtSrv[256];
extern int                ExtLgn;
extern char               ExtPwd[17];
//+------------------------------------------------------------------+
//| CBalanceManagerApp                                               |
//+------------------------------------------------------------------+
class CBalanceManagerApp : public CWinApp
  {
private:
   CManagerFactory   m_factory;

public:
                     CBalanceManagerApp();
   //{{AFX_VIRTUAL(CBalanceManagerApp)
public:
   virtual BOOL      InitInstance();
   virtual int       ExitInstance();
   //}}AFX_VIRTUAL
   //{{AFX_MSG(CBalanceManagerApp)
   //}}AFX_MSG
   DECLARE_MESSAGE_MAP()
  };
//+------------------------------------------------------------------+
