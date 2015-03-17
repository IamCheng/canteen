#if !defined(AFX_WORKERDLG_H__81D69A17_0E6B_46E9_AC85_1AFF13A43DA4__INCLUDED_)
#define AFX_WORKERDLG_H__81D69A17_0E6B_46E9_AC85_1AFF13A43DA4__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// workerDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CworkerDlg dialog

class CworkerDlg : public CDialog
{
// Construction
public:
	int t;
	CworkerDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CworkerDlg)
	enum { IDD = IDD_DIALOG_worker };
	CEdit	m_ct;
	CString	m_salary;
	CString	m_id;
	CString	m_name;
	CString	m_job;
	CString	m_age;
	CString	m_pwd;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CworkerDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CworkerDlg)
	afx_msg void OnBUTTONsure();
	afx_msg void OnBUTTONcancel();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_WORKERDLG_H__81D69A17_0E6B_46E9_AC85_1AFF13A43DA4__INCLUDED_)
