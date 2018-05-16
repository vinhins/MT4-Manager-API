//+------------------------------------------------------------------+
//|                                  MetaTrader 4 Manager API Sample |
//|                   Copyright 2001-2014, MetaQuotes Software Corp. |
//|                                        http://www.metaquotes.net |
//+------------------------------------------------------------------+
#include "stdafx.h"
#include "..\ManagerAPISample.h"
#include "NewsSendDlg.h"

//+------------------------------------------------------------------+
//|                                                                  |
//+------------------------------------------------------------------+
CNewsSendDlg::CNewsSendDlg(CWnd *pParent) : CDialog(CNewsSendDlg::IDD, pParent)
  {
   //{{AFX_DATA_INIT(CNewsSendDlg)
   //}}AFX_DATA_INIT
  }
//+------------------------------------------------------------------+
//|                                                                  |
//+------------------------------------------------------------------+
void CNewsSendDlg::DoDataExchange(CDataExchange* pDX)
  {
   CDialog::DoDataExchange(pDX);
   //{{AFX_DATA_MAP(CNewsSendDlg)
   DDX_Control(pDX, IDC_SUBJECT, m_Subject);
   DDX_Control(pDX, IDC_CATEGORY, m_Category);
   DDX_Control(pDX, IDC_HIGH, m_High);
   DDX_Control(pDX, IDC_BODY, m_Body);
   //}}AFX_DATA_MAP
  }
//+------------------------------------------------------------------+
//|                                                                  |
//+------------------------------------------------------------------+
BEGIN_MESSAGE_MAP(CNewsSendDlg, CDialog)
   //{{AFX_MSG_MAP(CNewsSendDlg)
   ON_BN_CLICKED(IDC_SEND, OnSend)
   //}}AFX_MSG_MAP
END_MESSAGE_MAP()
//+------------------------------------------------------------------+
//|                                                                  |
//+------------------------------------------------------------------+
void CNewsSendDlg::OnSend()
  {
   NewsTopic news={0};
   int       res =RET_ERROR;
//--- Проверяем данные
   if(m_Subject.GetWindowTextLength()<1) return;
//--- Категория/Тема/Приоритет
   m_Category.GetWindowText(news.category,sizeof(news.category)-1);
   m_Subject.GetWindowText(news.topic,sizeof(news.topic)-1);
   news.priority=(m_High.GetCheck()==BST_CHECKED)?TRUE:FALSE;
//--- читаем его
   news.bodylen=m_Body.GetWindowTextLength()+1;
   if((news.body=new char[news.bodylen+32])==NULL)
      return;
   m_Body.GetWindowText(news.body,news.bodylen);
   news.body[news.bodylen]=0;
//--- Отправляем
   res=ExtManager->NewsSend(&news);
   MessageBox(ExtManager->ErrorDescription(res),"NewsSend");
//---
   if(res==RET_OK) EndDialog(IDOK);
  }
//+------------------------------------------------------------------+
