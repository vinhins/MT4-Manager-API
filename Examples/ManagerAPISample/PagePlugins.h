//+------------------------------------------------------------------+
//|                                  MetaTrader 4 Manager API Sample |
//|                   Copyright 2001-2014, MetaQuotes Software Corp. |
//|                                        http://www.metaquotes.net |
//+------------------------------------------------------------------+
#pragma once
//+------------------------------------------------------------------+
//|                                                                  |
//+------------------------------------------------------------------+
class CPagePlugins : public CPropertyPageEx
  {
   DECLARE_DYNCREATE(CPagePlugins)
private:
   ConPlugin        *m_plugins;
   int               m_plugins_total;

public:
                     CPagePlugins();
                    ~CPagePlugins();

   //{{AFX_DATA(CPagePlugins)
   enum { IDD=IDD_MANAGER_PLUGINS };
   CListCtrl         m_Plugins;
   //}}AFX_DATA

   //{{AFX_VIRTUAL(CPagePlugins)
protected:
   virtual void      DoDataExchange(CDataExchange* pDX);
   //}}AFX_VIRTUAL

protected:
   //{{AFX_MSG(CPagePlugins)
   virtual BOOL      OnInitDialog();
   afx_msg void      OnGetdispinfoPlugins(NMHDR *pNMHDR, LRESULT* pResult);
   afx_msg void      OnDestroy();
   //}}AFX_MSG
   afx_msg LRESULT   OnPumpingMsg(WPARAM wParam,LPARAM lParam);
   DECLARE_MESSAGE_MAP()
  };
//{{AFX_INSERT_LOCATION}}
//+------------------------------------------------------------------+
