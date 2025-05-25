// ClientView.cpp : implementation of the CClientView class
//
/**************************************************************************************
Copyright (2010) Beijing Forest Studio, Lab of Information Security & Countermeasures  
Technology, Beijing Institute of Technology (BIT-ISCLab-BFS)
��Ȩ����(2010) ��������ѧ��Ϣ��ȫ��Կ�����ʵ����ɭ�ֹ�����(BIT-ISCLab-BFS)
**************************************************************************************/

#include "stdafx.h"
#include "Client.h"

#include "ClientDoc.h"
#include "ClientView.h"
#include "Netset.h"
#include "Login.h"
#include "Articlesadded.h"
#include "Useradded.h"

#include "Afxsock.h"
#include "winsock.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define WINSOCK_VERSION 0x0001
/////////////////////////////////////////////////////////////////////////////
// CClientView

IMPLEMENT_DYNCREATE(CClientView, CFormView)

BEGIN_MESSAGE_MAP(CClientView, CFormView)
	//{{AFX_MSG_MAP(CClientView)
	ON_COMMAND(ID_Login, OnLogin)
	ON_COMMAND(ID_Netset, OnNetset)
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CFormView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CFormView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CFormView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CClientView construction/destruction

CClientView::CClientView()
	: CFormView(CClientView::IDD)
{
	//{{AFX_DATA_INIT(CClientView)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
 	m_IP = "127.0.0.1";	// Ĭ��IP
}

CClientView::~CClientView()
{
}

void CClientView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CClientView)
	DDX_Control(pDX, IDC_LIST_Infos, m_infos);
	DDX_Control(pDX, IDC_LIST_Articles, m_articles);
	//}}AFX_DATA_MAP
}

BOOL CClientView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CFormView::PreCreateWindow(cs);
}

void CClientView::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();
	GetParentFrame()->RecalcLayout();
	ResizeParentToFit();

}


/////////////////////////////////////////////////////////////////////////////
// CClientView diagnostics

#ifdef _DEBUG
void CClientView::AssertValid() const
{
	CFormView::AssertValid();
}

void CClientView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}

