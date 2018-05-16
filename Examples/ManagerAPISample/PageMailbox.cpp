//+------------------------------------------------------------------+
//|                                  MetaTrader 4 Manager API Sample |
//|                   Copyright 2001-2014, MetaQuotes Software Corp. |
//|                                        http://www.metaquotes.net |
//+------------------------------------------------------------------+
#include "stdafx.h"
#include "ManagerAPISample.h"
#include "PageMailbox.h"

//+------------------------------------------------------------------+
//|                                                                  |
//+------------------------------------------------------------------+
IMPLEMENT_DYNCREATE(CPageMailbox, CPropertyPageEx)
//+------------------------------------------------------------------+
//|                                                                  |
//+------------------------------------------------------------------+
CPageMailbox::CPageMailbox() : CPropertyPageEx(CPageMailbox::IDD)
  {
   //{{AFX_DATA_INIT(CPageMailbox)
   //}}AFX_DATA_INIT
   m_psp.dwFlags&=~PSP_HASHELP;
  }
//+------------------------------------------------------------------+
//|                                                                  |
//+------------------------------------------------------------------+
CPageMailbox::~CPageMailbox()
  {
  }
//+------------------------------------------------------------------+
//|                                                                  |
//+------------------------------------------------------------------+
void CPageMailbox::DoDataExchange(CDataExchange* pDX)
  {
   CPropertyPageEx::DoDataExchange(pDX);
   //{{AFX_DATA_MAP(CPageMailbox)
   DDX_Control(pDX, IDC_MAILS, m_Mails);
   //}}AFX_DATA_MAP
  }
//+------------------------------------------------------------------+
//|                                                                  |
//+------------------------------------------------------------------+
BEGIN_MESSAGE_MAP(CPageMailbox, CPropertyPageEx)
   //{{AFX_MSG_MAP(CPageMailbox)
   //}}AFX_MSG_MAP
   ON_REGISTERED_MESSAGE(ExtPumpingMsg, OnPumpingMsg)
END_MESSAGE_MAP()
//+------------------------------------------------------------------+
//|                                                                  |
//+------------------------------------------------------------------+
BOOL CPageMailbox::OnInitDialog()
  {
   CRect rc;
   int   cx=0;
//---
   CPropertyPageEx::OnInitDialog();
//---
   m_Mails.SetExtendedStyle(LVS_EX_FULLROWSELECT);
   m_Mails.GetWindowRect(&rc);
   cx=(rc.Width()-::GetSystemMetrics(SM_CXVSCROLL)-::GetSystemMetrics(SM_CXBORDER)*4)/4;
   m_Mails.InsertColumn(0,"Time",   LVCFMT_LEFT,cx);
   m_Mails.InsertColumn(1,"From",   LVCFMT_LEFT,cx);
   m_Mails.InsertColumn(2,"Subject",LVCFMT_LEFT,cx*2);
//---
   return(TRUE);
  }
//+------------------------------------------------------------------+
//|                                                                  |
//+------------------------------------------------------------------+
LRESULT CPageMailbox::OnPumpingMsg(WPARAM wParam,LPARAM)
  {
   char    path[256]="",tmp[256]="";
   int     len =sizeof(path);
   FILE   *in  =NULL;
   MailBox mail={0};
   tm     *ptm =NULL;
//---
   if(wParam==PUMP_UPDATE_MAIL && ExtManagerPump->MailLast(path,&len)==RET_OK)
     {
      if((in=fopen(path,"rb"))!=NULL && fread(&mail,sizeof(mail),1,in)==1)
        {
         if((ptm=gmtime(&mail.time))==NULL) { COPY_STR(tmp,"unknown"); }
         else _snprintf(tmp,sizeof(tmp)-1,"%04d.%02d.%02d %02d:%02d",1900+ptm->tm_year,1+ptm->tm_mon,ptm->tm_mday,ptm->tm_hour,ptm->tm_min);
         m_Mails.InsertItem(0,tmp);
         m_Mails.SetItemText(0,1,mail.from);
         m_Mails.SetItemText(0,2,mail.subject);
        }
      if(in!=NULL) { fclose(in); in=NULL; }
     }
//---
   return(0);
  }
//+------------------------------------------------------------------+
//|                                                                  |
//+------------------------------------------------------------------+
