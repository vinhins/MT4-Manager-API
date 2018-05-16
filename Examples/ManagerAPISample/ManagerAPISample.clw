; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CPageExposure
LastTemplate=CPropertyPage
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "ManagerAPISample.h"

ClassCount=28
Class1=CManagerAPISampleApp
Class2=CManagerAPISampleDlg
Class3=CPageRequests

ResourceCount=30
Resource1=IDD_MANAGERAPISAMPLE_DIALOG (English (U.S.))
Resource2=IDR_MAINFRAME
Resource3=IDD_ABOUTBOX (English (U.S.))
Class4=CPageMain
Class5=CManagerSheet
Resource4=IDD_NEWS_SEND (Neutral)
Class6=CPageSymbols
Resource5=IDD_MANAGER_ONLINE (Neutral)
Class7=CPageDealer
Resource6=IDD_USER_BALANCE (Neutral)
Class8=CPageNews
Resource7=IDD_MANAGER_NEWS (Neutral)
Class9=CPageUsers
Resource8=IDD_MANAGER_LOGS (Neutral)
Class10=CSymbolChangeDlg
Resource9=IDD_MAIL_SEND (Neutral)
Class11=CUserUpdateDlg
Resource10=IDD_MANAGER_ORDERS (Neutral)
Class12=CUserNewDlg
Resource11=IDD_REQUEST (Neutral)
Class13=CUserGroupDlg
Resource12=IDD_MANAGER_MAIL (Neutral)
Class14=CPageOnline
Resource13=IDD_SYMBOL_CHANGE (Neutral)
Class15=CUserBalanceDlg
Resource14=IDD_USER_NEW (Neutral)
Class16=CPageOrders
Resource15=IDD_MANAGER_REPORTS (Neutral)
Class17=CUserHistoryDlg
Resource16=IDD_MANAGER_MAIN (Neutral)
Resource17=IDD_USER_GROUP (Neutral)
Class18=CPageReports
Class19=CPageDaily
Resource18=IDD_USER_HISTORY (Neutral)
Class20=CPageLogs
Resource19=IDD_MANAGER_MARGIN (Neutral)
Class21=CPageMW
Resource20=IDD_MANAGER_SUMMARY (Neutral)
Class22=CPageJournal
Resource21=IDD_MANAGER_JOURNAL (Neutral)
Class23=CPageMargin
Resource22=IDD_MANAGER_USERS (Neutral)
Resource23=IDD_MANAGER_REQUESTS (Neutral)
Class24=CPageMailbox
Resource24=IDD_USER_UPDATE (Neutral)
Resource25=IDD_MANAGER_DEALER (Neutral)
Resource26=IDD_MANAGER_DAILY (Neutral)
Class25=CNewsSendDlg
Resource27=IDD_MANAGER_MW (Neutral)
Class26=CPagePlugins
Resource28=IDD_MANAGER_PLUGINS (Neutral)
Class27=CPageSummary
Resource29=IDD_MANAGER_SYMBOLS (Neutral)
Class28=CPageExposure
Resource30=IDD_MANAGER_EXPOSURE (Neutral)

[CLS:CManagerAPISampleApp]
Type=0
HeaderFile=ManagerAPISample.h
ImplementationFile=ManagerAPISample.cpp
Filter=N
BaseClass=CWinApp
VirtualFilter=AC
LastObject=CManagerAPISampleApp

[CLS:CManagerAPISampleDlg]
Type=0
HeaderFile=ManagerAPISampleDlg.h
ImplementationFile=ManagerAPISampleDlg.cpp
Filter=D
LastObject=CManagerAPISampleDlg

[DLG:IDD_MANAGERAPISAMPLE_DIALOG (English (U.S.))]
Type=1
Class=CManagerAPISampleDlg
ControlCount=3
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_STATIC,static,1342308352

[DLG:IDD_ABOUTBOX (English (U.S.))]
Type=1
Class=?
ControlCount=4
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308480
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889

[CLS:CPageMain]
Type=0
HeaderFile=PageMain.h
ImplementationFile=PageMain.cpp
BaseClass=CPropertyPageEx
Filter=D
LastObject=IDC_PUMPING
VirtualFilter=idWC

[CLS:CManagerSheet]
Type=0
HeaderFile=ManagerSheet.h
ImplementationFile=ManagerSheet.cpp
BaseClass=CPropertySheetEx
Filter=W
VirtualFilter=hWC
LastObject=CManagerSheet

