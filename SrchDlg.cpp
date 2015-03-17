// SrchDlg.cpp : implementation file
//

#include "stdafx.h"
#include "餐厅.h"
#include "SrchDlg.h"
#include "ADOEx.h"
extern CString CTname;
extern CADOEx theAdo;
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
// CSrchDlg dialog


CSrchDlg::CSrchDlg(CWnd* pParent /*=NULL*/)
: CDialog(CSrchDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CSrchDlg)
	m_begin = _T("");
	m_end = _T("");
	name = _T("");
	m_ans = _T("");
	Ctrkinds = _T("");
	//}}AFX_DATA_INIT
}


void CSrchDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSrchDlg)
	DDX_Control(pDX, IDC_COMBO_ch, m_ch);
	DDX_Control(pDX, IDC_LIST_list, m_list);
	DDX_Control(pDX, IDC_COMBO_name, m_name);
	DDX_Control(pDX, IDC_COMBO_kind, m_kind);
	DDX_Control(pDX, IDC_COMBO_id, m_id);
	DDX_Text(pDX, IDC_EDIT_begin, m_begin);
	DDX_Text(pDX, IDC_EDIT_end, m_end);
	DDX_CBString(pDX, IDC_COMBO_name, name);
	DDX_Text(pDX, IDC_EDIT1, m_ans);
	DDX_CBString(pDX, IDC_COMBO_kind, Ctrkinds);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CSrchDlg, CDialog)
//{{AFX_MSG_MAP(CSrchDlg)
ON_BN_CLICKED(IDC_BUTTON_srch, OnBUTTONsrch)
ON_BN_CLICKED(IDC_RADIO_canteen, OnRADIOcanteen)
ON_BN_CLICKED(IDC_RADIO_kind, OnRADIOkind)
ON_BN_CLICKED(IDC_RADIO_person, OnRADIOperson)
ON_BN_CLICKED(IDC_RADIO_time, OnRADIOtime)
ON_CBN_SELCHANGE(IDC_COMBO_id, OnSelchangeCOMBOid)
ON_CBN_SELCHANGE(IDC_COMBO_name, OnSelchangeCOMBOname)
ON_CBN_SELCHANGE(IDC_COMBO_kind, OnSelchangeCOMBOkind)
	ON_CBN_EDITCHANGE(IDC_COMBO_ch, OnEditchangeCOMBOch)
	ON_CBN_SELCHANGE(IDC_COMBO_ch, OnSelchangeCOMBOch)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSrchDlg message handlers

void CSrchDlg::OnBUTTONsrch() 
{
	// TODO: Add your control notification handler code here
	UpdateData(true);
	if(m_begin.IsEmpty() || m_end.IsEmpty())
	{
		MessageBox("开始和结束时间不能为空");
		return;
	}
	CString sql = "select * from order_tb where ";
	switch(con)
	{
		case 1:person_srch();break;//个人；
		case 2:kind_srch();break;//各类
		case 3:time_srch();break;//时间；
		case 4:canteen_srch();break;//餐厅
	}
	//DBGrib控件显示
	//结果显示答案
	//CDialog::OnOK();
}

void CSrchDlg::OnRADIOcanteen() 
{
	con = 4;
	SetState(-1, -1, -1);
	return;
}

void CSrchDlg::OnRADIOkind() 
{
	// TODO: Add your control notification handler code here
	SetState(2, 2, 2);
	con = 2;
	
}

void CSrchDlg::OnRADIOperson() 
{
	con = 1;
	SetState(0, 1, 1);	
}

void CSrchDlg::OnRADIOtime() 
{
	// TODO: Add your control notification handler code here
	con = 3;
	SetState(3, 3, 3);
	
}

bool CSrchDlg::SetState(int a, int b, int c)
{
	int ctrl[5] = {IDC_COMBO_id, IDC_COMBO_name, IDC_COMBO_kind};
	for(int i = 0; i < 3; i++)
	{
		if(i == a || i == b || i == c)
		{
			GetDlgItem(ctrl[i])->EnableWindow(true);
		}
		else
		{
			GetDlgItem(ctrl[i])->EnableWindow(false);
		}
	}
	return true;
}