CClientDoc* CClientView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CClientDoc)));
	return (CClientDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CClientView message handlers
void CClientView::SetArticleForm()
{
	while(m_articles.DeleteColumn(0)){}	//ɾ�����е��������ͷ
	m_articles.SetExtendedStyle(LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES|LVS_EX_TRACKSELECT);
	//ѡ�����С����Ʊ���Զ�����

	m_articles.InsertColumn(0,_T("���"),LVCFMT_CENTER,70,-1);
	m_articles.InsertColumn(1,_T("������"),LVCFMT_CENTER,230,-1);
	m_articles.InsertColumn(2,_T("����"),LVCFMT_CENTER,115,-1);
} 
void CClientView::SetInfoForm()
{
	while(m_infos.DeleteColumn(0)){}	//ɾ�����е��������ͷ
	m_infos.SetExtendedStyle(LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES|LVS_EX_TRACKSELECT);
	//ѡ�����С����Ʊ���Զ�����

	if (flag == 1)	// ��ͨ�û�
	{
		m_infos.InsertColumn(0,_T("���"),LVCFMT_CENTER,70,-1);
		m_infos.InsertColumn(1,_T("�û���"),LVCFMT_CENTER,155,-1);
		m_infos.InsertColumn(2,_T("�û��Ա�"),LVCFMT_CENTER,70,-1);
		m_infos.InsertColumn(3,_T("�û����"),LVCFMT_CENTER,120,-1);
	}
	if (flag == 2)	// ����Ա
	{
		m_infos.InsertColumn(0,_T("���"),LVCFMT_CENTER,70,-1);
		m_infos.InsertColumn(1,_T("�û���"),LVCFMT_CENTER,110,-1);
		m_infos.InsertColumn(2,_T("�û��Ա�"),LVCFMT_CENTER,70,-1);
		m_infos.InsertColumn(3,_T("�û����"),LVCFMT_CENTER,80,-1);
		m_infos.InsertColumn(4,_T("�û�����"),LVCFMT_CENTER,80,-1);
	}
}



void CClientView::OnLogin() 
{
	char buf[1000];			// �Ž��յ�������
	flag = 0;
 	int port = 4000;		// ���˿ں���CStringתΪint
	
	CLogin dlg;
	if (dlg.DoModal() != IDOK)
	{
		return;
	}
	else
	{
		if(dlg.m_username.IsEmpty())
		{
			MessageBox(" ���������û���!","�û���¼",MB_OK|MB_ICONEXCLAMATION);
			OnLogin();
		}
		if (dlg.m_password.IsEmpty())
		{
			MessageBox(" ������������!","�û���¼",MB_OK|MB_ICONEXCLAMATION);
			OnLogin();
		}
		else
		{
			// ��������
			WSADATA wsaData;
			if(WSAStartup(WINSOCK_VERSION, &wsaData))
				OnLogin();

			//�����׽���
			m_sock_client = socket(AF_INET,SOCK_STREAM,0);
			if(m_sock_client == SOCKET_ERROR)
			{
				MessageBox("�׽��ֽ�������!\n");
				WSACleanup();
				OnLogin();
			}

			// ���ӷ�����
			sockaddr_in ServerAddr;
			ServerAddr.sin_family = AF_INET;
//			ServerAddr.sin_addr.s_addr = inet_addr("127.0.0.1");
			HOSTENT *hp=gethostbyname(m_IP);
			memcpy((char*)&ServerAddr.sin_addr, (char*)hp->h_addr, hp->h_length);
			ServerAddr.sin_port=htons(port);
			if(connect(m_sock_client,(struct sockaddr*)&ServerAddr,sizeof(ServerAddr))==SOCKET_ERROR)
			{
				MessageBox("�������ӷ�����!\n���Ժ��ٵ�¼!");
				closesocket(m_sock_client);
				WSACleanup();
				OnLogin();
			 }
			
			// �����û���	
			int rval = send(m_sock_client,dlg.m_username,dlg.m_username.GetLength(),0);
			if(rval<=0)
			{
				if(m_sock_client)
					closesocket(m_sock_client);
				OnLogin();
			}

			// ��������
			rval = recv(m_sock_client, buf, sizeof(buf),0);
			if (rval <=0)
			{
				if(m_sock_client)
					closesocket(m_sock_client);
				OnLogin();
			}
			buf[rval] = '\0';

			// �ж��Ƿ��Ѿ���¼
			if (strcmp(buf, "OK") == 0)	// ��֤�û���
			{
				rval = send(m_sock_client,dlg.m_password,dlg.m_password.GetLength(),0);

				memset(buf, 0, 100 * sizeof(char));
				rval = recv(m_sock_client, buf, sizeof(buf),0);
				buf[rval] = NULL;

				// �ж������Ƿ���ȷ
				if (strcmp(buf, "����Ա") == 0)
				{
					MessageBox("��¼�ɹ�!");
					flag = 2;	// ����Ա
				}
				else 
				{
					if (strcmp(buf, "��ͨ�û�") == 0)
					{
						MessageBox("��¼�ɹ�!");
						flag = 1;	// ��ͨ�û�
					}
					else
					{
						MessageBox("��¼ʧ��!");
						flag = 0;	// �ο�
					}
				}
			}
			else
			{
				MessageBox("��¼ʧ��!");
				flag = 0;	// �ο�
			}
			GetWelcomePage();	// ��ȡ��¼����
		}
	}	
}

void CClientView::GetWelcomePage()
{
	/*************************�����û���¼�������*************************/
	char buf[1000];
	// �û�Ϊ��¼ʧ�ܣ��ο�
	if (flag == 0)
	{
		// �����û������б�
		SetArticleForm();
		SetInfoForm();
		int nItem;
		int i = 0;
		int j;
		char str[25];

		m_articles.DeleteAllItems();  // ɾ���б��������е���Ϣ
 		memset(buf, 0, 100 * sizeof(char));
 		int rval = recv(m_sock_client, buf, sizeof(buf), 0);
 		buf[rval] = '\0';
 		while (strcmp(buf, "�û������б������") != 0)
 		{
			itoa(i, str, 10);	// ��ʮ����ת��
			nItem = m_articles.InsertItem(i, str);   // ���б��в���һ��,�����ñ��Ϊ��ǩ��
			// ��ʾһ�е���Ϣ
			for (j=1;j<3;j++)
			{
				m_articles.SetItemText(nItem, j, buf);
				send(m_sock_client, "OK", strlen("OK"), 0);
				memset(buf, 0, 100 * sizeof(char));
				rval = recv(m_sock_client, buf, sizeof(buf), 0);
				buf[rval] = '\0';
			}
			i++;	
 		}

		// �����û�Ȩ��
		AfxGetMainWnd()->SetWindowText( "�ο�");
	}

	// �û�Ϊ��¼�ɹ�������Ա
	if (flag == 2)
	{
		// �����û������б�
		SetArticleForm();
		int nItem;
		int i = 0;
		int j;
		char str[50];

		m_articles.DeleteAllItems();  // ɾ���б��������е���Ϣ
 		memset(buf, 0, 100 * sizeof(char));
 		int rval = recv(m_sock_client, buf, sizeof(buf), 0);
 		buf[rval] = '\0';
 		while (strcmp(buf, "�û������б������") != 0)
 		{
			itoa(i, str, 10);	// ��ʮ����ת��,��intת����char
			nItem = m_articles.InsertItem(i, str);   // ���б��в���һ��,�����ñ��Ϊ��ǩ��
			// ��ʾһ�е���Ϣ
			for (j=1;j<3;j++)
			{
				m_articles.SetItemText(nItem, j, buf);
				send(m_sock_client, "OK", strlen("OK"), 0);
				memset(buf, 0, 100 * sizeof(char));
				rval = recv(m_sock_client, buf, sizeof(buf), 0);
				buf[rval] = '\0';
			}
			i++;	
 		}

		// �û���Ϣ�б�
		SetInfoForm();
		i = 0;
		m_infos.DeleteAllItems();	// ɾ���б��������е���Ϣ
 		memset(buf, 0, 100 * sizeof(char));
 		rval = recv(m_sock_client, buf, sizeof(buf), 0);
 		buf[rval] = '\0';
 		while (strcmp(buf, "�û���Ϣ�б������") != 0)
 		{
			itoa(i, str, 10);	// ��ʮ����ת��
			nItem = m_infos.InsertItem(i, str);   // ���б��в���һ��,�����ñ��Ϊ��ǩ��
			// ��ʾһ�е���Ϣ
			for (j=1;j<5;j++)
			{
				m_infos.SetItemText(nItem, j, buf);
				send(m_sock_client, "OK", strlen("OK"), 0);
				memset(buf, 0, 100 * sizeof(char));
				rval = recv(m_sock_client, buf, sizeof(buf), 0);
				buf[rval] = '\0';
			}
			i++;	
 		}

		// �����û�Ȩ��
		AfxGetMainWnd()->SetWindowText( "����Ա");
	}

	// �û�Ϊ��¼�ɹ�����ͨ�û�
	if (flag == 1)
	{
		// �����û������б�
		SetArticleForm();
		int nItem;
		int i = 0;
		int j;
		char str[50];

		m_articles.DeleteAllItems();  // ɾ���б��������е���Ϣ
 		memset(buf, 0, 100 * sizeof(char));
 		int rval = recv(m_sock_client, buf, sizeof(buf), 0);
 		buf[rval] = '\0';
 		while (strcmp(buf, "�û������б������") != 0)
 		{
			itoa(i, str, 10);	// ��ʮ����ת������intת����char
			nItem = m_articles.InsertItem(i, str);   // ���б��в���һ�У������ñ��Ϊ��ǩ��
			// ��ʾһ�е���Ϣ
			for (j=1;j<3;j++)
			{
				m_articles.SetItemText(nItem, j, buf);
				send(m_sock_client, "OK", strlen("OK"), 0);
				memset(buf, 0, 100 * sizeof(char));
				rval = recv(m_sock_client, buf, sizeof(buf), 0);
				buf[rval] = '\0';
			}
			i++;	
 		}

		// �û���Ϣ�б�
		SetInfoForm();
		i = 0;
		m_infos.DeleteAllItems();	// ɾ���б��������е���Ϣ
 		memset(buf, 0, 100 * sizeof(char));
 		rval = recv(m_sock_client, buf, sizeof(buf), 0);
 		buf[rval] = '\0';
 		while (strcmp(buf, "�û���Ϣ�б������") != 0)
 		{
			itoa(i, str, 10);	// ��ʮ����ת��
			nItem = m_infos.InsertItem(i, str);   // ���б��в���һ��,�����ñ��Ϊ��ǩ��
			// ��ʾһ�е���Ϣ
			for (j=1;j<4;j++)
			{
				m_infos.SetItemText(nItem, j, buf);
				send(m_sock_client, "OK", strlen("OK"), 0);
				memset(buf, 0, 100 * sizeof(char));
				rval = recv(m_sock_client, buf, sizeof(buf), 0);
				buf[rval] = '\0';
			}
			i++;	
 		}

		// �����û����
		AfxGetMainWnd()->SetWindowText( "��ͨ�û�");
	}
}

void CClientView::OnNetset()
{
	CNetset dlg;
	if (dlg.DoModal() != IDOK)
	{
		return;
	}
	else
	{
		m_IP = dlg.ip.GetBuffer(2);
	}
}