[CLS:CPageSymbols]
Type=0
HeaderFile=PageSymbols.h
ImplementationFile=PageSymbols.cpp
BaseClass=CPropertyPageEx
Filter=D
LastObject=CPageSymbols
VirtualFilter=idWC

[CLS:CPageUsers]
Type=0
HeaderFile=PageUsers.h
ImplementationFile=PageUsers.cpp
BaseClass=CPropertyPageEx
Filter=D
VirtualFilter=idWC
LastObject=IDC_MARGIN

[CLS:CSymbolChangeDlg]
Type=0
HeaderFile=dialogs\symbolchangedlg.h
ImplementationFile=dialogs\symbolchangedlg.cpp
BaseClass=CDialog
Filter=D
LastObject=CSymbolChangeDlg
VirtualFilter=dWC

[CLS:CUserUpdateDlg]
Type=0
HeaderFile=dialogs\userupdatedlg.h
ImplementationFile=dialogs\userupdatedlg.cpp
BaseClass=CDialog
Filter=D
LastObject=CUserUpdateDlg
VirtualFilter=dWC

[CLS:CUserNewDlg]
Type=0
HeaderFile=dialogs\usernewdlg.h
ImplementationFile=dialogs\usernewdlg.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC
LastObject=IDOK

[CLS:CUserGroupDlg]
Type=0
HeaderFile=dialogs\usergroupdlg.h
ImplementationFile=dialogs\usergroupdlg.cpp
BaseClass=CDialog
Filter=D
LastObject=IDC_SETLEVERAGE
VirtualFilter=dWC

[CLS:CPageOnline]
Type=0
HeaderFile=PageOnline.h
ImplementationFile=PageOnline.cpp
BaseClass=CPropertyPageEx
Filter=D
LastObject=IDC_ONLINE_GET
VirtualFilter=idWC

[CLS:CUserBalanceDlg]
Type=0
HeaderFile=dialogs\userbalancedlg.h
ImplementationFile=dialogs\userbalancedlg.cpp
BaseClass=CDialog
Filter=D
LastObject=CUserBalanceDlg
VirtualFilter=dWC

[CLS:CPageOrders]
Type=0
HeaderFile=PageOrders.h
ImplementationFile=PageOrders.cpp
BaseClass=CPropertyPageEx
Filter=D
VirtualFilter=idWC
LastObject=IDC_ORDERS_GET

[CLS:CUserHistoryDlg]
Type=0
HeaderFile=dialogs\userhistorydlg.h
ImplementationFile=dialogs\userhistorydlg.cpp
BaseClass=CDialog
Filter=D
LastObject=CUserHistoryDlg
VirtualFilter=dWC

[CLS:CPageReports]
Type=0
HeaderFile=PageReports.h
ImplementationFile=PageReports.cpp
BaseClass=CPropertyPage
Filter=D
VirtualFilter=idWC
LastObject=CPageReports

[CLS:CPageDaily]
Type=0
HeaderFile=PageDaily.h
ImplementationFile=PageDaily.cpp
BaseClass=CPropertyPage
Filter=D
LastObject=IDC_DAILY
VirtualFilter=idWC

[CLS:CPageLogs]
Type=0
HeaderFile=PageLogs.h
ImplementationFile=PageLogs.cpp
BaseClass=CPropertyPageEx
Filter=D
VirtualFilter=idWC
LastObject=CPageLogs

[CLS:CPageMW]
Type=0
HeaderFile=PageMW.h
ImplementationFile=PageMW.cpp
BaseClass=CPropertyPageEx
Filter=D
LastObject=CPageMW
VirtualFilter=idWC

[CLS:CPageJournal]
Type=0
HeaderFile=PageJournal.h
ImplementationFile=PageJournal.cpp
BaseClass=CPropertyPageEx
Filter=D
VirtualFilter=idWC
LastObject=IDC_JOURNAL

[CLS:CPageMargin]
Type=0
HeaderFile=PageMargin.h
ImplementationFile=PageMargin.cpp
BaseClass=CPropertyPageEx
Filter=D
LastObject=IDC_USERS
VirtualFilter=idWC

