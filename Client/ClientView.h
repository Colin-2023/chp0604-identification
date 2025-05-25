// ClientView.h : interface of the CClientView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_CLIENTVIEW_H__0A33FE38_1836_4475_B4C1_8ABFD30F75FC__INCLUDED_)
#define AFX_CLIENTVIEW_H__0A33FE38_1836_4475_B4C1_8ABFD30F75FC__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include   "winsock.h " 
#pragma   comment(lib, "Ws2_32.lib ")
#define WINSOCK_VERSION 0x0001
class CClientView : public CFormView
{
protected: // create from serialization only
	CClientView();
	DECLARE_DYNCREATE(CClientView)

public:
	//{{AFX_DATA(CClientView)
	enum { IDD = IDD_CLIENT_FORM };
	CListCtrl	m_infos;
	CListCtrl	m_articles;
	CString m_title;
	SOCKET m_sock_client;	// 套接字m_sock_client
	//}}AFX_DATA

// Attributes
public:
	CClientDoc* GetDocument();

// Operations
public:
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CClientView)
	public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual void OnInitialUpdate(); // called first time after construct

	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CClientView();
	void SetArticleForm();	// 设置用户文章列表格式
	void SetInfoForm();		// 设置用户信息列表格式
	void GetWelcomePage();	// 获取下载界面
	int flag;			// 2：管理员，1：普通用户，0：游客
	char *m_IP;

#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CClientView)
	afx_msg void OnLogin();
	afx_msg void OnNetset();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in ClientView.cpp
inline CClientDoc* CClientView::GetDocument()
   { return (CClientDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CLIENTVIEW_H__0A33FE38_1836_4475_B4C1_8ABFD30F75FC__INCLUDED_)
