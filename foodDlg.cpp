// foodDlg.cpp : implementation file
//

#include "stdafx.h"
#include "����.h"
#include "foodDlg.h"
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
// CfoodDlg dialog


CfoodDlg::CfoodDlg(CWnd* pParent /*=NULL*/)
: CDialog(CfoodDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CfoodDlg)
	m_discnt = _T("");
	m_food_kind = _T("");
	m_food_id = _T("");
	m_food_name = _T("");
	m_food_price = _T("");
	m_canteen = _T("");
	//}}AFX_DATA_INIT
	t = 1;

}


void CfoodDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CfoodDlg)
	DDX_Text(pDX, IDC_EDIT_discnt, m_discnt);
	DDX_Text(pDX, IDC_EDIT_kind, m_food_kind);
	DDX_Text(pDX, IDC_EDIT_id, m_food_id);
	DDX_Text(pDX, IDC_EDIT_name, m_food_name);
	DDX_Text(pDX, IDC_EDIT_price, m_food_price);
	DDX_Text(pDX, IDC_EDIT6, m_canteen);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CfoodDlg, CDialog)
//{{AFX_MSG_MAP(CfoodDlg)
ON_BN_CLICKED(IDC_BUTTON_sure, OnBUTTONsure)
	ON_BN_CLICKED(IDC_BUTTON_cancel, OnBUTTONcancel)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CfoodDlg message handlers

void CfoodDlg::OnBUTTONsure() 
{
	// TODO: Add your control notification handler code here
	if(t++ >= 3)
	{
		t = 0;
		m_food_id = m_food_kind = m_food_name = m_food_price = m_discnt = "";
		UpdateData(false);
		return ;
	}
	UpdateData(true);
	if(m_food_id.IsEmpty() || m_food_kind.IsEmpty() || m_food_name.IsEmpty() || m_food_price.IsEmpty())
	{
		MessageBox("�Բ���������д�Ŀո�û�����룬�벹�ϱ�Ҫ������!");
		return ;
	}
	if(atof(m_discnt) > 10 || atof(m_discnt) < 0)
	{
		MessageBox("�ۿ���������!");
		return;
	}
	if(atoi(m_food_price) > 100000 || atoi(m_food_price) < 0)
	{
		MessageBox("�۸�����");
		return ;
	}
	bool flag = true;
	//�������ݿ⣬���id�Ƿ����,flag = true(�����ڿɴ���);

	CString str = "select * from menus_tb where special_id = '" + m_food_id + "'";//��ѯ���
	CStringArray result;
	if(theAdo.ExecuteSelSQL(str, "special_id", result))
	{
		if(result.GetSize() > 0)
		{
			MessageBox("�ò���ID���Ǵ��ڣ������Ƿ���������");
			return;
		}
	}
	//�����¼
	str = "insert into menus_tb values('" + m_food_id + "','" + m_food_name + "','" + m_food_kind + "','" + m_food_price + "','" + m_discnt  +  "')";
	char *p = (LPSTR)(LPCSTR)str;
	theAdo.ExecuteNotSelSQL(str);
	MessageBox("��ӳɹ�!\n");
	m_food_id = m_food_kind = m_food_name = m_food_price = m_discnt = "";;
	UpdateData(false);
}

void CfoodDlg::OnBUTTONcancel() 
{
	t = 0;
	m_food_id = m_food_kind = m_food_name = m_food_price = m_discnt = "";
	UpdateData(false);
}

BOOL CfoodDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	GetDlgItem(IDC_EDIT6)->SetWindowText(CTname);
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
