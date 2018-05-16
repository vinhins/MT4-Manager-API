//+------------------------------------------------------------------+
//|                                  MetaTrader 4 Manager API Sample |
//|                   Copyright 2001-2014, MetaQuotes Software Corp. |
//|                                        http://www.metaquotes.net |
//+------------------------------------------------------------------+
#include "stdafx.h"
#include "ManagerAPISample.h"
#include "PageDealer.h"

//+------------------------------------------------------------------+
//|                                                                  |
//+------------------------------------------------------------------+
static const char  *ExtOperationsUpr[9]={ "BUY","SELL","BUY LIMIT","SELL LIMIT","BUY STOP","SELL STOP","BALANCE","CREDIT","ERROR" };
static const double ExtDecimalArray[9] ={ 1.0, 10.0, 100.0, 1000.0, 10000.0, 100000.0, 1000000.0, 10000000.0, 100000000.0 };
//+------------------------------------------------------------------+
//| По номеру даем описание команды                                  |
//+------------------------------------------------------------------+
LPCSTR GetCmdUpr(const int cmd)
  {
//--- проверки
   if(cmd<0 || cmd>7) return(ExtOperationsUpr[8]);
//---
   return(ExtOperationsUpr[cmd]);
  }
//+------------------------------------------------------------------+
//|                                                                  |
//+------------------------------------------------------------------+
double __fastcall NormalizeDouble(const double val,int digits)
  {
   if(digits<0) digits=0;
   if(digits>8) digits=8;
//---
   const double p=ExtDecimalArray[digits];
   return((val>=0.0) ? (double(__int64(val*p+0.5000001))/p) : (double(__int64(val*p-0.5000001))/p));
  }
//+------------------------------------------------------------------+
//|                                                                  |
//+------------------------------------------------------------------+
IMPLEMENT_DYNCREATE(CPageDealer, CPropertyPageEx)
//+------------------------------------------------------------------+
//|                                                                  |
//+------------------------------------------------------------------+
CPageDealer::CPageDealer() : CPropertyPageEx(CPageDealer::IDD)
  {
   //{{AFX_DATA_INIT(CPageDealer)
   //}}AFX_DATA_INIT
   m_psp.dwFlags&=~PSP_HASHELP;
   memset(&m_req,0,sizeof(m_req));
  }
//+------------------------------------------------------------------+
//|                                                                  |
//+------------------------------------------------------------------+
CPageDealer::~CPageDealer()
  {
  }
//+------------------------------------------------------------------+
//|                                                                  |
//+------------------------------------------------------------------+
void CPageDealer::DoDataExchange(CDataExchange* pDX)
  {
   CPropertyPageEx::DoDataExchange(pDX);
   //{{AFX_DATA_MAP(CPageDealer)
   DDX_Control(pDX, IDC_RETURN, m_Return);
   DDX_Control(pDX, IDC_REJECT, m_Reject);
   DDX_Control(pDX, IDC_CONFIRM, m_Confirm);
   DDX_Control(pDX, IDC_SERVER, m_Server);
   DDX_Control(pDX, IDC_REQUEST, m_Request);
   DDX_Control(pDX, IDC_PASSWORD, m_Password);
   DDX_Control(pDX, IDC_LOGIN, m_Login);
   //}}AFX_DATA_MAP
  }
//+------------------------------------------------------------------+
//|                                                                  |
//+------------------------------------------------------------------+
BEGIN_MESSAGE_MAP(CPageDealer, CPropertyPageEx)
   //{{AFX_MSG_MAP(CPageDealer)
   ON_WM_DESTROY()
   ON_BN_CLICKED(IDC_CONNECT, OnConnect)
   ON_BN_CLICKED(IDC_DISCONNECT, OnDisconnect)
   ON_BN_CLICKED(IDC_CONFIRM, OnConfirm)
   ON_BN_CLICKED(IDC_REJECT, OnReject)
   ON_BN_CLICKED(IDC_RETURN, OnReturn)
   //}}AFX_MSG_MAP
   ON_REGISTERED_MESSAGE(ExtDealingMsg, OnDealingMsg)
END_MESSAGE_MAP()
//+------------------------------------------------------------------+
//|                                                                  |
//+------------------------------------------------------------------+
BOOL CPageDealer::OnInitDialog()
  {
   CPropertyPageEx::OnInitDialog();
//---
   m_Server.SetWindowText("localhost:443");
   SetDlgItemInt(m_Login.GetDlgCtrlID(),10,FALSE);
   m_Password.SetWindowText("Manager10");
//---
   EnableAnswer(FALSE);
//---
   return(TRUE);
  }
//+------------------------------------------------------------------+
//|                                                                  |
//+------------------------------------------------------------------+
void CPageDealer::OnDestroy()
  {
   if(ExtDealer->IsConnected()) ExtDealer->Disconnect();
   CPropertyPage::OnDestroy();
  }
