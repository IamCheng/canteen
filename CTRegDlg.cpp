// CTRegDlg.cpp : implementation file
//

#include "stdafx.h"
#include "����.h"
#include "CTRegDlg.h"
#include "ADOEx.h"
extern CADOEx theAdo;


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CCTRegDlg dialog


CCTRegDlg::CCTRegDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CCTRegDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CCTRegDlg)
	m_addr = _T("");
	m_id = _T("");
	m_name = _T("");
	m_num = _T("");
	m_time = _T("");
	m_boss = _T("");
	//}}AFX_DATA_INIT
}


void CCTRegDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CCTRegDlg)
	DDX_Text(pDX, IDC_EDIT_address, m_addr);
	DDX_Text(pDX, IDC_EDIT_ct_id, m_id);
	DDX_Text(pDX, IDC_EDIT_ct_name, m_name);
	DDX_Text(pDX, IDC_EDIT_num, m_num);
	DDX_Text(pDX, IDC_EDIT_regtime, m_time);
	DDX_Text(pDX, IDC_EDIT_reg_person, m_boss);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CCTRegDlg, CDialog)
	//{{AFX_MSG_MAP(CCTRegDlg)
	ON_BN_CLICKED(IDC_BUTTON_reg, OnBUTTONreg)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCTRegDlg message handlers

void CCTRegDlg::OnBUTTONreg() 
{
	// TODO: Add your control notification handler code here
	//�������ݿ⣨���У�
	UpdateData(true);
	if(m_addr.IsEmpty()||m_boss.IsEmpty()||m_id.IsEmpty()||m_name.IsEmpty()||m_time.IsEmpty()||m_num.IsEmpty())
	{
		MessageBox("��������������Ϣ\n");
		return;
	}
	CString str = "select * from cateen_tb where cateen_id = '" + m_id + "'";//��ѯ���
	bool flag = true;
	//�������ݿ⣬���id�Ƿ����,flag = true(�����ڿɴ���);
	CStringArray result;
	if(theAdo.ExecuteSelSQL(str, "cateen_id", result))
	{
		if(result.GetSize() > 0)
		{
			MessageBox("�ò���ID���Ǵ��ڣ������Ƿ���������");
			return;
		}
	}

	//�����¼
	str = "insert into cateen_tb values('" + m_id + "','" + m_name + "','" + m_num + "','" + m_time + "','" + m_addr + "','" + m_boss + "')";
	theAdo.ExecuteNotSelSQL(str);
	m_name = m_id = m_time = m_addr = m_boss = m_num = "";
	MessageBox("��ӳɹ�!\n");
	UpdateData(false);

	//CStringArray result;
	
}
