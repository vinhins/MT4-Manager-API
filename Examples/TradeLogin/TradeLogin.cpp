//+------------------------------------------------------------------+
//|                                         MetaTrader 4 Manager API |
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
         printf("Failed to create MetaTrader 4 Manager API interface\n");
         return;
        }
     }

   ~CManager()
     {
      if(m_manager!=NULL)
        {
         if(m_manager->IsConnected())
            m_manager->Disconnect();
         m_manager->Release();
         m_manager=NULL;
        }
      m_factory.WinsockCleanup();
     }

   bool IsValid()
     {
      return(m_manager!=NULL);
     }

   CManagerInterface* operator->()
     {
      return(m_manager);
     }
  };
//+------------------------------------------------------------------+
//|                                                                  |
//+------------------------------------------------------------------+
int main(int argc, char* argv[])
  {
   int          res=RET_ERROR;
   TradeRecord *trades=NULL;
//---
   printf("MetaTrader 4 Manager API: TradeLogin\n");
   printf("Transfer orders from one login to another\n");
   printf("Copyright 2001-2014, MetaQuotes Software Corp.\n\n");
//--- check parameters
   if(argc<6)
     {
      printf("usage: TradeLogin.exe server login password account_from account_to\n");
      return(0);
     }
//--- check manager interface
   CManager manager;
   if(!manager.IsValid()) return(-1);
//--- connect
   if((res=manager->Connect(argv[1]))!=RET_OK || (res=manager->Login(atoi(argv[2]),argv[3]))!=RET_OK)
     {
      printf("Connect to %s as '%s' failed (%s)\n",argv[1],argv[2],manager->ErrorDescription(res));
      return(-1);
     }
   printf("Connect to %s as '%s' successfull\n",argv[1],argv[2]);
//---
   int  login[2];
   int  total=2;

   login[0]=atoi(argv[4]);
   login[1]=atoi(argv[5]);
   printf("Transfering orders from '%d' to '%d'\n",login[0],login[1]);
//--- check users groups
   UserRecord *users=manager->UserRecordsRequest(login,&total);
   if(users==NULL || total!=2)
     {
      if(users)
         manager->MemFree(users);

      printf("Unknown users '%d' and '%d'\n",login[0],login[1]);
      return(-1);
     }
   if(strcmp(users[0].group,users[1].group)!=0)
     {
      if(users)
         manager->MemFree(users);

      printf("Users '%d' and '%d' should belong to the same group\n",login[0],login[1]);
      return(-1);
     }
   manager->MemFree(users);
   users=NULL;
//--- get open and closed trades for the first login
   trades=manager->AdmTradesRequest(argv[1],FALSE,&total);
   if(trades==NULL || total<1)
     {
      if(trades!=NULL) manager->MemFree(trades);
      printf("'%d' has no orders\n",login[0]);
      return(0);
     }
   printf("'%d' has %d orders\n",login[0],total);
//--- transfer orders to the second login
   for(int i=0; i<total; i++)
     {
      trades[i].login=login[1];
      if((res=manager->AdmTradeRecordModify(&trades[i]))!=RET_OK)
        {
         printf("#%d transfer failed: %d (%s)\n",trades[i].order,res,manager->ErrorDescription(res));
         return(-1);
        }
      printf("#%d transfered\n",trades[i].order);
     }
   printf("%d orders transfered from '%d' to '%d'\n",total,login[0],login[1]);
   manager->MemFree(trades);
   trades=NULL;
//--- fix balances for both logins
   if((res=manager->AdmBalanceFix(login,2))!=RET_OK)
     {
      printf("Balances fix failed: %d (%s)\n",res,manager->ErrorDescription(res));
      return(-1);
     }
   printf("Balances fixed\n");
//---
   return(0);
  }
//+------------------------------------------------------------------+