//+------------------------------------------------------------------+
//|                                                                  |
//+------------------------------------------------------------------+
void CPageDealer::OnConnect()
  {
   char server[128]="";
   int  login=0,res=RET_ERROR;
   char pass[16]="";
//---
   if(ExtManagerPump->IsConnected()==FALSE)
     {
      MessageBox("PumpingSwitch first.","DealerSwitch");
      return;
     }
//---
   m_Server.GetWindowText(server,sizeof(server)-1);
   login=GetDlgItemInt(m_Login.GetDlgCtrlID(),NULL,FALSE);
   m_Password.GetWindowText(pass,sizeof(pass)-1);
//--- connect dealer
   res=ExtDealer->Connect(server);
   if(res!=RET_OK)
     {
      MessageBox(ExtDealer->ErrorDescription(res),"Dealer Connect");
      return;
     }
   res=ExtDealer->Login(login,pass);
   if(res!=RET_OK)
     {
      MessageBox(ExtDealer->ErrorDescription(res),"Dealer Login");
      return;
     }
   res=ExtDealer->DealerSwitch(NULL,GetSafeHwnd(),ExtDealingMsg);
//---
   MessageBox(ExtDealer->ErrorDescription(res),"DealingSwitch");
  }
//+------------------------------------------------------------------+
//|                                                                  |
//+------------------------------------------------------------------+
void CPageDealer::OnDisconnect()
  {
   m_Request.SetWindowText("");
   EnableAnswer(FALSE);
   int res=ExtDealer->Disconnect();
   MessageBox(ExtDealer->ErrorDescription(res),"Disconnect");
  }
//+------------------------------------------------------------------+
//|                                                                  |
//+------------------------------------------------------------------+
void CPageDealer::OnConfirm()
  {
   int res=ExtDealer->DealerSend(&m_req,FALSE,FALSE);
   m_Request.SetWindowText("");
   EnableAnswer(FALSE);
   if(res!=RET_OK) MessageBox(ExtDealer->ErrorDescription(res),"DealerSend");
  }
//+------------------------------------------------------------------+
//|                                                                  |
//+------------------------------------------------------------------+
void CPageDealer::OnReject()
  {
   int res=ExtDealer->DealerReject(m_req.id);
   m_Request.SetWindowText("");
   EnableAnswer(FALSE);
   if(res!=RET_OK) MessageBox(ExtDealer->ErrorDescription(res),"DealerReject");
  }
//+------------------------------------------------------------------+
//|                                                                  |
//+------------------------------------------------------------------+
void CPageDealer::OnReturn()
  {
   int res=ExtDealer->DealerReset(m_req.id);
   m_Request.SetWindowText("");
   EnableAnswer(FALSE);
   if(res!=RET_OK) MessageBox(ExtDealer->ErrorDescription(res),"DealerReset");
  }
//+------------------------------------------------------------------+
//|                                                                  |
//+------------------------------------------------------------------+
LRESULT CPageDealer::OnDealingMsg(WPARAM wParam,LPARAM)
  {
   int res=RET_ERROR;
//---
   switch(wParam)
     {
      case DEAL_START_DEALING:
      case DEAL_STOP_DEALING:
         break;
      case DEAL_REQUEST_NEW:
         res=ExtDealer->DealerRequestGet(&m_req);
         if(res!=RET_OK)
           {
            MessageBox(ExtDealer->ErrorDescription(res),"DealerRequestGet");
            break;
           }
         ShowRequest();
         break;
      default: break;
     }
//---
   return(0);
  }
//+------------------------------------------------------------------+
//|                                                                  |
//+------------------------------------------------------------------+
void CPageDealer::EnableAnswer(BOOL enable)
  {
   m_Confirm.EnableWindow(enable);
   m_Reject.EnableWindow(enable);
   m_Return.EnableWindow(enable);
  }
