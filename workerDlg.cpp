// workerDlg.cpp : implementation file
//

#include "stdafx.h"
#include "����.h"
#include "workerDlg.h"
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
// CworkerDlg dialog


CworkerDlg::CworkerDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CworkerDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CworkerDlg)
	m_salary = _T("");
	m_id = _T("");
	m_name = _T("");
	m_job = _T("");
	m_age = _T("");
	m_pwd = _T("");
	//}}AFX_DATA_INIT
	t = 1;

}


void CworkerDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CworkerDlg)
	DDX_Control(pDX, IDC_EDIT6, m_ct);
	DDX_Text(pDX, IDC_EDIT_salary, m_salary);
	DDX_Text(pDX, IDC_EDIT_worker_id, m_id);
	DDX_Text(pDX, IDC_EDIT_worker_name, m_name);
	DDX_Text(pDX, IDC_EDIT_job, m_job);
	DDX_Text(pDX, IDC_EDIT_age, m_age);
	DDX_Text(pDX, IDC_EDIT_pwd, m_pwd);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CworkerDlg, CDialog)
	//{{AFX_MSG_MAP(CworkerDlg)
	ON_BN_CLICKED(IDC_BUTTON_sure, OnBUTTONsure)
	ON_BN_CLICKED(IDC_BUTTON_cancel, OnBUTTONcancel)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CworkerDlg message handlers

void CworkerDlg::OnBUTTONsure() 
{
	if(t++ >= 3)
	{
		m_age = m_id = m_job = m_salary = m_name = m_pwd = "";
		UpdateData(false);
	}
	UpdateData(true);
	if(m_id.IsEmpty() || m_name.IsEmpty() || m_salary.IsEmpty())
	{
		MessageBox("�Բ���������д�Ŀո�û�����룬�벹�ϱ�Ҫ������!");
		return ;
	}
	if(int mon = atof(m_salary) <= 0)
	{
		MessageBox("������������!");
		return;
	}
	bool flag = true;
	//�������ݿ⣬���id�Ƿ����,flag = true(�����ڿɴ���);
	CString str = "select * from worker_tb where worker_id = '" + m_id + "'";//��ѯ���
	CStringArray result;
	if(theAdo.ExecuteSelSQL(str, "worker_id", result))
	{
		if(result.GetSize() > 0)
			flag = false;
	}
	else
		flag = true;
	if(flag)
	{
		//�����¼
		str = "";
		str = str + "insert into worker_tb values('" + m_id + "','" + CTnum + "','" + m_name + "','" + m_job + "','" + m_age + "','" + m_salary + "','"; 	
		CString permission = "4";
		if(!m_pwd.IsEmpty())
			str +=  "4', '" + m_pwd + "')";
		else
			str += "0','')";
		
		theAdo.ExecuteNotSelSQL(str);
		m_age = m_id = m_job = m_salary = m_name = m_pwd = "";
		MessageBox("��ӳɹ�!\n");
		UpdateData(false);
	}
	else
	{
		MessageBox("�ù������Ǵ��ڣ������Ƿ���������");
	}
}

void CworkerDlg::OnBUTTONcancel() 
{
	m_age = m_id = m_job = m_name = m_salary = m_pwd = "";
	UpdateData(false);
//	CDialog::OnCancel();	
}

BOOL CworkerDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	m_ct.SetWindowText(CTname);	
	return TRUE;  
	// return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
