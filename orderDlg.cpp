// orderDlg.cpp : implementation file
//

#include "stdafx.h"
#include "餐厅.h"
#include "orderDlg.h"
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
// CorderDlg dialog


CorderDlg::CorderDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CorderDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CorderDlg)
	m_num = _T("");
	m_card = _T("");
	//}}AFX_DATA_INIT
	type = 0;
	total = 0;
}


void CorderDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CorderDlg)
	DDX_Control(pDX, IDC_EDIT_cardnum, m_cardctr);
	DDX_Control(pDX, IDC_LIST1, m_list);
	DDX_Control(pDX, IDC_COMBO_menus, m_menu);
	DDX_Text(pDX, IDC_EDIT1, m_num);
	DDX_Text(pDX, IDC_EDIT_cardnum, m_card);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CorderDlg, CDialog)
	//{{AFX_MSG_MAP(CorderDlg)
	ON_BN_CLICKED(IDC_BUTTON_add, OnBUTTONadd)
	ON_CBN_SELCHANGE(IDC_COMBO_menus, OnSelchangeCOMBOmenus)
	ON_BN_CLICKED(IDC_BUTTON_del, OnBUTTONdel)
	ON_BN_CLICKED(IDC_BUTTON_submit, OnBUTTONsubmit)
	ON_BN_CLICKED(IDC_RADIO_card, OnRADIOcard)
	ON_BN_CLICKED(IDC_RADIO_cash, OnRADIOcash)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CorderDlg message handlers

BOOL CorderDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();	
	CString str = "select * from menus_tb";//查询语句
	CStringArray result;
	if(theAdo.ExecuteSelSQL(str, "name", result))
	{
		for(int i = 0; i < result.GetSize(); i++)
			m_menu.AddString(result.GetAt(i));	
	}
	m_list.InsertColumn(0,"菜谱编号",LVCFMT_LEFT,80);
	m_list.InsertColumn(1,"菜名",LVCFMT_LEFT,90);
	m_list.InsertColumn(2,"种类",LVCFMT_LEFT,125);
	m_list.InsertColumn(3,"价格",LVCFMT_LEFT,125);
	m_list.InsertColumn(4, "折扣",LVCFMT_LEFT,125);
	m_list.InsertColumn(5, "数量", LVCFMT_LEFT,50);
	m_list.SetExtendedStyle(m_list.GetExtendedStyle()|LVS_EX_FULLROWSELECT
		|LVS_EX_GRIDLINES);
	// TODO: Add extra initialization here
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CorderDlg::OnBUTTONadd() 
{
	// TODO: Add your control notification handler code here
	UpdateData(true);
	if(m_num.IsEmpty())
	{
		MessageBox("数量不能为空");
		return ;
	}
	char *str = (LPSTR)(LPCSTR)m_name;
	CString strSQL = "select * from menus_tb where name = '" + m_name + "'";//查询语句
	CString fields[] = {"special_id", "name", "kinds", "price", "discount"};
	str = (LPSTR)(LPCSTR)strSQL;
	CStringArray strField;
	for(int i = 0; i < 5; i++)
		strField.Add(fields[i]);
	
	CStringArray strResult;
	if(theAdo.ExecuteSelSQL(strSQL, strField, strResult))
	{	
		for(i=0;i<strResult.GetSize();i++)
		{
			CString strID=theAdo.GetSingleString(strResult.GetAt(i), 1);
			int nItem = m_list.InsertItem(m_list.GetItemCount(),strID);
			for(int j = 1; j < strField.GetSize(); j++)
			{
				CString strItem = theAdo.GetSingleString(strResult.GetAt(i), j+1);
				strItem.TrimRight();
				if(j == 3)
				{
					total += atof(strItem) * atof(m_num) * atof(theAdo.GetSingleString(strResult.GetAt(i), j+2)) / 10;
					strItem.Format("%.2lf", atof(strItem) * atof(m_num) * atof(theAdo.GetSingleString(strResult.GetAt(i), j+2)) / 10);
				}
				m_list.SetItemText(nItem, j, strItem);
			}
			m_list.SetItemText(nItem, j, m_num);
		}
	}
	
}

void CorderDlg::OnSelchangeCOMBOmenus() 
{
	// TODO: Add your control notification handler code here
	int nSel = m_menu.GetCurSel();
	m_menu.GetLBText(nSel, m_name);
	
}

void CorderDlg::OnBUTTONdel() 
{
	// TODO: Add your control notification handler code here
	int nSel = m_list.GetNextItem(-1, LVNI_SELECTED);
	if(nSel == -1)
		return;
	CString mon = m_list.GetItemText(nSel, 3);
	total -= atof(mon);
	m_list.DeleteItem(nSel);
	
}

void CorderDlg::OnBUTTONsubmit() 
{
	// TODO: Add your control notification handler code here
	if(0 == m_list.GetItemCount())
	{
		MessageBox("抱歉，你还未点菜");
		return;
	}
	if(type == 1)
	{
		UpdateData(true);
		CString str = "select * from consumer_tb where consumer_id = '" + m_card + "'";//查询语句
		char *sr = (LPSTR)(LPCSTR)str;
		CStringArray result;
		if(theAdo.ExecuteSelSQL(str, "total", result))
		{
			if(result.GetSize() > 0)
			{
				double tmp = atof(result.GetAt(0));
				if(total > tmp)
				{
					MessageBox("余额不足!");
					return;
				}
				CString rest;
				rest.Format("%.2lf", tmp-total);
				//更新数据	CString sql = "update
				str = "update consumer_tb set total = '" + rest + "' where consumer_id = '" + m_card + "'";
				if(theAdo.ExecuteNotSelSQL(str))
				{
					MessageBox("支付成功!欢迎下次光临.");
				}
			}
		}
	}
	else
	{
		m_card = "tmp";	
		MessageBox("现金支付成功!欢迎下次光临.");
	}
	CString m_time, worker_id = Login_id;
	CTime tTime = CTime::GetCurrentTime();
	m_time = tTime.Format("%Y-%m-%d %H:%M:%S");
	char *p = (LPSTR)(LPCSTR)m_time;
	for(int i = 0; i < m_list.GetItemCount(); i++)
	{
		CString special_id = m_list.GetItemText(i, 0);
		CString num = m_list.GetItemText(i, 5);
		CString discnt = m_list.GetItemText(i, 4);
		CString pay = m_list.GetItemText(i, 3);
	//插入记录
		CString str = "insert into order_tb values('" + special_id + "','" + m_time + "','" + CTnum + "','" + m_card + "','" + num +   "','" + discnt +   "','" + pay +  "','" + worker_id +  "')";
		char *p = (LPSTR)(LPCSTR)str;
		theAdo.ExecuteNotSelSQL(str);
//		MessageBox("添加成功!\n");
	}

	m_list.DeleteAllItems();	//清理控件的内容。
	//如果选择刷卡，先判断是否有充足的余额
	
	//把订单内容插入数据库	
	//显示应付的价钱

	
}

void CorderDlg::OnRADIOcard() 
{
	type = 1;
	GetDlgItem(ID_static_cardnum)->ShowWindow(true);
	m_cardctr.ShowWindow(true);	
	
}

void CorderDlg::OnRADIOcash() 
{
	type = 2;
	GetDlgItem(ID_static_cardnum)->ShowWindow(false);
	m_cardctr.ShowWindow(SW_HIDE);	
}
