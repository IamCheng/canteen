// ²ÍÌüDlg.h : header file
//

#if !defined(AFX_DLG_H__778D2188_C3F9_49CF_8C22_1E87D4755F57__INCLUDED_)
#define AFX_DLG_H__778D2188_C3F9_49CF_8C22_1E87D4755F57__INCLUDED_

#include "UserRegDlg.h"	// Added by ClassView
#include "SrchDlg.h"	// Added by ClassView
#include "TabSheet.h"	// Added by ClassView
#include "workerDlg.h"	// Added by ClassView
#include "foodDlg.h"	// Added by ClassView
#include "CTRegDlg.h"
#include "orderDlg.h"	// Added by ClassView


#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CMyDlg dialog

class CMyDlg : public CDialog
{
// Construction
public:
	CorderDlg order;
	CUserRegDlg user;
	CCTRegDlg reg;
//	CCTRegDlg CTreg();
	CSrchDlg srch;
	CfoodDlg food_dlg;
	CworkerDlg worker_dlg;
//	CTabSheet m_tab;
	CMyDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CMyDlg)
	enum { IDD = IDD_MY_DIALOG };
	CTabSheet	m_tab;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMyDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CMyDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLG_H__778D2188_C3F9_49CF_8C22_1E87D4755F57__INCLUDED_)
