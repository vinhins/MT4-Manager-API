//+------------------------------------------------------------------+
//|                                  MetaTrader 4 Manager API Sample |
//|                   Copyright 2001-2014, MetaQuotes Software Corp. |
//|                                        http://www.metaquotes.net |
//+------------------------------------------------------------------+
#include "stdafx.h"
#include "ManagerAPISample.h"
#include "PageNews.h"

//+------------------------------------------------------------------+
//|                                                                  |
//+------------------------------------------------------------------+
IMPLEMENT_DYNCREATE(CPageNews, CPropertyPageEx)
//+------------------------------------------------------------------+
//|                                                                  |
//+------------------------------------------------------------------+
CPageNews::CPageNews() : CPropertyPageEx(CPageNews::IDD)
  {
   //{{AFX_DATA_INIT(CPageNews)
   //}}AFX_DATA_INIT
   m_psp.dwFlags&=~PSP_HASHELP;
  }
//+------------------------------------------------------------------+
//|                                                                  |
//+------------------------------------------------------------------+
CPageNews::~CPageNews()
  {
  }
//+------------------------------------------------------------------+
//|                                                                  |
//+------------------------------------------------------------------+
void CPageNews::DoDataExchange(CDataExchange* pDX)
  {
   CPropertyPageEx::DoDataExchange(pDX);
   //{{AFX_DATA_MAP(CPageNews)
   DDX_Control(pDX, IDC_NEWS, m_News);
   //}}AFX_DATA_MAP
  }
//+------------------------------------------------------------------+
//|                                                                  |
//+------------------------------------------------------------------+
BEGIN_MESSAGE_MAP(CPageNews, CPropertyPageEx)
   //{{AFX_MSG_MAP(CPageNews)
   ON_NOTIFY(LVN_GETDISPINFO, IDC_NEWS, OnGetdispinfoNews)
   //}}AFX_MSG_MAP
   ON_REGISTERED_MESSAGE(ExtPumpingMsg, OnPumpingMsg)
END_MESSAGE_MAP()
//+------------------------------------------------------------------+
//|                                                                  |
//+------------------------------------------------------------------+
BOOL CPageNews::OnInitDialog()
  {
   CRect rc;
   int   cx=0;
//---
   CPropertyPageEx::OnInitDialog();
//---
   m_News.SetExtendedStyle(LVS_EX_FULLROWSELECT);
   m_News.GetWindowRect(&rc);
   cx=(rc.Width()-::GetSystemMetrics(SM_CXVSCROLL)-::GetSystemMetrics(SM_CXBORDER)*4)/4;
   m_News.InsertColumn(0,"Time",    LVCFMT_LEFT,cx);
   m_News.InsertColumn(1,"Subject", LVCFMT_LEFT,cx*2);
   m_News.InsertColumn(2,"Category",LVCFMT_LEFT,cx);
//---
   return(TRUE);
  }
//+------------------------------------------------------------------+
//|                                                                  |
//+------------------------------------------------------------------+
LRESULT CPageNews::OnPumpingMsg(WPARAM wParam,LPARAM)
  {
//---
   if(wParam==PUMP_UPDATE_NEWS)
     {
      m_News.SetItemCount(ExtManagerPump->NewsTotal());
     }
//---
   return(0);
  }
//+------------------------------------------------------------------+
//|                                                                  |
//+------------------------------------------------------------------+
void CPageNews::OnGetdispinfoNews(NMHDR *pNMHDR,LRESULT *pResult)
  {
   LV_DISPINFO* pDI=(LV_DISPINFO*)pNMHDR;
   if(pResult!=NULL) *pResult=0;
//---
   NewsTopic news={0};
   char      tmp[256]="";
   int       i=pDI->item.iItem;
   if(ExtManagerPump->NewsTopicGet(i,&news)!=RET_OK) return;
//---
   if(pDI->item.mask&LVIF_TEXT)
     {
      switch(pDI->item.iSubItem)
        {
         case 0: COPY_STR(tmp,news.ctm);      break;
         case 1: COPY_STR(tmp,news.topic);    break;
         case 2: COPY_STR(tmp,news.category); break;
         default: break;
        }
      pDI->item.pszText=tmp;
     }
//---
  }
//+------------------------------------------------------------------+
//|                                                                  |
//+------------------------------------------------------------------+
