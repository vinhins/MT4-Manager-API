//+------------------------------------------------------------------+
//|                                  MetaTrader 4 Manager API Sample |
//|                   Copyright 2001-2014, MetaQuotes Software Corp. |
//|                                        http://www.metaquotes.net |
//+------------------------------------------------------------------+
#include "stdafx.h"
#include "BalanceManager.h"
#include "BalanceManagerDlg.h"
#include "Settings.h"

//+------------------------------------------------------------------+
//| CBalanceManagerDlg dialog                                        |
//+------------------------------------------------------------------+
CBalanceManagerDlg::CBalanceManagerDlg(CWnd *pParent) : CDialog(CBalanceManagerDlg::IDD, pParent)
  {
   //{{AFX_DATA_INIT(CBalanceManagerDlg)
   //}}AFX_DATA_INIT
   // Note that LoadIcon does not require a subsequent DestroyIcon in Win32
   m_hIcon=AfxGetApp()->LoadIcon(IDR_MAINFRAME);
  }
//+------------------------------------------------------------------+
//|                                                                  |
//+------------------------------------------------------------------+
void CBalanceManagerDlg::DoDataExchange(CDataExchange* pDX)
  {
   CDialog::DoDataExchange(pDX);
   //{{AFX_DATA_MAP(CBalanceManagerDlg)
   DDX_Control(pDX, IDC_LOG, m_log);
   DDX_Control(pDX, IDC_COMMENT, m_comment);
   DDX_Control(pDX, IDC_AMOUNT, m_value);
   DDX_Control(pDX, IDC_CLIENT, m_client);
   //}}AFX_DATA_MAP
  }
//+------------------------------------------------------------------+
//|                                                                  |
//+------------------------------------------------------------------+
BEGIN_MESSAGE_MAP(CBalanceManagerDlg, CDialog)
   //{{AFX_MSG_MAP(CBalanceManagerDlg)
   ON_WM_PAINT()
   ON_WM_QUERYDRAGICON()
   ON_BN_CLICKED(IDC_SETTINGS, OnSettings)
   ON_BN_CLICKED(IDC_REQUEST, OnRequest)
   ON_BN_CLICKED(IDC_EXIT, OnExit)
   ON_BN_CLICKED(IDC_DEPOSIT, OnDeposit)
   ON_BN_CLICKED(IDC_WITHDRAWAL, OnWithdrawal)
   //}}AFX_MSG_MAP
END_MESSAGE_MAP()
//+------------------------------------------------------------------+
//|                                                                  |
//+------------------------------------------------------------------+
BOOL CBalanceManagerDlg::OnInitDialog()
  {
   CRect rc;
   int   cx=0;
//---
   CDialog::OnInitDialog();
//---
   SetIcon(m_hIcon, TRUE);      // Set big icon
   SetIcon(m_hIcon, FALSE);     // Set small icon
//--- create log
   m_log.SetExtendedStyle(LVS_EX_FULLROWSELECT);
   m_log.GetWindowRect(&rc);
   cx=(rc.Width()-::GetSystemMetrics(SM_CXVSCROLL)-::GetSystemMetrics(SM_CXBORDER)*4)/8;
   m_log.InsertColumn(0,"Time",   LVCFMT_LEFT,cx);
   m_log.InsertColumn(1,"Client", LVCFMT_LEFT,cx*2);
   m_log.InsertColumn(2,"Message",LVCFMT_LEFT,cx*5);
   m_itemnum=0;
//---
   return(TRUE);
  }
//+------------------------------------------------------------------+
//|                                                                  |
//+------------------------------------------------------------------+
void CBalanceManagerDlg::OnPaint()
  {
   if(IsIconic())
     {
      CPaintDC dc(this);
      SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);
      //---
      int cxIcon=GetSystemMetrics(SM_CXICON);
      int cyIcon=GetSystemMetrics(SM_CYICON);
      CRect rect;
      GetClientRect(&rect);
      int x=(rect.Width() - cxIcon + 1)/2;
      int y=(rect.Height() - cyIcon + 1)/2;
      //--- draw the icon
      dc.DrawIcon(x, y, m_hIcon);
     }
   else
     {
      CDialog::OnPaint();
     }
  }
