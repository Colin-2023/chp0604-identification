; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CUseradded
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "Client.h"
LastPage=0

ClassCount=9
Class1=CClientApp
Class2=CClientDoc
Class3=CClientView
Class4=CMainFrame

ResourceCount=5
Resource1=IDD_ABOUTBOX
Resource2=IDD_CLIENT_FORM
Class5=CAboutDlg
Resource3=IDR_MAINFRAME
Resource4=IDD_NETSET_DIALOG
Class6=CLogin
Class7=CNetset
Class8=CUseradded
Class9=CArticlesadded
Resource5=IDD_LOGIN_DIALOG

[CLS:CClientApp]
Type=0
HeaderFile=Client.h
ImplementationFile=Client.cpp
Filter=N

[CLS:CClientDoc]
Type=0
HeaderFile=ClientDoc.h
ImplementationFile=ClientDoc.cpp
Filter=N

[CLS:CClientView]
Type=0
HeaderFile=ClientView.h
ImplementationFile=ClientView.cpp
Filter=D
LastObject=ID_NEXT_PANE
BaseClass=CFormView
VirtualFilter=VWC


[CLS:CMainFrame]
Type=0
HeaderFile=MainFrm.h
ImplementationFile=MainFrm.cpp
Filter=T
LastObject=ID_EDIT_CUT




[CLS:CAboutDlg]
Type=0
HeaderFile=Client.cpp
ImplementationFile=Client.cpp
Filter=D

[DLG:IDD_ABOUTBOX]
Type=1
Class=CAboutDlg
ControlCount=4
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308480
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889

[MNU:IDR_MAINFRAME]
Type=1
Class=CMainFrame
Command1=ID_Login
Command2=ID_Netset
Command3=ID_APP_ABOUT
CommandCount=3

[ACL:IDR_MAINFRAME]
Type=1
Class=CMainFrame
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_SAVE
Command4=ID_FILE_PRINT
Command5=ID_EDIT_UNDO
Command6=ID_EDIT_CUT
Command7=ID_EDIT_COPY
Command8=ID_EDIT_PASTE
Command9=ID_EDIT_UNDO
Command10=ID_EDIT_CUT
Command11=ID_EDIT_COPY
Command12=ID_EDIT_PASTE
Command13=ID_NEXT_PANE
Command14=ID_PREV_PANE
CommandCount=14

[DLG:IDD_CLIENT_FORM]
Type=1
Class=CClientView
ControlCount=4
Control1=IDC_LIST_Articles,SysListView32,1350631425
Control2=IDC_STATIC,button,1342177287
Control3=IDC_LIST_Infos,SysListView32,1350631425
Control4=IDC_STATIC,button,1342177287

[TB:IDR_MAINFRAME]
Type=1
Class=?
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_SAVE
Command4=ID_EDIT_CUT
Command5=ID_EDIT_COPY
Command6=ID_EDIT_PASTE
Command7=ID_FILE_PRINT
Command8=ID_APP_ABOUT
CommandCount=8

[DLG:IDD_NETSET_DIALOG]
Type=1
Class=CNetset
ControlCount=3
Control1=IDC_STATIC,static,1342308352
Control2=IDC_IPADDRESS1,SysIPAddress32,1342242816
Control3=IDOK1,button,1342242816

[DLG:IDD_LOGIN_DIALOG]
Type=1
Class=CLogin
ControlCount=6
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_STATIC,static,1342308352
Control4=IDC_EDIT_Login_UserName,edit,1350631560
Control5=IDC_STATIC,static,1342308352
Control6=IDC_EDIT_Login_PassWord,edit,1350631592

[CLS:CLogin]
Type=0
HeaderFile=Login.h
ImplementationFile=Login.cpp
BaseClass=CDialog
Filter=D
LastObject=CLogin
VirtualFilter=dWC

[CLS:CNetset]
Type=0
HeaderFile=Netset.h
ImplementationFile=Netset.cpp
BaseClass=CDialog
Filter=D
LastObject=CNetset
VirtualFilter=dWC

[CLS:CUseradded]
Type=0
HeaderFile=Useradded.h
ImplementationFile=Useradded.cpp
BaseClass=CDialog
Filter=D
LastObject=ID_AddUsers
VirtualFilter=dWC

[CLS:CArticlesadded]
Type=0
HeaderFile=Articlesadded.h
ImplementationFile=Articlesadded.cpp
BaseClass=CDialog
Filter=D
LastObject=ID_Login
VirtualFilter=dWC

