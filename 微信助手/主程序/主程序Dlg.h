
// ������Dlg.h : ͷ�ļ�
//

#pragma once
#include "afxcmn.h"
#include "afxwin.h"


// C������Dlg �Ի���
class C������Dlg : public CDialogEx
{
// ����
public:
	C������Dlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MY_DIALOG };
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
	CListCtrl m_List;
	CString m_Hex;
	CString m_String;
	afx_msg void OnBnClickedOk();
	BOOL MyPrivilegeValue();
	afx_msg void OnBnClickedBtnTiquan();

	LRESULT GetThreadIdMsg(WPARAM wparam, LPARAM lparam);
	afx_msg void OnBnClickedBtnPause();
private:
	DWORD m_ThreadId;
public:
	afx_msg void OnBnClickedBtnRecontinue();
	afx_msg void OnBnClickedCancel();
	afx_msg void OnBnClickedBtnFreedll();
private:
	LRESULT MyFreeLibrary(WPARAM wparam, LPARAM lparam);
	LRESULT MyFreeLibrarySuccess(WPARAM wparam, LPARAM lparam);
	LRESULT MyFreeLibraryFailed(WPARAM wparam, LPARAM lparam);
	BOOL FreeMyDll(HMODULE hMod);
public:
	afx_msg BOOL OnCopyData(CWnd* pWnd, COPYDATASTRUCT* pCopyDataStruct);
	// ����
	CEdit m_Param;
	afx_msg void OnBnClickedBtnMemText();
	afx_msg void OnBnClickedBtnTest();
};
