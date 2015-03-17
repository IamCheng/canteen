#if !defined(AFX_FOODDLG_H__45EADD2C_A863_4ED1_A511_DBEA2340C127__INCLUDED_)
#define AFX_FOODDLG_H__45EADD2C_A863_4ED1_A511_DBEA2340C127__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// foodDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CfoodDlg dialog

class CfoodDlg : public CDialog
{
// Construction
public:
	int t;
	CfoodDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CfoodDlg)
	enum { IDD = IDD_DIALOG_FOOD };
	CString	m_discnt;
	CString	m_food_kind;
	CString	m_food_id;
	CString	m_food_name;
	CString	m_food_price;
	CString	m_canteen;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CfoodDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CfoodDlg)
	afx_msg void OnBUTTONsure();
	afx_msg void OnBUTTONcancel();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_FOODDLG_H__45EADD2C_A863_4ED1_A511_DBEA2340C127__INCLUDED_)
