// CTRegDlg.cpp : implementation file
//

#include "stdafx.h"
#include "餐厅.h"
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
	//插入数据库（表中）
	UpdateData(true);
	if(m_addr.IsEmpty()||m_boss.IsEmpty()||m_id.IsEmpty()||m_name.IsEmpty()||m_time.IsEmpty()||m_num.IsEmpty())
	{
		MessageBox("请输入完整的信息\n");
		return;
	}
	CString str = "select * from cateen_tb where cateen_id = '" + m_id + "'";//查询语句
	bool flag = true;
	//连接数据库，检查id是否存在,flag = true(不存在可存入);
	CStringArray result;
	if(theAdo.ExecuteSelSQL(str, "cateen_id", result))
	{
		if(result.GetSize() > 0)
		{
			MessageBox("该餐厅ID已是存在，请检查是否输入有误");
			return;
		}
	}

	//插入记录
	str = "insert into cateen_tb values('" + m_id + "','" + m_name + "','" + m_num + "','" + m_time + "','" + m_addr + "','" + m_boss + "')";
	theAdo.ExecuteNotSelSQL(str);
	m_name = m_id = m_time = m_addr = m_boss = m_num = "";
	MessageBox("添加成功!\n");
	UpdateData(false);

	//CStringArray result;
	
}
