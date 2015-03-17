; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CSrchDlg
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "²ÍÌü.h"

ClassCount=11
Class1=CMyApp
Class2=CMyDlg
Class3=CAboutDlg

ResourceCount=10
Resource1=IDD_DIALOG_userReg
Resource2=IDR_MAINFRAME
Resource3=IDD_DIALOG_order
Class4=CfoodDlg
Resource4=IDD_MY_DIALOG
Class5=CworkerDlg
Class6=CTabSheet
Resource5=IDD_DIALOG_FOOD
Class7=CSrchDlg
Resource6=IDD_DIALOG_count
Class8=CCTRegDlg
Resource7=IDD_ABOUTBOX
Class9=CUserRegDlg
Resource8=IDD_DIALOG_CTReg
Class10=CorderDlg
Resource9=IDD_DIALOG_worker
Class11=CLoginDlg
Resource10=IDD_DIALOG_login

[CLS:CMyApp]
Type=0
HeaderFile=²ÍÌü.h
ImplementationFile=²ÍÌü.cpp
Filter=N

[CLS:CMyDlg]
Type=0
HeaderFile=²ÍÌüDlg.h
ImplementationFile=²ÍÌüDlg.cpp
Filter=D
LastObject=CMyDlg
BaseClass=CDialog
VirtualFilter=dWC

[CLS:CAboutDlg]
Type=0
HeaderFile=²ÍÌüDlg.h
ImplementationFile=²ÍÌüDlg.cpp
Filter=D

[DLG:IDD_ABOUTBOX]
Type=1
Class=CAboutDlg
ControlCount=4
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308480
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889

[DLG:IDD_MY_DIALOG]
Type=1
Class=CMyDlg
ControlCount=1
Control1=IDC_TAB1,SysTabControl32,1342177536

[DLG:IDD_DIALOG_FOOD]
Type=1
Class=CfoodDlg
ControlCount=15
Control1=IDC_STATIC,button,1342177287
Control2=IDC_STATIC,static,1342308865
Control3=IDC_STATIC,static,1342308865
Control4=IDC_STATIC,static,1342308865
Control5=IDC_STATIC,static,1342308865
Control6=IDC_STATIC,static,1342308865
Control7=IDC_STATIC,static,1342308865
Control8=IDC_EDIT_id,edit,1350631552
Control9=IDC_EDIT_price,edit,1350631552
Control10=IDC_EDIT_kind,edit,1350631552
Control11=IDC_EDIT_name,edit,1350631552
Control12=IDC_EDIT_discnt,edit,1350631552
Control13=IDC_EDIT6,edit,1484849280
Control14=IDC_BUTTON_sure,button,1342242816
Control15=IDC_BUTTON_cancel,button,1342177280

[CLS:CfoodDlg]
Type=0
HeaderFile=foodDlg.h
ImplementationFile=foodDlg.cpp
BaseClass=CDialog
Filter=D
LastObject=IDC_BUTTON_sure
VirtualFilter=dWC

[DLG:IDD_DIALOG_worker]
Type=1
Class=CworkerDlg
ControlCount=18
Control1=IDC_STATIC,button,1342177287
Control2=IDC_STATIC,static,1342308865
Control3=IDC_STATIC,static,1342308865
Control4=IDC_STATIC,static,1342308865
Control5=IDC_STATIC,static,1342308865
Control6=IDC_STATIC,static,1342308354
Control7=IDC_EDIT_worker_id,edit,1350631552
Control8=IDC_EDIT_worker_name,edit,1350631552
Control9=IDC_EDIT_age,edit,1350639744
Control10=IDC_EDIT_salary,edit,1350631552
Control11=IDC_EDIT6,edit,1484849280
Control12=IDC_BUTTON_sure,button,1342242816
Control13=IDC_BUTTON_cancel,button,1342177280
Control14=IDC_STATIC,static,1342308865
Control15=IDC_STATIC,static,1342308865
Control16=IDC_EDIT_job,edit,1350631552
Control17=IDC_EDIT_pwd,edit,1350631584
Control18=IDC_STATIC,static,1342308865

[CLS:CworkerDlg]
Type=0
HeaderFile=workerDlg.h
ImplementationFile=workerDlg.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC
LastObject=CworkerDlg

[CLS:CTabSheet]
Type=0
HeaderFile=TabSheet.h
ImplementationFile=TabSheet.cpp
BaseClass=CTabCtrl
Filter=W
LastObject=CTabSheet

