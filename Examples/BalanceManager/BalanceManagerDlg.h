//+------------------------------------------------------------------+
//|                                  MetaTrader 4 Manager API Sample |
//|                   Copyright 2001-2014, MetaQuotes Software Corp. |
//|                                        http://www.metaquotes.net |
//+------------------------------------------------------------------+
#pragma once
//+------------------------------------------------------------------+
//| Balance change dialog                                            |
//+------------------------------------------------------------------+
class CBalanceManagerDlg : public CDialog
  {
public:
   int               m_itemnum;
   char              m_path[_MAX_PATH];

public:
                     CBalanceManagerDlg(CWnd *pParent=NULL);
   void              LogMessage(int errorcode, char *msg);
   bool              CheckLogDir();

   //{{AFX_DATA(CBalanceManagerDlg)
   enum { IDD=IDD_BALANCEMANAGER_DIALOG };
   CListCtrl         m_log;
   CEdit             m_comment;
   CEdit             m_value;
   CEdit             m_client;
   //}}AFX_DATA

   //{{AFX_VIRTUAL(CBalanceManagerDlg)
protected:
   virtual void      DoDataExchange(CDataExchange* pDX);
   //}}AFX_VIRTUAL

protected:
   HICON             m_hIcon;

   //{{AFX_MSG(CBalanceManagerDlg)
   virtual BOOL      OnInitDialog();
   afx_msg void      OnPaint();
   afx_msg HCURSOR   OnQueryDragIcon();
   afx_msg void      OnSettings();
   afx_msg void      OnRequest();
   afx_msg void      OnExit();
   afx_msg void      OnDeposit();
   afx_msg void      OnWithdrawal();
   //}}AFX_MSG
   DECLARE_MESSAGE_MAP()
  };
//{{AFX_INSERT_LOCATION}}
//+------------------------------------------------------------------+
