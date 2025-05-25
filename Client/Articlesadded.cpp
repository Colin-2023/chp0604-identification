// Articlesadded.cpp : implementation file
//
/**************************************************************************************
Copyright (2010) Beijing Forest Studio, Lab of Information Security & Countermeasures  
Technology, Beijing Institute of Technology (BIT-ISCLab-BFS)
版权所有(2010) 北京理工大学信息安全与对抗技术实验室森林工作室(BIT-ISCLab-BFS)
**************************************************************************************/

#include "stdafx.h"
#include "Client.h"
#include "Articlesadded.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CArticlesadded dialog


CArticlesadded::CArticlesadded(CWnd* pParent /*=NULL*/)
	: CDialog(CArticlesadded::IDD, pParent)
{
	//{{AFX_DATA_INIT(CArticlesadded)
	//}}AFX_DATA_INIT
}


void CArticlesadded::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CArticlesadded)
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CArticlesadded, CDialog)
	//{{AFX_MSG_MAP(CArticlesadded)
	ON_COMMAND(ID_AddArtis, OnAddArtis)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CArticlesadded message handlers

void CArticlesadded::OnAddArtis() 
{
	// TODO: Add your command handler code here
	
}
