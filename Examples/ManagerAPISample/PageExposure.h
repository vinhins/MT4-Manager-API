//+------------------------------------------------------------------+
//|                                  MetaTrader 4 Manager API Sample |
//|                   Copyright 2001-2014, MetaQuotes Software Corp. |
//|                                        http://www.metaquotes.net |
//+------------------------------------------------------------------+
#pragma once
//+------------------------------------------------------------------+
//|                                                                  |
//+------------------------------------------------------------------+
class CPageExposure : public CPropertyPageEx
  {
   DECLARE_DYNCREATE(CPageExposure)
private:
   ExposureValue    *m_exposure;
   int               m_exposure_total;

public:
                     CPageExposure();
                    ~CPageExposure();

   //{{AFX_DATA(CPageExposure)
   enum { IDD=IDD_MANAGER_EXPOSURE };
   CListCtrl         m_Exposure;
   //}}AFX_DATA

   //{{AFX_VIRTUAL(CPageExposure)
protected:
   virtual void      DoDataExchange(CDataExchange* pDX);
   //}}AFX_VIRTUAL

protected:
   //{{AFX_MSG(CPageExposure)
   virtual BOOL      OnInitDialog();
   afx_msg void      OnDestroy();
   afx_msg void      OnGetdispinfoExposure(NMHDR *pNMHDR, LRESULT* pResult);
   //}}AFX_MSG
   afx_msg LRESULT   OnPumpingMsg(WPARAM wParam,LPARAM lParam);
   DECLARE_MESSAGE_MAP()
  };
//{{AFX_INSERT_LOCATION}}
//+------------------------------------------------------------------+