[CLS:CPageRequests]
Type=0
HeaderFile=PageRequests.h
ImplementationFile=PageRequests.cpp
BaseClass=CPropertyPage
Filter=D
VirtualFilter=idWC
LastObject=CPageRequests

[CLS:CPageMailbox]
Type=0
HeaderFile=PageMailbox.h
ImplementationFile=PageMailbox.cpp
BaseClass=CPropertyPage
Filter=D
VirtualFilter=idWC
LastObject=CPageMailbox

[CLS:CPageNews]
Type=0
HeaderFile=PageNews.h
ImplementationFile=PageNews.cpp
BaseClass=CPropertyPage
Filter=D
VirtualFilter=idWC
LastObject=IDC_NEWS

[CLS:CPageDealer]
Type=0
HeaderFile=PageDealer.h
ImplementationFile=PageDealer.cpp
BaseClass=CPropertyPageEx
Filter=D
VirtualFilter=idWC
LastObject=IDC_CONFIRM

[CLS:CNewsSendDlg]
Type=0
HeaderFile=dialogs\newssenddlg.h
ImplementationFile=dialogs\newssenddlg.cpp
BaseClass=CDialog
Filter=D
LastObject=CNewsSendDlg

[DLG:IDD_MANAGER_DAILY (Neutral)]
Type=1
Class=CPageDaily
ControlCount=2
Control1=IDC_REQUEST,button,1342242816
Control2=IDC_DAILY,SysListView32,1350635529

[DLG:IDD_MAIL_SEND (Neutral)]
Type=1
Class=?
ControlCount=6
Control1=IDC_SEND,button,1342242816
Control2=IDC_STATIC,static,1342308354
Control3=IDC_RECEPIENT,edit,1350631552
Control4=IDC_STATIC,static,1342308354
Control5=IDC_SUBJECT,edit,1350631552
Control6=IDC_BODY,edit,1350631556

[DLG:IDD_MANAGER_MAIN (Neutral)]
Type=1
Class=CPageMain
ControlCount=15
Control1=IDC_STATIC,static,1342308354
Control2=IDC_SERVER,edit,1350631552
Control3=IDC_STATIC,static,1342308354
Control4=IDC_LOGIN,edit,1350639744
Control5=IDC_STATIC,static,1342308354
Control6=IDC_PASSWORD,edit,1350631584
Control7=IDC_CONNECT,button,1342242816
Control8=IDC_LOGINCMD,button,1342242816
Control9=IDC_DISCONNECT,button,1342242816
Control10=IDC_RIGHTS,button,1342242816
Control11=IDC_REQ_GROUPS,button,1342242816
Control12=IDC_SEND_MAIL,button,1342242816
Control13=IDC_SEND_NEWS,button,1342242816
Control14=IDC_GROUPS,SysListView32,1350631433
Control15=IDC_PUMPING,button,1342242816

[DLG:IDD_MANAGER_SYMBOLS (Neutral)]
Type=1
Class=CPageSymbols
ControlCount=3
Control1=IDC_REFRESH,button,1342242816
Control2=IDC_CHANGE,button,1342242816
Control3=IDC_SYMBOLS,SysListView32,1350631437

[DLG:IDD_NEWS_SEND (Neutral)]
Type=1
Class=CNewsSendDlg
ControlCount=7
Control1=IDC_SEND,button,1342242816
Control2=IDC_STATIC,static,1342308354
Control3=IDC_CATEGORY,edit,1350631552
Control4=IDC_STATIC,static,1342308354
Control5=IDC_SUBJECT,edit,1350631552
Control6=IDC_BODY,edit,1350631556
Control7=IDC_HIGH,button,1342243363

[DLG:IDD_MANAGER_USERS (Neutral)]
Type=1
Class=CPageUsers
ControlCount=8
Control1=IDC_REQUEST,button,1342242816
Control2=IDC_NEW,button,1342242816
Control3=IDC_UPDATE,button,1342242816
Control4=IDC_GROUPOP,button,1342242816
Control5=IDC_BALANCE,button,1342242816
Control6=IDC_USERS,SysListView32,1350635529
Control7=IDC_USERS_GET,button,1342242816
Control8=IDC_MARGIN,button,1342242816

