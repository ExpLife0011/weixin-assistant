// ProcessList.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "������.h"
#include "ProcessList.h"
#include "afxdialogex.h"

// ȫ�ֱ���
DWORD gPid = 0;

// CProcessList �Ի���

IMPLEMENT_DYNAMIC(CProcessList, CDialogEx)

CProcessList::CProcessList(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DIALOG_PROCESS, pParent)
{

}

CProcessList::~CProcessList()
{
}

void CProcessList::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_PROCESSS, m_Process);
}


BEGIN_MESSAGE_MAP(CProcessList, CDialogEx)
	ON_BN_CLICKED(IDOK, &CProcessList::OnBnClickedOk)
END_MESSAGE_MAP()


// CProcessList ��Ϣ�������


BOOL CProcessList::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	m_Process.SetExtendedStyle(LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT);
	m_Process.InsertColumn(0, TEXT("������"), 0, 220);
	m_Process.InsertColumn(1, TEXT("PID"), 0, 100);

	GetListProcess();

	return TRUE;  // return TRUE unless you set the focus to a control
				  // �쳣: OCX ����ҳӦ���� FALSE
}

void CProcessList::GetListProcess()
{
	HANDLE hPro = CreateToolhelp32Snapshot(TH32CS_SNAPALL, 0);

	if (INVALID_HANDLE_VALUE != hPro) {

		PROCESSENTRY32 pro32 = { 0 };
		pro32.dwSize = sizeof(PROCESSENTRY32);

		BOOL bRet = Process32First(hPro, &pro32);

		while (bRet) {

			int idx = m_Process.GetItemCount();
			m_Process.InsertItem(idx, pro32.szExeFile);
			CString tmpstr;
			tmpstr.Format(TEXT("%d"), pro32.th32ProcessID);
			m_Process.SetItemText(idx, 1, tmpstr);
			//����PID
			m_Process.SetItemData(idx, pro32.th32ProcessID);
			bRet = Process32Next(hPro, &pro32);
		}

		CloseHandle(hPro);
	}
}

void CProcessList::OnBnClickedOk()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	//CDialogEx::OnOK();

	int idx = m_Process.GetSelectionMark();
	if (0 > idx) {
		
		AfxMessageBox(TEXT("��ѡȡ����"));
		return;
	}

	DWORD pid = m_Process.GetItemData(idx);
	if ((0 == pid) || (4 == pid)) {
		AfxMessageBox(TEXT("����ѡȡϵͳ����"));
		return;
	}

	HANDLE hPro = OpenProcess(PROCESS_ALL_ACCESS, FALSE, pid);
	if (NULL == hPro) {

		CString str;
		str.Format(TEXT("%d"), GetLastError());
		AfxMessageBox(str);
	}
	else {

		PVOID pbuf = VirtualAllocEx(hPro, NULL, MAX_PATH, MEM_COMMIT, PAGE_READWRITE);
		if (pbuf) {

			TCHAR mFilePath[MAX_PATH] = { 0 };
			GetCurrentDirectory(MAX_PATH, mFilePath);
			lstrcat(mFilePath, TEXT("\\΢������.dll"));
			DWORD bWriteSize = 0;
			//AfxMessageBox(mFilePath);
			BOOL bRet = WriteProcessMemory(hPro, pbuf, mFilePath, MAX_PATH, &bWriteSize);
			if (bRet) {

				PVOID pLoad = GetProcAddress(GetModuleHandle(TEXT("kernel32.dll")), "LoadLibraryW");
				if (pLoad) {

					HANDLE hRemote = CreateRemoteThread(
						hPro, 
						NULL, 
						0, 
						(LPTHREAD_START_ROUTINE)pLoad,
						pbuf, 
						0, 
						NULL);
					if (hRemote) {

						gPid = pid;
						CloseHandle(hRemote);
						PostMessage(WM_CLOSE);
						//AfxMessageBox(TEXT("ע��DLL�ɹ���"));
					}
				}
			}
		}
		CloseHandle(hPro);
	}
}