//+------------------------------------------------------------------+
//|                                                                  |
//+------------------------------------------------------------------+
HCURSOR CBalanceManagerDlg::OnQueryDragIcon()
  {
   return(HCURSOR) m_hIcon;
  }
//+------------------------------------------------------------------+
//| Call dialog for server/login/password settings                   |
//+------------------------------------------------------------------+
void CBalanceManagerDlg::OnSettings()
  {
   Settings dlg;
   dlg.DoModal();
  }
//+------------------------------------------------------------------+
//| Connect to server (if needed) and request selected user record   |
//+------------------------------------------------------------------+
void CBalanceManagerDlg::OnRequest()
  {
   int         res;
   int         login;
   UserRecord *users;
   int         users_total;
   char        tmp[32];
//---
   login=GetDlgItemInt(m_client.GetDlgCtrlID(),NULL,FALSE);
   if(!login)
     {
      ::MessageBeep(-1);
      m_client.SetFocus();
      return;
     }
//---
   AfxGetApp()->BeginWaitCursor();
//---
   if(ExtManager->IsConnected())
      ExtManager->Disconnect();

   if((res=ExtManager->Connect(ExtSrv))==RET_OK)
     {
      res=ExtManager->Login(ExtLgn,ExtPwd);
      if(res!=RET_OK)
        {
         LogMessage(res,"Login failed"); // login failed
         AfxGetApp()->EndWaitCursor();
         return;
        }
     }
   else
     {
      LogMessage(res,"Connect failed");  // connect failed
      AfxGetApp()->EndWaitCursor();
      return;
     }
//--- Get user data
   users_total=1;
   users=ExtManager->UserRecordsRequest(&login,&users_total);
   if(users!=NULL)
     {
      //--- fill controls
      SetDlgItemText(IDC_NAME,users->name);
      SetDlgItemText(IDC_COUNTRY,users->country);
      SetDlgItemText(IDC_CITY,users->city);
      sprintf(tmp,"%.2f",users->balance);
      SetDlgItemText(IDC_BALANCE,tmp);
      //--- free data
      ExtManager->MemFree(users);
      users      =NULL;
      users_total=0;
      //--- log out
      LogMessage(RET_OK,"Get client data");
     }
   else
     {
      LogMessage(RET_ERROR,"Get client data failed"); // request failed
     }
   AfxGetApp()->EndWaitCursor();
  }
//+------------------------------------------------------------------+
//|                                                                  |
//+------------------------------------------------------------------+
void CBalanceManagerDlg::OnExit()
  {
   this->DestroyWindow();
  }
//+------------------------------------------------------------------+
//|                                                                  |
//+------------------------------------------------------------------+
void CBalanceManagerDlg::OnDeposit()
  {
   TradeTransInfo  info={0};
   char            tmp[250];
//--- create transaction
   info.type   =TT_BR_BALANCE;
   info.cmd    =OP_BALANCE;
   info.orderby=GetDlgItemInt(m_client.GetDlgCtrlID(),NULL,FALSE);
   m_value.GetWindowText(tmp,32);
   info.price=atof(tmp);
   m_comment.GetWindowText(info.comment,sizeof(info.comment)-1);
   if(info.orderby<=0)
     {
      ::MessageBeep(-1);
      m_client.SetFocus();
      return;
     }
//--- do transaction
   int res=ExtManager->TradeTransaction(&info);
   if(res!=RET_OK) LogMessage(res,"Transaction failed");
   else
     {
      _snprintf(tmp,sizeof(tmp)-1,"Deposit %.02f for %d",info.price,info.orderby);
      LogMessage(res,tmp);
      OnRequest();
     }
  }
