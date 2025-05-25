#if !defined(AFX_ARTICLESADDED_H__C0B6B8C8_922E_49CF_90FC_2504E2EF2F0C__INCLUDED_)
#define AFX_ARTICLESADDED_H__C0B6B8C8_922E_49CF_90FC_2504E2EF2F0C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Articlesadded.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CArticlesadded dialog

class CArticlesadded : public CDialog
{
// Construction
public:
	CArticlesadded(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CArticlesadded)
	enum { IDD = IDD_ARTICLE_ADDED_DIALOG };
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CArticlesadded)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CArticlesadded)
	afx_msg void OnAddArtis();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ARTICLESADDED_H__C0B6B8C8_922E_49CF_90FC_2504E2EF2F0C__INCLUDED_)
