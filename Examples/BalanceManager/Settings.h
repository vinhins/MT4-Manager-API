//+------------------------------------------------------------------+
//|                                  MetaTrader 4 Manager API Sample |
//|                   Copyright 2001-2014, MetaQuotes Software Corp. |
//|                                        http://www.metaquotes.net |
//+------------------------------------------------------------------+
#pragma once
//+------------------------------------------------------------------+
//| Settings dialog                                                  |
//+------------------------------------------------------------------+
class Settings : public CDialog
  {
public:
                     Settings(CWnd *pParent=NULL);
   //{{AFX_DATA(Settings)
   enum { IDD=IDD_SETTINGS };
   CEdit             m_login;
   CEdit             m_password;
   CEdit             m_server;
   //}}AFX_DATA

   //{{AFX_VIRTUAL(Settings)
protected:
   virtual void      DoDataExchange(CDataExchange* pDX);
   //}}AFX_VIRTUAL

protected:
   //{{AFX_MSG(Settings)
   virtual void      OnOK();
   afx_msg void      OnPaint();
   //}}AFX_MSG
   DECLARE_MESSAGE_MAP()
  };
//{{AFX_INSERT_LOCATION}}
//+------------------------------------------------------------------+