//+------------------------------------------------------------------+
//|                                                                  |
//+------------------------------------------------------------------+
void CPageDealer::ShowRequest()
  {
   SymbolInfo  si ={""};
   ConGroup    grp={""};
   CString     str,sPrice,sFormat;
//--- check pumping connect
   if(ExtManagerPump->IsConnected()==FALSE)
     {
      OnDisconnect();
      return;
     }
//--- get current symbol prices
   if(ExtManagerPump->SymbolInfoGet(m_req.trade.symbol,&si)!=RET_OK || si.bid==0.0 || si.ask==0.0)
     {
      //--- symbol hidden
      //--- show symbol, reset request to the queue
      ExtManagerPump->SymbolAdd(m_req.trade.symbol);
      PostMessage(WM_COMMAND,IDC_RETURN);
      return;
     }
   if(si.bid==0.0 || si.ask==0.0)
     {
      //--- there are no quotes,
      //--- return request to the queue
      PostMessage(WM_COMMAND,IDC_RETURN);
      return;
     }
//--- price format string
   sFormat.Format("%%.%dlf",si.digits);
//--- current prices
   m_req.prices[0]=si.bid; m_req.prices[1]=si.ask;
//--- spread difference for the group
   if(ExtManagerPump->GroupRecordGet(m_req.group,&grp)==RET_OK)
     {
      //--- разводим спред для этой группы
      double spread_diff=grp.secgroups[si.type].spread_diff;
      if(spread_diff!=0)
        {
         //--- подготовим данные
         double spread=si.ask-si.bid;
         //--- разведём спред
         m_req.prices[0]=NormalizeDouble(m_req.prices[0]-si.point*spread_diff/2.0,si.digits);
         m_req.prices[1]=NormalizeDouble(m_req.prices[0]+spread+si.point*spread_diff,si.digits);
        }
     }
//--- show request
   switch(m_req.trade.type)
     {
      case TT_PRICES_GET:
         str.Format("'%d' %s: QUOTES for %.2lf %s: ",m_req.login,m_req.group,
                    m_req.trade.volume/100.0,m_req.trade.symbol);
         sPrice.Format(sFormat,m_req.prices[0]);
         str+=sPrice; str+= " / ";
         sPrice.Format(sFormat,m_req.prices[1]);
         str+=sPrice;
         break;
      case TT_ORDER_IE_OPEN:
      case TT_ORDER_REQ_OPEN:
      case TT_ORDER_MK_OPEN:
         if(m_req.trade.cmd==OP_BUY)
           {
            if(m_req.trade.type==TT_ORDER_MK_OPEN) m_req.trade.price=m_req.prices[1];
           }
         else
           {
            if(m_req.trade.type==TT_ORDER_MK_OPEN) m_req.trade.price=m_req.prices[0];
           }
         sPrice.Format(sFormat,m_req.trade.price);
         str.Format("'%d' %s: CONFIRM OPEN %s %.2lf %s at %s ",m_req.login,m_req.group,
                    GetCmdUpr(m_req.trade.cmd),m_req.trade.volume/100.0,m_req.trade.symbol,sPrice);
         break;
      case TT_ORDER_IE_CLOSE:
      case TT_ORDER_REQ_CLOSE:
      case TT_ORDER_MK_CLOSE:
         if(m_req.trade.cmd==OP_BUY)
           {
            if(m_req.trade.type==TT_ORDER_MK_CLOSE) m_req.trade.price=m_req.prices[0];
           }
         else
           {
            if(m_req.trade.type==TT_ORDER_MK_CLOSE) m_req.trade.price=m_req.prices[1];
           }
         sPrice.Format(sFormat,m_req.trade.price);
         str.Format("'%d' %s: CONFIRM CLOSE #%d %s %.2lf %s at %s ",m_req.login,m_req.group,
                   m_req.trade.order,GetCmdUpr(m_req.trade.cmd),m_req.trade.volume/100.0,
                   m_req.trade.symbol,sPrice);
         break;
      case TT_ORDER_DELETE:
         sPrice.Format(sFormat,m_req.trade.price);
         str.Format("'%d'%s: DELETE #%d %s %.2lf %s at %s ",m_req.login,m_req.group,
                    m_req.trade.order,GetCmdUpr(m_req.trade.cmd),m_req.trade.volume/100.0,
                    m_req.trade.symbol,sPrice);
         break;
      case TT_ORDER_MODIFY:
         sPrice.Format(sFormat,m_req.trade.price);
         str.Format("'%d' %s: MODIFY #%d %s %.2lf %s at %s ",m_req.login,m_req.group,
                    m_req.trade.order,GetCmdUpr(m_req.trade.cmd),m_req.trade.volume/100.0,
                    m_req.trade.symbol,sPrice);
         str+=" sl: "; sPrice.Format(sFormat,m_req.trade.sl); str+=sPrice;
         str+=" tp: "; sPrice.Format(sFormat,m_req.trade.tp); str+=sPrice;
         break;
      case TT_ORDER_CLOSE_BY:
         sPrice.Format(sFormat,m_req.trade.price);
         str.Format("'%d' %s: CLOSE #%d BY #%d at %s ",m_req.login,m_req.group,
                    m_req.trade.order,m_req.trade.orderby,sPrice);
         break;
      case TT_ORDER_CLOSE_ALL:
         str.Format("'%d' %s: CLOSE ALL ORDERS for %s ",m_req.login,m_req.group,m_req.trade.symbol);
         break;
      case TT_ORDER_PENDING_OPEN:
         sPrice.Format(sFormat,m_req.trade.price);
         str.Format("'%d' %s: %s %.2lf %s at %s ",m_req.login,m_req.group,
                    GetCmdUpr(m_req.trade.cmd),m_req.trade.volume/100.0,m_req.trade.symbol,sPrice);
         break;
      default:
         str.Format("'%d' %s: UNKNOWN ",m_req.login,m_req.group);
         break;
     }
   m_Request.SetWindowText(str);
//---
   EnableAnswer(TRUE);
   ::MessageBeep(-1);
  }
//+------------------------------------------------------------------+
//|                                                                  |
//+------------------------------------------------------------------+
