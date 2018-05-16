//+------------------------------------------------------------------+
//|                                      MetaTrader Manager API Test |
//|                   Copyright 2001-2014, MetaQuotes Software Corp. |
//|                                        http://www.metaquotes.net |
//+------------------------------------------------------------------+
#include "..\stdafx.h"
#include "common.h"
//+------------------------------------------------------------------+
//| Глобальные переменные                                            |
//+------------------------------------------------------------------+
volatile UINT  ExtInternalMsg     =0;
volatile UINT  ExtInternalHandle  =0;
//+------------------------------------------------------------------+
//| Функции                                                          |
//+------------------------------------------------------------------+
//|                                                                  |
//+------------------------------------------------------------------+
static const char  *ExtOperations[9]  ={ "buy","sell","buy limit","sell limit",
   "buy stop","sell stop","balance","credit","error" };
static const double ExtDecimalArray[9]={ 1.0, 10.0, 100.0, 1000.0, 10000.0, 100000.0, 1000000.0, 10000000.0, 100000000.0 };
//+------------------------------------------------------------------+
//|                                                                  |
//+------------------------------------------------------------------+
void ToSym(char *pricebuf,const double price,int digits)
  {
   char *cp;
//---
   if(pricebuf==NULL) return;
//---
   if(digits>0) digits++;
   if(digits>8) digits=8;
   sprintf(pricebuf,"%.8lf",price);
   if((cp=strstr(pricebuf,"."))!=NULL) *(cp+digits)=0;
//---
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
//| По номеру даем описание команды                                  |
//+------------------------------------------------------------------+
LPCSTR GetCmd(const int cmd)
  {
//--- проверки
   if(cmd<0 || cmd>7) return(ExtOperations[8]);
//---
   return(ExtOperations[cmd]);
  }
//+------------------------------------------------------------------+
//|                                                                  |
//+------------------------------------------------------------------+
void FormatDateTime(const tm *ptm,CString& str,BOOL bUseTime,BOOL bUseSec)
  {
   if(ptm==NULL) return;
//---
   if(bUseTime)
     {
      if(bUseSec) str.Format("%04d.%02d.%02d %02d:%02d:%02d",ptm->tm_year+1900,ptm->tm_mon+1,ptm->tm_mday,ptm->tm_hour,ptm->tm_min,ptm->tm_sec);
      else        str.Format("%04d.%02d.%02d %02d:%02d",ptm->tm_year+1900,ptm->tm_mon+1,ptm->tm_mday,ptm->tm_hour,ptm->tm_min);
     }
   else str.Format("%04d.%02d.%02d",ptm->tm_year+1900,ptm->tm_mon+1,ptm->tm_mday);
//---
  }
//+------------------------------------------------------------------+
//|                                                                  |
//+------------------------------------------------------------------+
void FormatDouble(int val,int digits,CString& str)
  {
   CString sFormat;
   int      divider=1;
   for(int i=0; i<digits; i++) divider*=10;
   sFormat.Format(_T("%%.0%dlf"), digits);
   str.Format(sFormat, double(val)/divider);
  }
//+------------------------------------------------------------------+
//|                                                                  |
//+------------------------------------------------------------------+
