// UserRegDlg.cpp : implementation file
//

#include "stdafx.h"
#include "����.h"
#include "UserRegDlg.h"
#include "ADOEx.h"
extern CADOEx theAdo;


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CUserRegDlg dialog


CUserRegDlg::CUserRegDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CUserRegDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CUserRegDlg)
	m_id = _T("");
	m_name = _T("");
	m_pwd = _T("");
	m_money = _T("");
	//}}AFX_DATA_INIT
	t = 0;
}


void CUserRegDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CUserRegDlg)
	DDX_Text(pDX, IDC_EDIT_id, m_id);
	DDX_Text(pDX, IDC_EDIT_name, m_name);
	DDX_Text(pDX, IDC_EDIT_pwd, m_pwd);
	DDX_Text(pDX, IDC_EDIT_total, m_money);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CUserRegDlg, CDialog)
	//{{AFX_MSG_MAP(CUserRegDlg)
	ON_BN_CLICKED(IDC_BUTTON_reg, OnBUTTONreg)
	ON_BN_CLICKED(IDC_BUTTON_cancel, OnBUTTONcancel)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CUserRegDlg message handlers

void CUserRegDlg::OnBUTTONreg() 
{
//	CString sql = 
	// TODO: Add your control notification handler code here
	if(t++ >= 3)
	{
		t = 0;
		m_id = m_pwd = m_name = m_money = "";
		UpdateData(false);
		return ;
	}
	UpdateData(true);
	if(m_id.IsEmpty() || m_pwd.IsEmpty() || m_name.IsEmpty() || m_money.IsEmpty())
	{
		MessageBox("�Բ���������д�Ŀո�û�����룬�벹�ϱ�Ҫ������!");
		return ;
	}
	bool flag = true;
	//�������ݿ⣬���id�Ƿ����,flag = true(�����ڿɴ���);

	CString str = "select * from consumer_tb where consumer_id = '" + m_id + "'";//��ѯ���
	CStringArray result;
	if(theAdo.ExecuteSelSQL(str, "consumer_id", result))
	{
		if(result.GetSize() > 0)
		{
			MessageBox("�ò���ID���Ǵ��ڣ������Ƿ���������");
			return;
		}
	}
	//�����¼
	str = "insert into consumer_tb values('" + m_id + "','" + m_name + "','" + m_money + "','" + m_pwd  +  "', '3')";
	char *p = (LPSTR)(LPCSTR)str;
	if(theAdo.ExecuteNotSelSQL(str))
		MessageBox("��ӳɹ�!\n");
	else
		MessageBox("�Ƿ�����!!!!!!!");
	m_id = m_pwd = m_name = m_money = "";;
	UpdateData(false);
	t = 0;
	
}
void CUserRegDlg::OnBUTTONcancel() 
{
	t = 0;
	m_id = m_pwd = m_name = m_money = "";
	UpdateData(false);
	return ;	
}
