#if !defined(AFX_USERREGDLG_H__6BF4E1C8_36AD_4B3D_89DB_5726D2B68425__INCLUDED_)
#define AFX_USERREGDLG_H__6BF4E1C8_36AD_4B3D_89DB_5726D2B68425__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// UserRegDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CUserRegDlg dialog

class CUserRegDlg : public CDialog
{
// Construction
public:
	int t;
	CUserRegDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CUserRegDlg)
	enum { IDD = IDD_DIALOG_userReg };
	CString	m_id;
	CString	m_name;
	CString	m_pwd;
	CString	m_money;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CUserRegDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CUserRegDlg)
	afx_msg void OnBUTTONreg();
	afx_msg void OnBUTTONcancel();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_USERREGDLG_H__6BF4E1C8_36AD_4B3D_89DB_5726D2B68425__INCLUDED_)
