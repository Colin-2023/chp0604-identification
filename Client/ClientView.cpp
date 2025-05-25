// ClientView.cpp : implementation of the CClientView class
//
/**************************************************************************************
Copyright (2010) Beijing Forest Studio, Lab of Information Security & Countermeasures  
Technology, Beijing Institute of Technology (BIT-ISCLab-BFS)
版权所有(2010) 北京理工大学信息安全与对抗技术实验室森林工作室(BIT-ISCLab-BFS)
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
 	m_IP = "127.0.0.1";	// 默认IP
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
	while(m_articles.DeleteColumn(0)){}	//删除所有的项，包括表头
	m_articles.SetExtendedStyle(LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES|LVS_EX_TRACKSELECT);
	//选择整行、绘制表格、自动换行

	m_articles.InsertColumn(0,_T("编号"),LVCFMT_CENTER,70,-1);
	m_articles.InsertColumn(1,_T("文章名"),LVCFMT_CENTER,230,-1);
	m_articles.InsertColumn(2,_T("作者"),LVCFMT_CENTER,115,-1);
} 
void CClientView::SetInfoForm()
{
	while(m_infos.DeleteColumn(0)){}	//删除所有的项，包括表头
	m_infos.SetExtendedStyle(LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES|LVS_EX_TRACKSELECT);
	//选择整行、绘制表格、自动换行

	if (flag == 1)	// 普通用户
	{
		m_infos.InsertColumn(0,_T("编号"),LVCFMT_CENTER,70,-1);
		m_infos.InsertColumn(1,_T("用户名"),LVCFMT_CENTER,155,-1);
		m_infos.InsertColumn(2,_T("用户性别"),LVCFMT_CENTER,70,-1);
		m_infos.InsertColumn(3,_T("用户身份"),LVCFMT_CENTER,120,-1);
	}
	if (flag == 2)	// 管理员
	{
		m_infos.InsertColumn(0,_T("编号"),LVCFMT_CENTER,70,-1);
		m_infos.InsertColumn(1,_T("用户名"),LVCFMT_CENTER,110,-1);
		m_infos.InsertColumn(2,_T("用户性别"),LVCFMT_CENTER,70,-1);
		m_infos.InsertColumn(3,_T("用户身份"),LVCFMT_CENTER,80,-1);
		m_infos.InsertColumn(4,_T("用户密码"),LVCFMT_CENTER,80,-1);
	}
}



void CClientView::OnLogin() 
{
	char buf[1000];			// 放接收到的数据
	flag = 0;
 	int port = 4000;		// 将端口号由CString转为int
	
	CLogin dlg;
	if (dlg.DoModal() != IDOK)
	{
		return;
	}
	else
	{
		if(dlg.m_username.IsEmpty())
		{
			MessageBox(" 请先输入用户名!","用户登录",MB_OK|MB_ICONEXCLAMATION);
			OnLogin();
		}
		if (dlg.m_password.IsEmpty())
		{
			MessageBox(" 请先输入密码!","用户登录",MB_OK|MB_ICONEXCLAMATION);
			OnLogin();
		}
		else
		{
			// 建立连接
			WSADATA wsaData;
			if(WSAStartup(WINSOCK_VERSION, &wsaData))
				OnLogin();

			//创建套接字
			m_sock_client = socket(AF_INET,SOCK_STREAM,0);
			if(m_sock_client == SOCKET_ERROR)
			{
				MessageBox("套接字建立错误!\n");
				WSACleanup();
				OnLogin();
			}

			// 连接服务器
			sockaddr_in ServerAddr;
			ServerAddr.sin_family = AF_INET;
//			ServerAddr.sin_addr.s_addr = inet_addr("127.0.0.1");
			HOSTENT *hp=gethostbyname(m_IP);
			memcpy((char*)&ServerAddr.sin_addr, (char*)hp->h_addr, hp->h_length);
			ServerAddr.sin_port=htons(port);
			if(connect(m_sock_client,(struct sockaddr*)&ServerAddr,sizeof(ServerAddr))==SOCKET_ERROR)
			{
				MessageBox("不能连接服务器!\n请稍候再登录!");
				closesocket(m_sock_client);
				WSACleanup();
				OnLogin();
			 }
			
			// 发送用户名	
			int rval = send(m_sock_client,dlg.m_username,dlg.m_username.GetLength(),0);
			if(rval<=0)
			{
				if(m_sock_client)
					closesocket(m_sock_client);
				OnLogin();
			}

			// 接收数据
			rval = recv(m_sock_client, buf, sizeof(buf),0);
			if (rval <=0)
			{
				if(m_sock_client)
					closesocket(m_sock_client);
				OnLogin();
			}
			buf[rval] = '\0';

			// 判断是否已经登录
			if (strcmp(buf, "OK") == 0)	// 验证用户名
			{
				rval = send(m_sock_client,dlg.m_password,dlg.m_password.GetLength(),0);

				memset(buf, 0, 100 * sizeof(char));
				rval = recv(m_sock_client, buf, sizeof(buf),0);
				buf[rval] = NULL;

				// 判断密码是否正确
				if (strcmp(buf, "管理员") == 0)
				{
					MessageBox("登录成功!");
					flag = 2;	// 管理员
				}
				else 
				{
					if (strcmp(buf, "普通用户") == 0)
					{
						MessageBox("登录成功!");
						flag = 1;	// 普通用户
					}
					else
					{
						MessageBox("登录失败!");
						flag = 0;	// 游客
					}
				}
			}
			else
			{
				MessageBox("登录失败!");
				flag = 0;	// 游客
			}
			GetWelcomePage();	// 获取登录界面
		}
	}	
}

void CClientView::GetWelcomePage()
{
	/*************************接收用户登录后的数据*************************/
	char buf[1000];
	// 用户为登录失败，游客
	if (flag == 0)
	{
		// 设置用户文章列表
		SetArticleForm();
		SetInfoForm();
		int nItem;
		int i = 0;
		int j;
		char str[25];

		m_articles.DeleteAllItems();  // 删除列表中所有列的信息
 		memset(buf, 0, 100 * sizeof(char));
 		int rval = recv(m_sock_client, buf, sizeof(buf), 0);
 		buf[rval] = '\0';
 		while (strcmp(buf, "用户文章列表发送完毕") != 0)
 		{
			itoa(i, str, 10);	// 按十进制转换
			nItem = m_articles.InsertItem(i, str);   // 向列表中插入一行,并设置编号为标签项
			// 显示一行的信息
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

		// 设置用户权限
		AfxGetMainWnd()->SetWindowText( "游客");
	}

	// 用户为登录成功，管理员
	if (flag == 2)
	{
		// 设置用户文章列表
		SetArticleForm();
		int nItem;
		int i = 0;
		int j;
		char str[50];

		m_articles.DeleteAllItems();  // 删除列表中所有列的信息
 		memset(buf, 0, 100 * sizeof(char));
 		int rval = recv(m_sock_client, buf, sizeof(buf), 0);
 		buf[rval] = '\0';
 		while (strcmp(buf, "用户文章列表发送完毕") != 0)
 		{
			itoa(i, str, 10);	// 按十进制转换,将int转换成char
			nItem = m_articles.InsertItem(i, str);   // 向列表中插入一行,并设置编号为标签项
			// 显示一行的信息
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

		// 用户信息列表
		SetInfoForm();
		i = 0;
		m_infos.DeleteAllItems();	// 删除列表中所有列的信息
 		memset(buf, 0, 100 * sizeof(char));
 		rval = recv(m_sock_client, buf, sizeof(buf), 0);
 		buf[rval] = '\0';
 		while (strcmp(buf, "用户信息列表发送完毕") != 0)
 		{
			itoa(i, str, 10);	// 按十进制转换
			nItem = m_infos.InsertItem(i, str);   // 向列表中插入一行,并设置编号为标签项
			// 显示一行的信息
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

		// 设置用户权限
		AfxGetMainWnd()->SetWindowText( "管理员");
	}

	// 用户为登录成功，普通用户
	if (flag == 1)
	{
		// 设置用户文章列表
		SetArticleForm();
		int nItem;
		int i = 0;
		int j;
		char str[50];

		m_articles.DeleteAllItems();  // 删除列表中所有列的信息
 		memset(buf, 0, 100 * sizeof(char));
 		int rval = recv(m_sock_client, buf, sizeof(buf), 0);
 		buf[rval] = '\0';
 		while (strcmp(buf, "用户文章列表发送完毕") != 0)
 		{
			itoa(i, str, 10);	// 按十进制转换，将int转换成char
			nItem = m_articles.InsertItem(i, str);   // 向列表中插入一行，并设置编号为标签项
			// 显示一行的信息
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

		// 用户信息列表
		SetInfoForm();
		i = 0;
		m_infos.DeleteAllItems();	// 删除列表中所有列的信息
 		memset(buf, 0, 100 * sizeof(char));
 		rval = recv(m_sock_client, buf, sizeof(buf), 0);
 		buf[rval] = '\0';
 		while (strcmp(buf, "用户信息列表发送完毕") != 0)
 		{
			itoa(i, str, 10);	// 按十进制转换
			nItem = m_infos.InsertItem(i, str);   // 向列表中插入一行,并设置编号为标签项
			// 显示一行的信息
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

		// 设置用户身份
		AfxGetMainWnd()->SetWindowText( "普通用户");
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