[DLG:IDD_SYMBOL_CHANGE (Neutral)]
Type=1
Class=CSymbolChangeDlg
ControlCount=8
Control1=IDC_STATIC,static,1342308354
Control2=IDC_EXEMODE,combobox,1344339971
Control3=IDC_STATIC,static,1342308354
Control4=IDC_STOPS,edit,1350639744
Control5=IDC_STATIC,static,1342308354
Control6=IDC_SPREAD,edit,1350639744
Control7=IDOK,button,1342242816
Control8=IDCANCEL,button,1342242817

[DLG:IDD_USER_UPDATE (Neutral)]
Type=1
Class=CUserUpdateDlg
ControlCount=10
Control1=IDC_STATIC,static,1342308354
Control2=IDC_NAME,edit,1350631552
Control3=IDC_STATIC,static,1342308354
Control4=IDC_GROUP,combobox,1344339971
Control5=IDC_STATIC,static,1342308354
Control6=IDC_EMAIL,edit,1350631552
Control7=IDOK,button,1342242816
Control8=IDCANCEL,button,1342242817
Control9=IDC_STATIC,static,1342308354
Control10=IDC_LOGIN,edit,1350641792

[DLG:IDD_USER_NEW (Neutral)]
Type=1
Class=CUserNewDlg
ControlCount=12
Control1=IDC_STATIC,static,1342308354
Control2=IDC_NAME,edit,1350631552
Control3=IDC_STATIC,static,1342308354
Control4=IDC_GROUP,combobox,1344339971
Control5=IDC_STATIC,static,1342308354
Control6=IDC_EMAIL,edit,1350631552
Control7=IDOK,button,1342242816
Control8=IDCANCEL,button,1342242817
Control9=IDC_STATIC,static,1342308354
Control10=IDC_LOGIN,edit,1350631552
Control11=IDC_STATIC,static,1342308354
Control12=IDC_PASSWORD,edit,1350631552

[DLG:IDD_USER_GROUP (Neutral)]
Type=1
Class=CUserGroupDlg
ControlCount=11
Control1=IDC_GROUP,combobox,1344339971
Control2=IDC_SETGROUP,button,1342242816
Control3=IDC_LEVERAGE,combobox,1344339971
Control4=IDC_SETLEVERAGE,button,1342242816
Control5=IDC_ENABLE,button,1342242816
Control6=IDC_DISABLE,button,1342242816
Control7=IDC_DELETE,button,1342242816
Control8=IDC_STATIC,static,1342308352
Control9=IDC_LOGINS,SysListView32,1350647809
Control10=IDOK,button,1342242816
Control11=IDCANCEL,button,1342242817

[DLG:IDD_USER_BALANCE (Neutral)]
Type=1
Class=CUserBalanceDlg
ControlCount=11
Control1=IDC_STATIC,static,1342308354
Control2=IDC_LOGIN,edit,1350639744
Control3=IDC_STATIC,static,1342308354
Control4=IDC_VALUE,edit,1350631552
Control5=IDC_STATIC,static,1342308354
Control6=IDC_VALUE_DATE,SysDateTimePick32,1342242848
Control7=IDC_STATIC,static,1342308354
Control8=IDC_COMMENT,edit,1350631552
Control9=IDC_BALANCE,button,1342242816
Control10=IDC_CREDIT,button,1342242816
Control11=IDCANCEL,button,1342242817

[DLG:IDD_MANAGER_ORDERS (Neutral)]
Type=1
Class=CPageOrders
ControlCount=4
Control1=IDC_REQUEST,button,1342242816
Control2=IDC_ORDERS,SysListView32,1350635529
Control3=IDC_HISTORY,button,1342242816
Control4=IDC_ORDERS_GET,button,1342242816

[DLG:IDD_USER_HISTORY (Neutral)]
Type=1
Class=CUserHistoryDlg
ControlCount=8
Control1=IDC_STATIC,static,1342308354
Control2=IDC_LOGIN,edit,1350639744
Control3=IDC_STATIC,static,1342308354
Control4=IDC_FROM,SysDateTimePick32,1342242848
Control5=IDOK,button,1342242816
Control6=IDCANCEL,button,1342242817
Control7=IDC_STATIC,static,1342308354
Control8=IDC_TO,SysDateTimePick32,1342242848

[DLG:IDD_MANAGER_REPORTS (Neutral)]
Type=1
Class=CPageReports
ControlCount=2
Control1=IDC_REQUEST,button,1342242816
Control2=IDC_ORDERS,SysListView32,1350635529

