#if !defined(AFX_LOGINDLG_H__AAA0C073_F3E4_4144_BEB0_4A9394AE07A2__INCLUDED_)
#define AFX_LOGINDLG_H__AAA0C073_F3E4_4144_BEB0_4A9394AE07A2__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// LoginDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CLoginDlg dialog

class CLoginDlg : public CDialog
{
// Construction
public:
	CLoginDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CLoginDlg)
	enum { IDD = IDD_DIALOG_login };
	CString	m_id;
	CString	m_pwd;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CLoginDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CLoginDlg)
	afx_msg void OnBUTTONlogin();
	afx_msg void OnRADIOcanteen();
	afx_msg void OnRADIOcomsumer();
	afx_msg void OnRADIOadmin();
	afx_msg void OnBUTTONcancel();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_LOGINDLG_H__AAA0C073_F3E4_4144_BEB0_4A9394AE07A2__INCLUDED_)
