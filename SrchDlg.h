#if !defined(AFX_SRCHDLG_H__3424FE75_4CCA_4BFC_BC44_39001B40F3FB__INCLUDED_)
#define AFX_SRCHDLG_H__3424FE75_4CCA_4BFC_BC44_39001B40F3FB__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// SrchDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CSrchDlg dialog

class CSrchDlg : public CDialog
{
// Construction
public:
	void canteen_srch();
	void time_srch();
	void kind_srch();
	void person_srch();
	int con;
	CString time;
	CString kind;
	CString id;
	bool SetState(int a, int b, int c);
	CSrchDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CSrchDlg)
	enum { IDD = IDD_DIALOG_count };
	CComboBox	m_ch;
	CListCtrl	m_list;
	CComboBox	m_name;
	CComboBox	m_kind;
	CComboBox	m_id;
	CString	m_begin;
	CString	m_end;
	CString	name;
	CString	m_ans;
	CString	Ctrkinds;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSrchDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CSrchDlg)
	afx_msg void OnBUTTONsrch();
	afx_msg void OnRADIOcanteen();
	afx_msg void OnRADIOkind();
	afx_msg void OnRADIOperson();
	afx_msg void OnRADIOtime();
	afx_msg void OnSelchangeCOMBOid();
	afx_msg void OnSelchangeCOMBOname();
	virtual BOOL OnInitDialog();
	afx_msg void OnSelchangeCOMBOkind();
	afx_msg void OnEditchangeCOMBOch();
	afx_msg void OnSelchangeCOMBOch();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SRCHDLG_H__3424FE75_4CCA_4BFC_BC44_39001B40F3FB__INCLUDED_)
