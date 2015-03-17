#if !defined(AFX_ORDERDLG_H__6CD60FA6_124D_44D4_AA44_B8C4A9AFF17A__INCLUDED_)
#define AFX_ORDERDLG_H__6CD60FA6_124D_44D4_AA44_B8C4A9AFF17A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// orderDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CorderDlg dialog

class CorderDlg : public CDialog
{
// Construction
public:
	double total;
	int type;
	CString m_id;
	CString m_name;
	CorderDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CorderDlg)
	enum { IDD = IDD_DIALOG_order };
	CEdit	m_cardctr;
	CListCtrl	m_list;
	CComboBox	m_menu;
	CString	m_num;
	CString	m_card;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CorderDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CorderDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnBUTTONadd();
	afx_msg void OnSelchangeCOMBOmenus();
	afx_msg void OnBUTTONdel();
	afx_msg void OnBUTTONsubmit();
	afx_msg void OnRADIOcard();
	afx_msg void OnRADIOcash();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ORDERDLG_H__6CD60FA6_124D_44D4_AA44_B8C4A9AFF17A__INCLUDED_)
