//+------------------------------------------------------------------+
//|                                  MetaTrader 4 Manager API Sample |
//|                   Copyright 2001-2014, MetaQuotes Software Corp. |
//|                                        http://www.metaquotes.net |
//+------------------------------------------------------------------+
#pragma once

//+------------------------------------------------------------------+
//|                                                                  |
//+------------------------------------------------------------------+
class CMailSendDlg : public CDialog
  {
private:
   ConManager        m_man;

public:
                     CMailSendDlg(const ConManager *man,CWnd *pParent=NULL);

   //{{AFX_DATA(CMailSendDlg)
   enum { IDD=IDD_MAIL_SEND };
   CEdit             m_Subject;
   CEdit             m_Recepient;
   CEdit             m_Body;
   //}}AFX_DATA

   //{{AFX_VIRTUAL(CMailSendDlg)
protected:
   virtual void      DoDataExchange(CDataExchange* pDX);
   //}}AFX_VIRTUAL

protected:
   //{{AFX_MSG(CMailSendDlg)
   afx_msg void      OnSend();
   //}}AFX_MSG
   DECLARE_MESSAGE_MAP()
  };
//{{AFX_INSERT_LOCATION}}
//+------------------------------------------------------------------+
