//+------------------------------------------------------------------+
//|                                  MetaTrader 4 Manager API Sample |
//|                   Copyright 2001-2014, MetaQuotes Software Corp. |
//|                                        http://www.metaquotes.net |
//+------------------------------------------------------------------+
#include "stdafx.h"
#include "..\ManagerAPISample.h"
#include "symbolchangedlg.h"

//+------------------------------------------------------------------+
//|                                                                  |
//+------------------------------------------------------------------+
CSymbolChangeDlg::CSymbolChangeDlg(const SymbolProperties *prop,CWnd *pParent) : CDialog(CSymbolChangeDlg::IDD, pParent)
  {
   //{{AFX_DATA_INIT(CSymbolChangeDlg)
   //}}AFX_DATA_INIT
   if(prop!=NULL) memcpy(&m_prop,prop,sizeof(m_prop));
   else           memset(&m_prop,0,sizeof(m_prop));
  }
//+------------------------------------------------------------------+
//|                                                                  |
//+------------------------------------------------------------------+
void CSymbolChangeDlg::DoDataExchange(CDataExchange* pDX)
  {
   CDialog::DoDataExchange(pDX);
   //{{AFX_DATA_MAP(CSymbolChangeDlg)
   DDX_Control(pDX, IDC_STOPS, m_Stops);
   DDX_Control(pDX, IDC_SPREAD, m_Spread);
   DDX_Control(pDX, IDC_EXEMODE, m_ExeMode);
   //}}AFX_DATA_MAP
  }
//+------------------------------------------------------------------+
//|                                                                  |
//+------------------------------------------------------------------+
BEGIN_MESSAGE_MAP(CSymbolChangeDlg, CDialog)
   //{{AFX_MSG_MAP(CSymbolChangeDlg)
   //}}AFX_MSG_MAP
END_MESSAGE_MAP()
//+------------------------------------------------------------------+
//|                                                                  |
//+------------------------------------------------------------------+
BOOL CSymbolChangeDlg::OnInitDialog()
  {
   CDialog::OnInitDialog();
//---
   if(m_prop.symbol[0]==0)
     {
      EndDialog(IDCANCEL);
      return(FALSE);
     }
//---
   SetWindowText(m_prop.symbol);
   m_ExeMode.SetCurSel(m_prop.exemode);
   SetDlgItemInt(m_Stops.GetDlgCtrlID(),m_prop.stops_level,FALSE);
   SetDlgItemInt(m_Spread.GetDlgCtrlID(),m_prop.spread,FALSE);
//---
   return(TRUE);
  }
//+------------------------------------------------------------------+
//|                                                                  |
//+------------------------------------------------------------------+
void CSymbolChangeDlg::OnOK()
  {
//---
   m_prop.exemode    =m_ExeMode.GetCurSel();
   m_prop.stops_level=GetDlgItemInt(m_Stops.GetDlgCtrlID(),NULL,FALSE);
   m_prop.spread     =GetDlgItemInt(m_Spread.GetDlgCtrlID(),NULL,FALSE);
//--- if you want change spread balance and color
   //   m_prop.spread_balance=whatever you want;
   //   m_prop.color         =whatever you want;
//---
   int res=ExtManager->SymbolChange(&m_prop);
   MessageBox(ExtManager->ErrorDescription(res),"SymbolChange");
//---
   if(res==RET_OK) CDialog::OnOK();
  }
//+------------------------------------------------------------------+
//|                                                                  |
//+------------------------------------------------------------------+
