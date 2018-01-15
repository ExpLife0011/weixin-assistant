
// MFCWebDemoDlg.h : ͷ�ļ�
//

#pragma once
#include "afxwin.h"
#include "explorer1.h"


// CMFCWebDemoDlg �Ի���
class CMFCWebDemoDlg : public CDialogEx
{
// ����
public:
	CMFCWebDemoDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MFCWEBDEMO_DIALOG };
#endif

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
public:
	CEdit m_EditAddress;
	CExplorer1 m_WebIE;
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
};
