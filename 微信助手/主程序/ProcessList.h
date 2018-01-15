#pragma once
#include "afxcmn.h"

#include <TlHelp32.h>

extern DWORD gPid;

// CProcessList �Ի���

class CProcessList : public CDialogEx
{
	DECLARE_DYNAMIC(CProcessList)

public:
	CProcessList(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CProcessList();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_PROCESS };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	CListCtrl m_Process;
	void GetListProcess();
	afx_msg void OnBnClickedOk();
};
