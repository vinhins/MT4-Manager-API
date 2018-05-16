//+------------------------------------------------------------------+
//|                                  MetaTrader 4 Manager API Sample |
//|                   Copyright 2001-2014, MetaQuotes Software Corp. |
//|                                        http://www.metaquotes.net |
//+------------------------------------------------------------------+
#include "stdafx.h"
#include "..\ManagerAPISample.h"
#include "MailSendDlg.h"

//+------------------------------------------------------------------+
//|                                                                  |
//+------------------------------------------------------------------+
CMailSendDlg::CMailSendDlg(const ConManager *man,CWnd *pParent) : CDialog(CMailSendDlg::IDD, pParent)
  {
   //{{AFX_DATA_INIT(CMailSendDlg)
   //}}AFX_DATA_INIT
   if(man!=NULL) memcpy(&m_man,man,sizeof(m_man));
   else          memset(&m_man,0,sizeof(m_man));
  }
//+------------------------------------------------------------------+
//|                                                                  |
//+------------------------------------------------------------------+
void CMailSendDlg::DoDataExchange(CDataExchange* pDX)
  {
   CDialog::DoDataExchange(pDX);
   //{{AFX_DATA_MAP(CMailSendDlg)
   DDX_Control(pDX, IDC_SUBJECT, m_Subject);
   DDX_Control(pDX, IDC_RECEPIENT, m_Recepient);
   DDX_Control(pDX, IDC_BODY, m_Body);
   //}}AFX_DATA_MAP
  }
//+------------------------------------------------------------------+
//|                                                                  |
//+------------------------------------------------------------------+
BEGIN_MESSAGE_MAP(CMailSendDlg, CDialog)
   //{{AFX_MSG_MAP(CMailSendDlg)
   ON_BN_CLICKED(IDC_SEND, OnSend)
   //}}AFX_MSG_MAP
END_MESSAGE_MAP()
//+------------------------------------------------------------------+
//|                                                                  |
//+------------------------------------------------------------------+
void CMailSendDlg::OnSend()
  {
   MailBox mail={0};
   CString str;
   int    *logins=NULL,total=0,res;
//--- заголовок письма
   mail.sender=m_man.login;
   COPY_STR(mail.from,m_man.mailbox);
   m_Subject.GetWindowText(mail.subject,sizeof(mail.subject)-1);
//--- получатели
   if((logins=new int[1024])==NULL)
     {
      MessageBox("Send mail: Out of meory");
      return;
     }
   m_Recepient.GetWindowText(str);
   while(total<1024)
     {
      logins[total++]=atoi(str);
      if(logins[total-1]<=0) total-=1;
      if((res=str.Find(_T(',')))!=-1) str=str.Mid(res+1);
      else break;
     }
   if(total==0)
     {
      delete[] logins;
      return;
     }
   mail.to=total;
//--- подготовим буфер с текстом
   if((mail.bodylen=m_Body.GetWindowTextLength())<1)
     {
      delete[] logins;
      return;
     }
   if((mail.body=new char[mail.bodylen+16])==NULL)
     {
      MessageBox("Send mail: Out of meory");
      delete[] logins;
      return;
     }
   m_Body.GetWindowText(mail.body,mail.bodylen+2);
   mail.body[mail.bodylen]=0;
//---
   res=ExtManager->MailSend(&mail,logins);
   MessageBox(ExtManager->ErrorDescription(res),"MailSend");
//---
   if(logins   !=NULL) { delete[] logins;    logins   =NULL; }
   if(mail.body!=NULL) { delete[] mail.body; mail.body=NULL; }
   if(res==RET_OK) EndDialog(IDOK);
  }
//+------------------------------------------------------------------+
//|                                                                  |
//+------------------------------------------------------------------+
