#if !defined(AFX_USERADDED_H__E8EED39C_9163_44A3_912C_A00779DDE762__INCLUDED_)
#define AFX_USERADDED_H__E8EED39C_9163_44A3_912C_A00779DDE762__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Useradded.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CUseradded dialog

class CUseradded : public CDialog
{
// Construction
public:
	CUseradded(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CUseradded)
	enum { IDD = IDD_USER_ADDED_DIALOG };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CUseradded)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CUseradded)
	afx_msg void OnAddUsers();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_USERADDED_H__E8EED39C_9163_44A3_912C_A00779DDE762__INCLUDED_)
