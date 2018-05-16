//+------------------------------------------------------------------+
//|                                  MetaTrader 4 Manager API Sample |
//|                   Copyright 2001-2014, MetaQuotes Software Corp. |
//|                                        http://www.metaquotes.net |
//+------------------------------------------------------------------+
#include "stdafx.h"
#include "ManagerAPISample.h"
#include "PagePlugins.h"
//---
//+------------------------------------------------------------------+
//|                                                                  |
//+------------------------------------------------------------------+
IMPLEMENT_DYNCREATE(CPagePlugins, CPropertyPageEx)
//+------------------------------------------------------------------+
//|                                                                  |
//+------------------------------------------------------------------+
CPagePlugins::CPagePlugins() : CPropertyPageEx(CPagePlugins::IDD),
   m_plugins(NULL),m_plugins_total(0)
  {
   //{{AFX_DATA_INIT(CPagePlugins)
   //}}AFX_DATA_INIT
  }
//+------------------------------------------------------------------+
//|                                                                  |
//+------------------------------------------------------------------+
CPagePlugins::~CPagePlugins()
  {
  }
//+------------------------------------------------------------------+
//|                                                                  |
//+------------------------------------------------------------------+
void CPagePlugins::DoDataExchange(CDataExchange* pDX)
  {
   CPropertyPageEx::DoDataExchange(pDX);
   //{{AFX_DATA_MAP(CPagePlugins)
   DDX_Control(pDX, IDC_PLUGINS, m_Plugins);
   //}}AFX_DATA_MAP
  }
//+------------------------------------------------------------------+
//|                                                                  |
//+------------------------------------------------------------------+
BEGIN_MESSAGE_MAP(CPagePlugins, CPropertyPageEx)
   //{{AFX_MSG_MAP(CPagePlugins)
   ON_NOTIFY(LVN_GETDISPINFO, IDC_PLUGINS, OnGetdispinfoPlugins)
   ON_WM_DESTROY()
   //}}AFX_MSG_MAP
   ON_REGISTERED_MESSAGE(ExtPumpingMsg, OnPumpingMsg)
END_MESSAGE_MAP()
//+------------------------------------------------------------------+
//|                                                                  |
//+------------------------------------------------------------------+
BOOL CPagePlugins::OnInitDialog()
  {
   CRect rc;
   int   cx=0;
//---
   CPropertyPageEx::OnInitDialog();
//---
   m_Plugins.GetClientRect(&rc);
   cx=(rc.Width()-::GetSystemMetrics(SM_CXVSCROLL)-::GetSystemMetrics(SM_CXBORDER)*3)/3;
   m_Plugins.SetExtendedStyle(LVS_EX_FULLROWSELECT);
   m_Plugins.InsertColumn(0,"Name", LVCFMT_LEFT,cx);
   m_Plugins.InsertColumn(1,"Version",LVCFMT_RIGHT,cx);
   m_Plugins.InsertColumn(2,"File",  LVCFMT_RIGHT,cx);
//---
   return(TRUE);
  }
//+------------------------------------------------------------------+
//|                                                                  |
//+------------------------------------------------------------------+
void CPagePlugins::OnDestroy()
  {
//---
   if(m_plugins!=NULL) { ExtManagerPump->MemFree(m_plugins); m_plugins=NULL; m_plugins_total=0; }
//---
   CPropertyPageEx::OnDestroy();
  }
//+------------------------------------------------------------------+
//|                                                                  |
//+------------------------------------------------------------------+
void CPagePlugins::OnGetdispinfoPlugins(NMHDR *pNMHDR, LRESULT* pResult)
  {
   LV_DISPINFO* pDI=(LV_DISPINFO*)pNMHDR;
   if(pResult!=NULL) *pResult=0;
//---
   char tmp[256]="";
   int  i=pDI->item.iItem;
   if(i<0 || i>=m_plugins_total) return;
//---
   if(pDI->item.mask&LVIF_TEXT)
     {
      switch(pDI->item.iSubItem)
        {
         case 0: COPY_STR(tmp,m_plugins[i].info.name); break;
         case 1: _snprintf(tmp,sizeof(tmp)-1,"%d.%02d",m_plugins[i].info.version/100,m_plugins[i].info.version%100); break;
         case 2: COPY_STR(tmp,m_plugins[i].file);      break;
         default: break;
        }
      pDI->item.pszText=tmp;
     }
//---
  }
//+------------------------------------------------------------------+
//|                                                                  |
//+------------------------------------------------------------------+
LRESULT CPagePlugins::OnPumpingMsg(WPARAM wParam,LPARAM)
  {
//---
   if(wParam==PUMP_UPDATE_PLUGINS)
     {
      if(m_plugins!=NULL)
        {
         ExtManagerPump->MemFree(m_plugins);
         m_plugins=NULL; m_plugins_total=0;
        }
      m_plugins=ExtManagerPump->PluginsGet(&m_plugins_total);
      m_Plugins.SetItemCount(m_plugins_total);
     }
//---
   return(0);
  }
//+------------------------------------------------------------------+
//|                                                                  |
//+------------------------------------------------------------------+