[DLG:IDD_DIALOG_count]
Type=1
Class=CSrchDlg
ControlCount=23
Control1=IDC_STATIC,static,1342308865
Control2=IDC_STATIC_caption,button,1342177287
Control3=IDC_RADIO_person,button,1342308361
Control4=IDC_RADIO_time,button,1342177289
Control5=IDC_RADIO_canteen,button,1342177289
Control6=IDC_RADIO_kind,button,1342177289
Control7=IDC_STATIC,button,1342177287
Control8=IDC_BUTTON_srch,button,1342251008
Control9=IDC_COMBO_id,combobox,1344340226
Control10=IDC_STATIC_id,static,1342308352
Control11=IDC_COMBO_name,combobox,1344340226
Control12=IDC_STATIC_name,static,1342308352
Control13=IDC_COMBO_kind,combobox,1344340226
Control14=IDC_STATIC,static,1342308352
Control15=IDC_EDIT1,edit,1476460676
Control16=IDC_STATIC_time,static,1342308352
Control17=IDC_STATIC,button,1342177287
Control18=IDC_LIST_list,SysListView32,1350631425
Control19=IDC_EDIT_begin,edit,1350631552
Control20=IDC_STATIC,static,1342308864
Control21=IDC_EDIT_end,edit,1350631552
Control22=IDC_COMBO_ch,combobox,1344340226
Control23=IDC_STATIC_ch,static,1342308865

[CLS:CSrchDlg]
Type=0
HeaderFile=SrchDlg.h
ImplementationFile=SrchDlg.cpp
BaseClass=CDialog
Filter=D
LastObject=CSrchDlg
VirtualFilter=dWC

[DLG:IDD_DIALOG_CTReg]
Type=1
Class=CCTRegDlg
ControlCount=15
Control1=IDC_STATIC,static,1342308865
Control2=IDC_STATIC,button,1342177287
Control3=IDC_STATIC,static,1342308865
Control4=IDC_STATIC,static,1342308865
Control5=IDC_STATIC,static,1342308865
Control6=IDC_STATIC,static,1342308865
Control7=IDC_STATIC,static,1342308354
Control8=IDC_EDIT_ct_id,edit,1350631552
Control9=IDC_EDIT_ct_name,edit,1350631552
Control10=IDC_EDIT_regtime,edit,1350639744
Control11=IDC_EDIT_num,edit,1350631552
Control12=IDC_EDIT_address,edit,1350631552
Control13=IDC_STATIC,static,1342308352
Control14=IDC_EDIT_reg_person,edit,1350631552
Control15=IDC_BUTTON_reg,button,1342242816

[CLS:CCTRegDlg]
Type=0
HeaderFile=CTRegDlg.h
ImplementationFile=CTRegDlg.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC
LastObject=CCTRegDlg

[DLG:IDD_DIALOG_userReg]
Type=1
Class=CUserRegDlg
ControlCount=11
Control1=IDC_EDIT_name,edit,1350631552
Control2=IDC_EDIT_id,edit,1350631552
Control3=IDC_EDIT_total,edit,1350631552
Control4=IDC_STATIC_name,static,1342308865
Control5=IDC_STATIC_id,static,1342308865
Control6=IDC_STATIC,static,1342308865
Control7=IDC_STATIC,static,1342308865
Control8=IDC_EDIT_pwd,edit,1350631584
Control9=IDC_STATIC,static,1342308865
Control10=IDC_BUTTON_reg,button,1342242816
Control11=IDC_BUTTON_cancel,button,1342242816

[CLS:CUserRegDlg]
Type=0
HeaderFile=UserRegDlg.h
ImplementationFile=UserRegDlg.cpp
BaseClass=CDialog
Filter=D
LastObject=CUserRegDlg
VirtualFilter=dWC

[DLG:IDD_DIALOG_order]
Type=1
Class=CorderDlg
ControlCount=14
Control1=IDC_LIST1,SysListView32,1350631425
Control2=IDC_STATIC,static,1342308865
Control3=IDC_COMBO_menus,combobox,1344340226
Control4=IDC_STATIC,static,1342308865
Control5=IDC_BUTTON_add,button,1342242816
Control6=IDC_BUTTON_del,button,1342242816
Control7=IDC_STATIC_num,static,1342308865
Control8=IDC_EDIT1,edit,1350639745
Control9=IDC_BUTTON_submit,button,1342242816
Control10=IDC_RADIO_card,button,1342177289
Control11=IDC_STATIC,button,1342177287
Control12=IDC_RADIO_cash,button,1342177289
Control13=IDC_EDIT_cardnum,edit,1082196096
Control14=ID_static_cardnum,static,1073873409

[CLS:CorderDlg]
Type=0
HeaderFile=orderDlg.h
ImplementationFile=orderDlg.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC
LastObject=CorderDlg

[CLS:CLoginDlg]
Type=0
HeaderFile=LoginDlg.h
ImplementationFile=LoginDlg.cpp
BaseClass=CDialog
Filter=D
LastObject=CLoginDlg
VirtualFilter=dWC

[DLG:IDD_DIALOG_login]
Type=1
Class=CLoginDlg
ControlCount=11
Control1=IDC_STATIC,static,1342177806
Control2=IDC_STATIC,button,1342177287
Control3=IDC_STATIC,static,1342308865
Control4=IDC_STATIC,static,1342308865
Control5=IDC_EDIT_id,edit,1350631552
Control6=IDC_EDIT_pwd,edit,1350631584
Control7=IDC_RADIO_admin,button,1342308361
Control8=IDC_RADIO_comsumer,button,1342177289
Control9=IDC_RADIO_canteen,button,1342177289
Control10=IDC_BUTTON_login,button,1342242816
Control11=IDC_BUTTON_cancel,button,1342242816

