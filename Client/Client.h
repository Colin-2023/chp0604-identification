// Client.h : main header file for the CLIENT application
//

#if !defined(AFX_CLIENT_H__4CE4BFAA_CC17_40E6_8975_554018BDB911__INCLUDED_)
#define AFX_CLIENT_H__4CE4BFAA_CC17_40E6_8975_554018BDB911__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CClientApp:
// See Client.cpp for the implementation of this class
//

class CClientApp : public CWinApp
{
public:
	CClientApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CClientApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation
	//{{AFX_MSG(CClientApp)
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CLIENT_H__4CE4BFAA_CC17_40E6_8975_554018BDB911__INCLUDED_)