[DLG:IDD_MANAGER_LOGS (Neutral)]
Type=1
Class=CPageLogs
ControlCount=1
Control1=IDC_LOGS,SysListView32,1350631437

[DLG:IDD_MANAGER_MW (Neutral)]
Type=1
Class=CPageMW
ControlCount=1
Control1=IDC_SYMBOLS,SysListView32,1350631437

[DLG:IDD_MANAGER_JOURNAL (Neutral)]
Type=1
Class=CPageJournal
ControlCount=5
Control1=IDC_JOURNAL,SysListView32,1350635533
Control2=IDC_MODE,combobox,1344339971
Control3=IDC_FROM,SysDateTimePick32,1342242848
Control4=IDC_TO,SysDateTimePick32,1342242848
Control5=IDC_REQUEST,button,1342242816

[DLG:IDD_MANAGER_ONLINE (Neutral)]
Type=1
Class=CPageOnline
ControlCount=3
Control1=IDC_REQUEST,button,1342242816
Control2=IDC_USERS,SysListView32,1350635529
Control3=IDC_ONLINE_GET,button,1342242816

[DLG:IDD_MANAGER_MARGIN (Neutral)]
Type=1
Class=CPageMargin
ControlCount=1
Control1=IDC_USERS,SysListView32,1350635529

[DLG:IDD_MANAGER_REQUESTS (Neutral)]
Type=1
Class=CPageRequests
ControlCount=1
Control1=IDC_REQUESTS,SysListView32,1350631433

[DLG:IDD_MANAGER_MAIL (Neutral)]
Type=1
Class=CPageMailbox
ControlCount=1
Control1=IDC_MAILS,SysListView32,1350631433

[DLG:IDD_MANAGER_NEWS (Neutral)]
Type=1
Class=CPageNews
ControlCount=1
Control1=IDC_NEWS,SysListView32,1350635529

[DLG:IDD_MANAGER_DEALER (Neutral)]
Type=1
Class=CPageDealer
ControlCount=12
Control1=IDC_STATIC,static,1342308354
Control2=IDC_SERVER,edit,1350631552
Control3=IDC_STATIC,static,1342308354
Control4=IDC_LOGIN,edit,1350639744
Control5=IDC_STATIC,static,1342308354
Control6=IDC_PASSWORD,edit,1350631584
Control7=IDC_CONNECT,button,1342242816
Control8=IDC_DISCONNECT,button,1342242816
Control9=IDC_REQUEST,static,1342312961
Control10=IDC_CONFIRM,button,1342242816
Control11=IDC_REJECT,button,1342242816
Control12=IDC_RETURN,button,1342242816

[DLG:IDD_REQUEST (Neutral)]
Type=1
Class=?
ControlCount=5
Control1=IDC_ALL,button,1342308361
Control2=IDC_SINGLE,button,1342177289
Control3=IDC_LOGIN,edit,1350631552
Control4=IDOK,button,1342242816
Control5=IDCANCEL,button,1342242817

[DLG:IDD_MANAGER_PLUGINS (Neutral)]
Type=1
Class=CPagePlugins
ControlCount=1
Control1=IDC_PLUGINS,SysListView32,1350635529

[CLS:CPagePlugins]
Type=0
HeaderFile=PagePlugins.h
ImplementationFile=PagePlugins.cpp
BaseClass=CPropertyPage
Filter=D
LastObject=CPagePlugins
VirtualFilter=idWC

[DLG:IDD_MANAGER_SUMMARY (Neutral)]
Type=1
Class=CPageSummary
ControlCount=1
Control1=IDC_SUMMARY,SysListView32,1350635529

[CLS:CPageSummary]
Type=0
HeaderFile=pagesummary.h
ImplementationFile=pagesummary.cpp
BaseClass=CPropertyPage
Filter=D
VirtualFilter=idWC
LastObject=CPageSummary

[DLG:IDD_MANAGER_EXPOSURE (Neutral)]
Type=1
Class=CPageExposure
ControlCount=1
Control1=IDC_EXPOSURE,SysListView32,1350635529

[CLS:CPageExposure]
Type=0
HeaderFile=PageExposure.h
ImplementationFile=PageExposure.cpp
BaseClass=CPropertyPage
Filter=D
VirtualFilter=idWC
LastObject=IDC_EXPOSURE

