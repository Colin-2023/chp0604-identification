// Netset.cpp : implementation file
//
/**************************************************************************************
Copyright (2010) Beijing Forest Studio, Lab of Information Security & Countermeasures  
Technology, Beijing Institute of Technology (BIT-ISCLab-BFS)
��Ȩ����(2010) ��������ѧ��Ϣ��ȫ��Կ�����ʵ����ɭ�ֹ�����(BIT-ISCLab-BFS)
**************************************************************************************/

#include "stdafx.h"
#include "Client.h"
#include "Netset.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CNetset dialog


CNetset::CNetset(CWnd* pParent /*=NULL*/)
	: CDialog(CNetset::IDD, pParent)
{
	//{{AFX_DATA_INIT(CNetset)
	//}}AFX_DATA_INIT
}


void CNetset::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CNetset)
	DDX_Control(pDX, IDC_IPADDRESS1, m_IpAddress);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CNetset, CDialog)
	//{{AFX_MSG_MAP(CNetset)
	ON_BN_CLICKED(IDOK1, OnOk1)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CNetset message handlers

void CNetset::OnOk1() 
{
	BYTE add1,   add2,   add3,   add4;
    m_IpAddress.GetAddress(add1,   add2,   add3,   add4);
	ip.Format("%d.%d.%d.%d",   add1,   add2,   add3,   add4);
	/*Format('this is %d %d',[12,13]); 
    ���е�һ��%d��������0���ڶ���%d��1�������ַ���ʾ��ʱ�������� this is 12 13 */
	UpdateData(FALSE);

	CDialog::OnOK();	
}

BOOL CNetset::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	m_IpAddress.SetAddress(127,0,0,1);
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
