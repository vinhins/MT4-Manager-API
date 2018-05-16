//+------------------------------------------------------------------+
//|                                  MetaTrader 4 Manager API Sample |
//|                   Copyright 2001-2014, MetaQuotes Software Corp. |
//|                                        http://www.metaquotes.net |
//+------------------------------------------------------------------+
#pragma once

//+------------------------------------------------------------------+
//|                                                                  |
//+------------------------------------------------------------------+
class CNewsSendDlg : public CDialog
  {
public:
                     CNewsSendDlg(CWnd *pParent=NULL);

   //{{AFX_DATA(CNewsSendDlg)
   enum { IDD=IDD_NEWS_SEND };
   CEdit             m_Subject;
   CEdit             m_Category;
   CButton           m_High;
   CEdit             m_Body;
   //}}AFX_DATA

   //{{AFX_VIRTUAL(CNewsSendDlg)
protected:
   virtual void      DoDataExchange(CDataExchange* pDX);
   //}}AFX_VIRTUAL

protected:
   //{{AFX_MSG(CNewsSendDlg)
   afx_msg void      OnSend();
   //}}AFX_MSG
   DECLARE_MESSAGE_MAP()
  };
//{{AFX_INSERT_LOCATION}}
//+------------------------------------------------------------------+