void CSrchDlg::OnSelchangeCOMBOid() 
{
	// TODO: Add your control notification handler code here
	int nsel = m_id.GetCurSel();
	CString name;
	m_id.GetLBText(nsel, id);
	//查询id对应的顾客名字Name
	CString str = "select * from consumer_tb where consumer_id = '" + id + "'";//查询语句
	CStringArray result;
	if(theAdo.ExecuteSelSQL(str, "consumer_name", result))
	{
		int nSel = m_name.FindStringExact(0, result.GetAt(0));
		if(nSel != -1)
			m_name.SetCurSel(nSel);
	}
}

void CSrchDlg::OnSelchangeCOMBOname() 
{
	int nsel = m_name.GetCurSel();
	CString name;
	m_name.GetLBText(nsel, name);
	//查询id对应的顾客名字Name
	CString str = "select * from consumer_tb where consumer_name = '" + name + "'";//查询语句
	CStringArray result;
	theAdo.ExecuteSelSQL(str, "consumer_id", result);
	id = result.GetAt(0);
	int nSel = m_id.FindStringExact(0, id);
	if(nSel != -1)
		m_id.SetCurSel(nSel);

}

BOOL CSrchDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	m_list.InsertColumn(0, "菜品", LVCFMT_CENTER, 70);
	m_list.InsertColumn(1, "价格", LVCFMT_CENTER, 70);	
	m_list.InsertColumn(2, "餐厅", LVCFMT_CENTER, 70);
	m_list.InsertColumn(3, "时间", LVCFMT_CENTER, 120);
	m_list.SetExtendedStyle(m_list.GetExtendedStyle()|LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES);
	if(type == 2)
	{
		GetDlgItem(IDC_STATIC_ch)->ShowWindow(false);
		GetDlgItem(IDC_COMBO_ch)->ShowWindow(false);
	}
	else
	{
		CString str = "select * from cateen_tb";
		CStringArray result;
		theAdo.ExecuteSelSQL(str, "cateen_name", result);
		for(int i = 0; i < result.GetSize(); i++)
			m_ch.AddString(result.GetAt(i));
	}
	if(type == 3)
	{
		SetState(-1, -1, -1);
		m_id.AddString(Login_id);
		m_id.SetCurSel(0);
		CString str = "select * from consumer_tb where consumer_id = '" + Login_id + "'";//查询语句
		CStringArray result;
		theAdo.ExecuteSelSQL(str, "consumer_name", result);
		m_name.AddString(result.GetAt(0));
		con = 1;
		m_name.SetCurSel(0);
		id = Login_id;
		GetDlgItem(IDC_RADIO_person)->EnableWindow(false);
		GetDlgItem(IDC_RADIO_time)->EnableWindow(false);
		GetDlgItem(IDC_RADIO_kind)->EnableWindow(false);		
		GetDlgItem(IDC_RADIO_canteen)->EnableWindow(false);
		
		return true;
		
	}
	//连接数据库，初始化三个comboBox控件。
	CString str = "select * from consumer_tb";//查询语句
	CStringArray result;
	if(theAdo.ExecuteSelSQL(str, "consumer_id", result))
	{
		for(int i = 0; i < result.GetSize(); i++)
			m_id.AddString(result.GetAt(i));
		theAdo.ExecuteSelSQL(str, "consumer_name", result);
		for(i = 0; i < result.GetSize(); i++)
			m_name.AddString(result.GetAt(i));
	}
	str = "select * from menus_tb";
	if(theAdo.ExecuteSelSQL(str, "kinds", result))
	{
		for(int i = 0; i < result.GetSize(); i++)
			m_kind.AddString(result.GetAt(i));
	}



	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

void CSrchDlg::OnSelchangeCOMBOkind() 
{
	// TODO: Add your control notification handler code here
	//连接数据库，查询kind的种类(加上餐厅名)
	
}

