; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CBalanceManagerDlg
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "BalanceManager.h"

ClassCount=3
Class1=CBalanceManagerApp
Class2=CBalanceManagerDlg

ResourceCount=4
Resource2=IDD_BALANCEMANAGER_DIALOG
Resource3=IDD_BALANCEMANAGER_DIALOG (English (U.S.))
Resource1=IDR_MAINFRAME
Class3=Settings
Resource4=IDD_SETTINGS

[CLS:CBalanceManagerApp]
Type=0
HeaderFile=BalanceManager.h
ImplementationFile=BalanceManager.cpp
Filter=N

[CLS:CBalanceManagerDlg]
Type=0
HeaderFile=BalanceManagerDlg.h
ImplementationFile=BalanceManagerDlg.cpp
Filter=D
LastObject=CBalanceManagerDlg
BaseClass=CDialog
VirtualFilter=dWC



[DLG:IDD_BALANCEMANAGER_DIALOG]
Type=1
ControlCount=3
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_STATIC,static,1342308352
Class=CBalanceManagerDlg

[DLG:IDD_BALANCEMANAGER_DIALOG (English (U.S.))]
Type=1
Class=CBalanceManagerDlg
ControlCount=23
Control1=IDC_CLIENT,edit,1350631552
Control2=IDC_REQUEST,button,1342242816
Control3=IDC_AMOUNT,edit,1350631552
Control4=IDC_COMMENT,edit,1350631552
Control5=IDC_DEPOSIT,button,1342242816
Control6=IDC_WITHDRAWAL,button,1342242816
Control7=IDC_SETTINGS,button,1342242816
Control8=IDC_EXIT,button,1342242816
Control9=IDC_STATIC,static,1342308354
Control10=IDC_STATIC,static,1342308354
Control11=IDC_NAME,edit,1350568064
Control12=IDC_STATIC,static,1342308354
Control13=IDC_COUNTRY,edit,1350568064
Control14=IDC_STATIC,static,1342308354
Control15=IDC_CITY,edit,1350568064
Control16=IDC_STATIC,static,1342308354
Control17=IDC_BALANCE,edit,1350568064
Control18=IDC_STATIC,static,1342308354
Control19=IDC_LOG,SysListView32,1350565889
Control20=IDC_STATIC,button,1342177287
Control21=IDC_STATIC,button,1342177287
Control22=IDC_STATIC,button,1342177287
Control23=IDC_STATIC,static,1342308354

[DLG:IDD_SETTINGS]
Type=1
Class=Settings
ControlCount=8
Control1=IDC_SERVER,edit,1350631552
Control2=IDC_LOGIN,edit,1350631552
Control3=IDC_PASSWORD,edit,1350631584
Control4=IDOK,button,1342242817
Control5=IDCANCEL,button,1342242816
Control6=IDC_STATIC,static,1342308354
Control7=IDC_STATIC,static,1342308354
Control8=IDC_STATIC,static,1342308354

[CLS:Settings]
Type=0
HeaderFile=Settings.h
ImplementationFile=Settings.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC
LastObject=Settings

