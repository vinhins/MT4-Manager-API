//+------------------------------------------------------------------+
//|                                      MetaTrader Manager API Test |
//|                   Copyright 2001-2014, MetaQuotes Software Corp. |
//|                                        http://www.metaquotes.net |
//+------------------------------------------------------------------+
#pragma once
//---
#ifndef __AFXWIN_H__
   #error include 'stdafx.h' before including this file for PCH
#endif
#include "resource.h"      // main symbols
//---
extern char ExtProgramPath[256];
//+------------------------------------------------------------------+
//|                                                                  |
//+------------------------------------------------------------------+
class CManagerAPITestApp : public CWinApp
  {
public:
                     CManagerAPITestApp();

   //{{AFX_VIRTUAL(CManagerAPITestApp)
public:
   virtual BOOL      InitInstance();
   //}}AFX_VIRTUAL

   //{{AFX_MSG(CManagerAPITestApp)
   //}}AFX_MSG
   DECLARE_MESSAGE_MAP()
  };
//{{AFX_INSERT_LOCATION}}
//+------------------------------------------------------------------+
