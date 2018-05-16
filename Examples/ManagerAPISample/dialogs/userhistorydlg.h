//+------------------------------------------------------------------+
//|                                  MetaTrader 4 Manager API Sample |
//|                   Copyright 2001-2014, MetaQuotes Software Corp. |
//|                                        http://www.metaquotes.net |
//+------------------------------------------------------------------+
#pragma once

class CUserHistoryDlg : public CDialog
  {
private:
   int               m_login;
   time_t            m_from;
   time_t            m_to;

public:
                     CUserHistoryDlg(CWnd *pParent=NULL);
   int               GetLogin() const { return(m_login); }
   int               GetFrom()  const { return(m_from);  }
   int               GetTo()    const { return(m_to);    }

   //{{AFX_DATA(CUserHistoryDlg)
   enum { IDD=IDD_USER_HISTORY };
   CDateTimeCtrl     m_To;
   CEdit             m_Login;
   CDateTimeCtrl     m_From;
   //}}AFX_DATA

   //{{AFX_VIRTUAL(CUserHistoryDlg)
protected:
   virtual void      DoDataExchange(CDataExchange* pDX);
   //}}AFX_VIRTUAL

protected:
   //{{AFX_MSG(CUserHistoryDlg)
   virtual BOOL      OnInitDialog();
   virtual void      OnOK();
   //}}AFX_MSG
   DECLARE_MESSAGE_MAP()
  };
//{{AFX_INSERT_LOCATION}}
//+------------------------------------------------------------------+
