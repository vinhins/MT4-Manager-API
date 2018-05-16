//+------------------------------------------------------------------+
//|                                      MetaTrader Manager API Test |
//|                   Copyright 2001-2014, MetaQuotes Software Corp. |
//|                                        http://www.metaquotes.net |
//+------------------------------------------------------------------+
#pragma once
//+------------------------------------------------------------------+
//| Функции                                                          |
//+------------------------------------------------------------------+
void                 ToSym(char *pricebuf,const double price,int digits);
double __fastcall    NormalizeDouble(const double price,int digits);
LPCSTR               GetCmd(const int cmd);
void                 FormatDateTime(const tm *ptm,CString& str,BOOL bUseTime=TRUE,BOOL bUseSec=FALSE);
//+------------------------------------------------------------------+
//|                                                                  |
//+------------------------------------------------------------------+
inline void          FormatDateTime(__time32_t ctm,CString& str,BOOL bUseTime=TRUE,BOOL bUseSec=FALSE)
                     { FormatDateTime(_gmtime32(&ctm),str,bUseTime,bUseSec); }
void                 FormatDouble(int val,int digits,CString &str);
//+------------------------------------------------------------------+
