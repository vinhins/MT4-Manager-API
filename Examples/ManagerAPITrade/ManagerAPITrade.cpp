//+------------------------------------------------------------------+
//|                                                       MetaTrader |
//|                   Copyright 2001-2014, MetaQuotes Software Corp. |
//|                                        http://www.metaquotes.net |
//+------------------------------------------------------------------+
#include "stdafx.h"
#include "..\MT4ManagerAPI.h"
//+------------------------------------------------------------------+
//|                                                                  |
//+------------------------------------------------------------------+
class CManager
  {
private:
   CManagerFactory   m_factory;
   CManagerInterface *m_manager;
public:
   CManager() : m_factory("..\\..\\mtmanapi.dll"),m_manager(NULL)
     {
      m_factory.WinsockStartup();
      if(m_factory.IsValid()==FALSE || (m_manager=m_factory.Create(ManAPIVersion))==NULL)
        {
         printf("Failed to create manager interface\n");
         return;
        }
     }
   ~CManager()
     {
      if(m_manager!=NULL) { m_manager->Release(); m_manager=NULL; }
      m_factory.WinsockCleanup();
     }
   bool              IsValid()    { return(m_manager!=NULL); }
   CManagerInterface* operator->() { return(m_manager);       }
  };
//+------------------------------------------------------------------+
//|                                                                  |
//+------------------------------------------------------------------+
int main(int argc, char* argv[])
  {
   CManager       manager;
   TradeTransInfo info  ={0};
   TradeRecord   *trades=NULL;
   int            total =0,res=RET_ERROR,i;
   MarginLevel    level ={0};
//--- check creation
   if(manager.IsValid()==FALSE) return(-1);
//--- connect
   if((res=manager->Connect("localhost:440"))!=RET_OK || (res=manager->Login(11,"Manager11"))!=RET_OK)
     {
      printf("Connect failed: %d (%s)\n",res,manager->ErrorDescription(res));
      return(-1);
     }
   printf("Connected as '11'\n");
//--- open
   info.type   =TT_BR_ORDER_OPEN;      // trade transaction type
   info.cmd    =OP_BUY;                // trade command
   info.orderby=17190;                 // order, order by, login
   strcpy(info.symbol,"EURUSD");       // trade symbol
   info.volume =100;                   // trade volume
   info.price  =1.2900;                // trade price
   info.sl     =1.2800;                // stoploss
   info.tp     =1.3000;                // takeprofit
   if((res=manager->TradeTransaction(&info))!=RET_OK)
     {
      printf("Order open failed: %d (%s)\n",res,manager->ErrorDescription(res));
      return(-1);
     }
   printf("Order has been opened\n");
//--- request trades
   trades=manager->TradesRequest(&total);
   if(trades==NULL || total<1)
     {
      printf("Orders request failed\n");
      return(-1);
     }
//--- find last order
   for(i=total-1; i>=0; --i)
      if(trades[i].login==17190)
        {
         info.order=trades[i].order;
         break;
        }
   manager->MemFree(trades);
   trades=NULL;
//--- close
   info.type=TT_BR_ORDER_CLOSE;
   if((res=manager->TradeTransaction(&info))!=RET_OK)
     {
      printf("Order close failed: %d (%s)\n",res,manager->ErrorDescription(res));
      return(-1);
     }
   printf("Order has been closed\n");
//--- external command
   char  data_in[256]="";
   LPSTR data_out=NULL;
   int   size_out=0;
   if((res=manager->ExternalCommand(data_in,sizeof(data_in),&data_out,&size_out))!=RET_OK)
     {
      printf("External command failed: %d (%s)\n",res,manager->ErrorDescription(res));
      return(-1);
     }
   printf("External command succeeded (%d bytes)\n",size_out);
   if(data_out!=NULL)
     {
      manager->MemFree(data_out);
      data_out=NULL;
     }
//---
   if((res=manager->MarginLevelRequest(17190,&level))!=RET_OK)
     {
      printf("Margin level request failed: %d (%s)\n",res,manager->ErrorDescription(res));
      return(-1);
     }
   printf("Margin level for '%d': %.2lf%c\n",level.login,level.margin_level,level.margin_type==MARGIN_TYPE_PERCENT ? '%':'$');
//---
   if((res=manager->HistoryCorrect("USDJPY",&total))>RET_OK_NONE)
     {
      printf("USDJPY base correction failed: %d (%s)\n",res,manager->ErrorDescription(res));
      return(-1);
     }
   if(res==RET_OK_NONE) printf("USDJPY bases are correct.\n");
   else                 printf("USDJPY bases has been corrected: %d bars updated\n",total);
//---
   return(0);
  }
//+------------------------------------------------------------------+
//|                                                                  |
//+------------------------------------------------------------------+
