#if !defined(AFX_NETSET_H__2907D784_13A3_4FD0_8090_639AC9A56A11__INCLUDED_)
#define AFX_NETSET_H__2907D784_13A3_4FD0_8090_639AC9A56A11__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Netset.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CNetset dialog

class CNetset : public CDialog
{
// Construction
public:
	CNetset(CWnd* pParent = NULL);   // standard constructor

	CString ip;
// Dialog Data
	//{{AFX_DATA(CNetset)
	enum { IDD = IDD_NETSET_DIALOG };
	CIPAddressCtrl	m_IpAddress;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CNetset)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CNetset)
	afx_msg void OnOk1();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_NETSET_H__2907D784_13A3_4FD0_8090_639AC9A56A11__INCLUDED_)
