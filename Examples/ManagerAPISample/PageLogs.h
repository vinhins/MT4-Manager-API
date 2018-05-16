//+------------------------------------------------------------------+
//|                                  MetaTrader 4 Manager API Sample |
//|                   Copyright 2001-2014, MetaQuotes Software Corp. |
//|                                        http://www.metaquotes.net |
//+------------------------------------------------------------------+
#pragma once

//+------------------------------------------------------------------+
//|                                                                  |
//+------------------------------------------------------------------+
class CPageLogs : public CPropertyPageEx
  {
   DECLARE_DYNCREATE(CPageLogs)

public:
                     CPageLogs();
                    ~CPageLogs();

   void              LogOut(LPCSTR str);

   //{{AFX_DATA(CPageLogs)
   enum { IDD=IDD_MANAGER_LOGS };
   CListCtrl         m_Logs;
   //}}AFX_DATA

   //{{AFX_VIRTUAL(CPageLogs)
protected:
   virtual void      DoDataExchange(CDataExchange* pDX);
   //}}AFX_VIRTUAL

protected:
   //{{AFX_MSG(CPageLogs)
   virtual BOOL      OnInitDialog();
   //}}AFX_MSG
   DECLARE_MESSAGE_MAP()
  };
//{{AFX_INSERT_LOCATION}}
//+------------------------------------------------------------------+