//+------------------------------------------------------------------+
//|                                                                  |
//+------------------------------------------------------------------+
void CBalanceManagerDlg::OnWithdrawal()
  {
   TradeTransInfo  info={0};
   char            tmp[250];
//--- create transaction
   info.type   =TT_BR_BALANCE;
   info.cmd    =OP_BALANCE;
   info.orderby=GetDlgItemInt(m_client.GetDlgCtrlID(),NULL,FALSE);
   m_value.GetWindowText(tmp,32);
   info.price=-atof(tmp);
   m_comment.GetWindowText(info.comment,sizeof(info.comment)-1);
   if(info.orderby<=0) { ::MessageBeep(-1); m_client.SetFocus(); return; }
//--- do transaction
   int res=ExtManager->TradeTransaction(&info);
   if(res!=RET_OK) LogMessage(res,"Transaction failed");
   else
     {
      _snprintf(tmp,sizeof(tmp)-1,"Withdrawal %.02f for %d",info.price,info.orderby);
      LogMessage(res,tmp);
      OnRequest();
     }
  }

//+------------------------------------------------------------------+
//| Create log message                                               |
//+------------------------------------------------------------------+
void CBalanceManagerDlg::LogMessage(int errorcode, char *msg)
  {
   tm              *tmm;
   time_t          ctm;
   char            tmp[250];
   char            fname[256];
   FILE            *fl;
//--- get current time
   if((ctm=time(NULL))==NULL)    return;
   if((tmm=localtime(&ctm))==NULL)  return;
//--- insert item to list
   _snprintf(tmp,sizeof(tmp)-1,"%02d:%02d:%02d",tmm->tm_hour,tmm->tm_min,tmm->tm_sec);
   m_log.InsertItem(m_itemnum, "");
   m_log.SetItemText(m_itemnum,0,tmp); //set date
   _snprintf(tmp,sizeof(tmp)-1,"%d",GetDlgItemInt(m_client.GetDlgCtrlID(),NULL,FALSE));
   m_log.SetItemText(m_itemnum,1,tmp); //set client
   _snprintf(tmp,sizeof(tmp)-1,"%s [%s]",msg,ExtManager->ErrorDescription(errorcode));
   m_log.SetItemText(m_itemnum,2,tmp); //set message
   m_log.EnsureVisible(m_itemnum,false);
   m_itemnum++;
//--- check log directory
   if(!CheckLogDir()) return;
//--- write message to file
   _snprintf(fname,sizeof(fname)-1,"%s\\log\\%04d%02d%02d.log",m_path,tmm->tm_year+1900,tmm->tm_mon+1,tmm->tm_mday);
   fl=fopen(fname,"at");
   if(fl)
     {
      _snprintf(tmp,sizeof(tmp)-1,"%02d:%02d:%02d\t%d\t%s [%s]\n",tmm->tm_hour,tmm->tm_min,tmm->tm_sec,
                                                         GetDlgItemInt(m_client.GetDlgCtrlID(),NULL,FALSE),
                                                         msg,ExtManager->ErrorDescription(errorcode));
      fputs(tmp,fl);
      fclose(fl);
     }
  }
//+------------------------------------------------------------------+
//| Check log directory                                              |
//+------------------------------------------------------------------+
bool CBalanceManagerDlg::CheckLogDir()
  {
   tm              *tmm;
   time_t          ctm;
   char            fname[256];
   HANDLE          fh;
   WIN32_FIND_DATA fd={0};
//--- get current time
   if((ctm=time(NULL))==NULL)       return(false);
   if((tmm=localtime(&ctm))==NULL)  return(false);
//--- check log directory
   _snprintf(fname,sizeof(fname)-1,"%s\\log",m_path);
   if((fh=FindFirstFile(fname,&fd))==INVALID_HANDLE_VALUE)
     {
      //--- create 'log' directory
      CreateDirectory(fname,NULL);
     }
   else
     {
      //--- this is a file?
      if((fd.dwFileAttributes&FILE_ATTRIBUTE_DIRECTORY)==FALSE) return(false);
     }
//---
   return(true);
  }

//+------------------------------------------------------------------+