void CSrchDlg::person_srch()
{
	UpdateData(true);
	m_list.DeleteAllItems();
	char tmp[100];
	strcpy(tmp, (LPSTR)(LPCSTR)m_end);
	int len = strlen(tmp);
	tmp[len-1]++;
	m_end = tmp;
	//SQL语句
	CString strSQL = "select * from order_tb, consumer_tb,menus_tb,cateen_tb "
	"where order_tb.comsumer_id = consumer_tb.consumer_id "
	"and order_tb.canteen_id = cateen_tb.cateen_id "
	" and order_tb.special_id = menus_tb.special_id "
	"and order_tb.comsume_time >= '" + m_begin;
	strSQL = strSQL + "'" + "and order_tb.comsume_time < '" + m_end + "'" + " and consumer_id = '" + id + "'";
	char *str = (LPSTR)(LPCSTR)strSQL;
	MessageBox(strSQL);
	CString fields[] = {"name", "price", "cateen_name", "comsume_time"};
	CStringArray strField;
	for(int i = 0; i < 4; i++)
		strField.Add(fields[i]);	
	CStringArray strResult;
	double ans = 0;
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
				m_list.SetItemText(nItem, j, strItem);
				if(j == 1)
					ans += atof(strItem);
			}
		}
	}
	m_ans.Format("	总金额为%.2lf元。", ans);
	UpdateData(false);

}

void CSrchDlg::kind_srch()
{
	UpdateData(true);
	m_list.DeleteAllItems();
	char tmp[100];
	strcpy(tmp, (LPSTR)(LPCSTR)m_end);
	int len = strlen(tmp);
	tmp[len-1]++;
	m_end = tmp;
	//SQL语句
	CString strSQL = "select * from order_tb, menus_tb "
	" where order_tb.special_id = menus_tb.special_id "
	"and order_tb.comsume_time >= '" + m_begin;
	strSQL = strSQL + "'" + "and order_tb.comsume_time < '" + m_end + "'" + " and kinds = '" + Ctrkinds + "'";
	char *str = (LPSTR)(LPCSTR)strSQL;
	MessageBox(strSQL);
	CString fields[] = {"name", "price", "comsume_time"};
	CStringArray strField;
	for(int i = 0; i < 3; i++)
		strField.Add(fields[i]);	
	CStringArray strResult;
	double ans = 0;
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
				if(j == 2)	j++;
				m_list.SetItemText(nItem, j, strItem);
				if(j == 1)
					ans += atof(strItem);
			}
			m_list.SetItemText(nItem, 2, CTname);
		}
	}
	m_ans.Format("	总金额为%.2lf元。", ans);
	UpdateData(false);


}

void CSrchDlg::time_srch()
{
	UpdateData(true);
	m_list.DeleteAllItems();
	char tmp[100];
	strcpy(tmp, (LPSTR)(LPCSTR)m_end);
	int len = strlen(tmp);
	tmp[len-1]++;
	m_end = tmp;
	//SQL语句
	CString strSQL = "select * from order_tb, menus_tb "
	" where order_tb.special_id = menus_tb.special_id and "
	"order_tb.comsume_time >= '" + m_begin;
	strSQL = strSQL  + "' and order_tb.comsume_time < '" + m_end + "'" + " and canteen_id = '" + CTnum + "'" ;
	char *str = (LPSTR)(LPCSTR)strSQL;
	MessageBox(strSQL);
	CString fields[] = {"name", "price", "comsume_time"};
	CStringArray strField;
	for(int i = 0; i < 3; i++)
		strField.Add(fields[i]);	
	CStringArray strResult;
	double ans = 0;
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
				if(j == 2)	j++;
				m_list.SetItemText(nItem, j, strItem);
				if(j == 1)
					ans += atof(strItem);
			}
			m_list.SetItemText(nItem, 2, CTname);
		}
	}
	m_ans.Format("	总金额为%.2lf元。", ans);
	UpdateData(false);
}

void CSrchDlg::canteen_srch()
{
	time_srch();
}

void CSrchDlg::OnEditchangeCOMBOch() 
{

	
}

void CSrchDlg::OnSelchangeCOMBOch() 
{
	int nsel = m_ch.GetCurSel();
	m_ch.GetLBText(nsel, CTname);
	MessageBox(CTname);
	//查询id对应的顾客名字Name
	CString str = "select * from cateen_tb where cateen_name = '" + CTname + "'";//查询语句
	CStringArray result;
	theAdo.ExecuteSelSQL(str, "cateen_id", result);
	CTnum = result.GetAt(0);
	
}
