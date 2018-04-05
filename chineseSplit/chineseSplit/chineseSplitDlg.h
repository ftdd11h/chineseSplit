
// chineseSplitDlg.h : ͷ�ļ�
//

#pragma once
#include "sqlQuery.h"

// CchineseSplitDlg �Ի���
class CchineseSplitDlg : public CDialogEx
{
// ����
public:
	CchineseSplitDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_CHINESESPLIT_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()

	sqlQuery* m_database;
public:
	afx_msg void OnBnClickedBtnSplit();
	afx_msg void OnBnClickedBtnClear();
	afx_msg void OnEnSetfocusEdtOrigin();
	afx_msg void OnEnSetfocusEdtAdmit();
	CString matching(string str_origin);
};
