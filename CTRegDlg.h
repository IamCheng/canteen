#if !defined(AFX_CTREGDLG_H__70E413CB_3094_40F4_B8D9_2659EE2303F2__INCLUDED_)
#define AFX_CTREGDLG_H__70E413CB_3094_40F4_B8D9_2659EE2303F2__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// CTRegDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CCTRegDlg dialog

class CCTRegDlg : public CDialog
{
// Construction
public:
	CCTRegDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CCTRegDlg)
	enum { IDD = IDD_DIALOG_CTReg };
	CString	m_addr;
	CString	m_id;
	CString	m_name;
	CString	m_num;
	CString	m_time;
	CString	m_boss;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCTRegDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CCTRegDlg)
	afx_msg void OnBUTTONreg();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CTREGDLG_H__70E413CB_3094_40F4_B8D9_2659EE2303F2__INCLUDED_)
