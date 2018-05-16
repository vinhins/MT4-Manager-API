//+------------------------------------------------------------------+
//|                                  MetaTrader 4 Manager API Sample |
//|                   Copyright 2001-2014, MetaQuotes Software Corp. |
//|                                        http://www.metaquotes.net |
//+------------------------------------------------------------------+
#pragma once

//+------------------------------------------------------------------+
//|                                                                  |
//+------------------------------------------------------------------+
class CRequestDlg : public CDialog
  {
protected:
   int               m_int;

public:
                     CRequestDlg(CWnd *pParent=NULL);
   int               GetInt() const { return(m_int); }

   //{{AFX_DATA(CRequestDlg)
   enum { IDD=IDD_REQUEST };
   CEdit             m_Int;
   CButton           m_All;
   CButton           m_Single;
   //}}AFX_DATA

   //{{AFX_VIRTUAL(CRequestDlg)
protected:
   virtual void      DoDataExchange(CDataExchange* pDX);
   //}}AFX_VIRTUAL

protected:
   //{{AFX_MSG(CRequestDlg)
   virtual BOOL      OnInitDialog();
   afx_msg void      OnAllSingle();
   afx_msg void      OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags);
   virtual void      OnOK();
   //}}AFX_MSG
   DECLARE_MESSAGE_MAP()
  };
//{{AFX_INSERT_LOCATION}}
//+------------------------------------------------------------------+
