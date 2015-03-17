// LoginDlg.cpp : implementation file
//

#include "stdafx.h"
#include "餐厅.h"
#include "LoginDlg.h"
#include "ADOEx.h"

extern CADOEx theAdo;
extern CString CTname;
extern CString worker;
extern CString CTnum;
extern CString Login_id;
extern int type;

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CLoginDlg dialog


CLoginDlg::CLoginDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CLoginDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CLoginDlg)
	m_id = _T("");
	m_pwd = _T("");
	//}}AFX_DATA_INIT
	type = -1;
}


void CLoginDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CLoginDlg)
	DDX_Text(pDX, IDC_EDIT_id, m_id);
	DDX_Text(pDX, IDC_EDIT_pwd, m_pwd);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CLoginDlg, CDialog)
	//{{AFX_MSG_MAP(CLoginDlg)
	ON_BN_CLICKED(IDC_BUTTON_login, OnBUTTONlogin)
	ON_BN_CLICKED(IDC_RADIO_canteen, OnRADIOcanteen)
	ON_BN_CLICKED(IDC_RADIO_comsumer, OnRADIOcomsumer)
	ON_BN_CLICKED(IDC_RADIO_admin, OnRADIOadmin)
	ON_BN_CLICKED(IDC_BUTTON_cancel, OnBUTTONcancel)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CLoginDlg message handlers

void CLoginDlg::OnBUTTONlogin() 
{
	// TODO: Add your control notification handler code here
	UpdateData(true);
	if(type == -1)
		return;
	if(type == 1)
	{
		CString str = "select * from Admin_tb where admin_id = '" + m_id + "' and pwd = '" + m_pwd + "'";//查询语句
		CStringArray result;
		if(theAdo.ExecuteSelSQL(str, "admin_id", result))
		{
			if(result.GetSize() > 0)
			{
				Login_id = m_id;
				CDialog::OnOK();
				return;
			}		
		}
		else
			MessageBox("密码有误或者用户不存在!");
	}
	if(type == 2)
	{
		CString str = "select * from worker_tb where worker_id = '" + m_id + "' and pwd = '" + m_pwd + "'";//查询语句
		CStringArray result;
		if(theAdo.ExecuteSelSQL(str, "worker_id", result))
		{
			theAdo.ExecuteSelSQL(str, "permission", result);
			if(atoi(result.GetAt(0)) != 4)
			{
				MessageBox("该员工无权限登录!");
				return;
			}			
			if(result.GetSize() > 0)
			{
				Login_id = m_id;
				theAdo.ExecuteSelSQL(str, "cateen_id", result);
				CTnum = result.GetAt(0);
				str = "select * from cateen_tb where cateen_id = '" + CTnum  + "'";
				theAdo.ExecuteSelSQL(str, "cateen_name", result);
				CTname = result.GetAt(0);
				CDialog::OnOK();
				return;
			}
			
		}
		else
			MessageBox("密码有误或者用户不存在!");
	}
	if(type == 3)
	{
		CString str = "select * from consumer_tb where consumer_id = '" + m_id + "' and pwd = '" + m_pwd + "'";//查询语句
		CStringArray result;
		if(theAdo.ExecuteSelSQL(str, "consumer_id", result))
		{
			if(result.GetSize() > 0)
			{
				Login_id = m_id;
				CDialog::OnOK();
				return;
			}
			
		}
		else
			MessageBox("密码有误或者用户不存在!");

	}
//	CDialog::OnOK();
	
}

void CLoginDlg::OnRADIOcanteen() 
{
	// TODO: Add your control notification handler code here
	type = 2;
	
}

void CLoginDlg::OnRADIOcomsumer() 
{
	// TODO: Add your control notification handler code here
	type = 3;
	
}

void CLoginDlg::OnRADIOadmin() 
{
	// TODO: Add your control notification handler code here
	type = 1;	
}

void CLoginDlg::OnBUTTONcancel() 
{
	// TODO: Add your control notification handler code here
	CDialog::OnCancel();;
}
