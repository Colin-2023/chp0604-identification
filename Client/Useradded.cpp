// Useradded.cpp : implementation file
//
/**************************************************************************************
Copyright (2010) Beijing Forest Studio, Lab of Information Security & Countermeasures  
Technology, Beijing Institute of Technology (BIT-ISCLab-BFS)
版权所有(2010) 北京理工大学信息安全与对抗技术实验室森林工作室(BIT-ISCLab-BFS)
**************************************************************************************/

#include "stdafx.h"
#include "Client.h"
#include "Useradded.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CUseradded dialog


CUseradded::CUseradded(CWnd* pParent /*=NULL*/)
	: CDialog(CUseradded::IDD, pParent)
{
	//{{AFX_DATA_INIT(CUseradded)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CUseradded::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CUseradded)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CUseradded, CDialog)
	//{{AFX_MSG_MAP(CUseradded)
	ON_COMMAND(ID_AddUsers, OnAddUsers)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CUseradded message handlers

void CUseradded::OnAddUsers() 
{
	// TODO: Add your command handler code here
	
}
