
// chineseSplitDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "chineseSplit.h"
#include "chineseSplitDlg.h"
#include "afxdialogex.h"
#include <io.h> 
#include <fcntl.h>
#include "Split.h"
#define  _CRT_SECURE_NO_WARNINGS

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// �Ի�������
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CchineseSplitDlg �Ի���



CchineseSplitDlg::CchineseSplitDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CchineseSplitDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CchineseSplitDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CchineseSplitDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BTN_SPLIT, &CchineseSplitDlg::OnBnClickedBtnSplit)
	ON_BN_CLICKED(IDC_BTN_CLEAR, &CchineseSplitDlg::OnBnClickedBtnClear)
	ON_EN_SETFOCUS(IDC_EDT_ORIGIN, &CchineseSplitDlg::OnEnSetfocusEdtOrigin)
	ON_EN_SETFOCUS(IDC_EDT_ADMIT, &CchineseSplitDlg::OnEnSetfocusEdtAdmit)
END_MESSAGE_MAP()


// CchineseSplitDlg ��Ϣ�������

BOOL CchineseSplitDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// ���ô˶Ի����ͼ�ꡣ  ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO:  �ڴ���Ӷ���ĳ�ʼ������
#ifdef _DEBUG
	AllocConsole();
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	int hCrt = _open_osfhandle((long)handle, _O_TEXT);
	FILE * hf = _fdopen(hCrt, "w");
	*stdout = *hf;
#endif
	OnBnClickedBtnClear();
	m_database = new sqlQuery();
	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

void CchineseSplitDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ  ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CchineseSplitDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CchineseSplitDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CchineseSplitDlg::OnBnClickedBtnSplit()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	CString str_origin;
	((CEdit*)GetDlgItem(IDC_EDT_ORIGIN))->GetWindowTextW(str_origin);
	CT2CA pszName(str_origin);
	std::string m_NameStd(pszName);
	CString str_target = matching(m_NameStd);
	((CEdit*)GetDlgItem(IDC_EDT_ADMIT))->SetWindowTextW(str_target);
}


void CchineseSplitDlg::OnBnClickedBtnClear()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	((CEdit*)GetDlgItem(IDC_EDT_ORIGIN))->SetWindowTextW(L"������Ҫ���ֵ����");
	((CEdit*)GetDlgItem(IDC_EDT_ADMIT))->SetWindowTextW(L"���ֺ�Ľ��");
}


void CchineseSplitDlg::OnEnSetfocusEdtOrigin()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	((CEdit*)GetDlgItem(IDC_EDT_ORIGIN))->SetWindowTextW(L"");
}


void CchineseSplitDlg::OnEnSetfocusEdtAdmit()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	((CEdit*)GetDlgItem(IDC_EDT_ADMIT))->SetWindowTextW(L"");
}



CString CchineseSplitDlg::matching(string str_origin)
{
	cout << str_origin << endl;
	Split sp(str_origin);
	string res = sp.getResult();
	return CString(res.c_str());
}
