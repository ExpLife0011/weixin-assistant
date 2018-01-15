// ΢������.cpp : ���� DLL �ĳ�ʼ�����̡�
//

#include "stdafx.h"
#include "΢������.h"

#include <process.h>
#include "Inc.h"
#include "ApiUtils.h"
#include "StringUtils.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

//
//TODO:  ����� DLL ����� MFC DLL �Ƕ�̬���ӵģ�
//		��Ӵ� DLL �������κε���
//		MFC �ĺ������뽫 AFX_MANAGE_STATE ����ӵ�
//		�ú�������ǰ�档
//
//		����: 
//
//		extern "C" BOOL PASCAL EXPORT ExportedFunction()
//		{
//			AFX_MANAGE_STATE(AfxGetStaticModuleState());
//			// �˴�Ϊ��ͨ������
//		}
//
//		�˺������κ� MFC ����
//		������ÿ��������ʮ����Ҫ��  ����ζ��
//		��������Ϊ�����еĵ�һ�����
//		���֣������������ж������������
//		������Ϊ���ǵĹ��캯���������� MFC
//		DLL ���á�
//
//		�й�������ϸ��Ϣ��
//		����� MFC ����˵�� 33 �� 58��
//

// C΢������App

BEGIN_MESSAGE_MAP(C΢������App, CWinApp)
END_MESSAGE_MAP()


// C΢������App ����

C΢������App::C΢������App()
{
	// TODO:  �ڴ˴���ӹ�����룬
	// ��������Ҫ�ĳ�ʼ�������� InitInstance ��
}


// Ψһ��һ�� C΢������App ����

C΢������App theApp;


// C΢������App ��ʼ��

BOOL C΢������App::InitInstance()
{
	CWinApp::InitInstance();

	if (!AfxSocketInit())
	{
		AfxMessageBox(IDP_SOCKETS_INIT_FAILED);
		return FALSE;
	}

	bPauseRecord = FALSE;

	_beginthread(MyWorkThread, 0, NULL);

	return TRUE;
}

//ȫ�ֱ���
DWORD	mSendJmp = 0;
DWORD	mLoginJmp = 0;
DWORD	g_ThreadId = 0;
HANDLE	g_WorkThreadHandle = NULL;
BOOL	debug = TRUE;
//----------------------

static VOID MyWindowProc(
	_In_ HWND hwnd,
	_In_ UINT uMsg,
	_In_ WPARAM wParam,
	_In_ LPARAM lParam
) {

	if (bPauseRecord) {
		return;
	}
		
	HWND hWndTarget = ::FindWindow(NULL, TEXT("CNJע�빤��������"));

	switch (uMsg) {

	case WM_LBUTTONDOWN:
	{

		COPYDATASTRUCT cData = { 0 };
		char text[128];
		int len = sprintf_s(text, "WM_LBUTTONDOWN = hwnd:[0x%08X]-msg:[%d]-wp:[%d]-lp:[%d]", hwnd, uMsg, wParam, lParam);
		cData.lpData = text;
		cData.cbData = len;
		::SendMessage(hWndTarget, WM_COPYDATA, 0, (LPARAM)&cData);
		break;
	}

	case WM_SYSCOMMAND:
	{

		COPYDATASTRUCT cData = { 0 };
		char text[128];
		int len = sprintf_s(text, "WM_SYSCOMMAND = hwnd:[0x%08X]-msg:[%d]-wp:[%d]-lp:[%d]", hwnd, uMsg, wParam, lParam);
		cData.lpData = text;
		cData.cbData = len;
		::SendMessage(hWndTarget, WM_COPYDATA, 0, (LPARAM)&cData);
		break;
	}

	case WM_CLOSE:
	{

		COPYDATASTRUCT cData = { 0 };
		char text[128];
		int len = sprintf_s(text, "WM_CLOSE = hwnd:[0x%08X]-msg:[%d]-wp:[%d]-lp:[%d]", hwnd, uMsg, wParam, lParam);
		cData.lpData = text;
		cData.cbData = len;
		::SendMessage(hWndTarget, WM_COPYDATA, 0, (LPARAM)&cData);
		break;
	}

	case WM_MOVE:
	{

		COPYDATASTRUCT cData = { 0 };
		char text[128];
		int len = sprintf_s(text, "WM_MOVE = hwnd:[0x%08X]-msg:[%d]-wp:[%d]-lp:[%d]", hwnd, uMsg, wParam, lParam);
		cData.lpData = text;
		cData.cbData = len;
		::SendMessage(hWndTarget, WM_COPYDATA, 0, (LPARAM)&cData);
		break;
	}

	}

	//if (uMsg == 132 || uMsg == 32 || uMsg == 874 || uMsg == 512 || 
	//	uMsg == 160 || uMsg == 15 || uMsg == 646 || uMsg == 642 ||
	//	uMsg == 258 || uMsg == 674 || uMsg == 675) return;

	//COPYDATASTRUCT cData = { 0 };
	//char text[128];
	//int len = sprintf_s(text, "hwnd:[0x%08X]-msg:[%d]-wp:[%d]-lp:[%d]", hwnd, uMsg, wParam, lParam);
	//cData.lpData = text;
	//cData.cbData = len;
	//::SendMessage(hWndTarget, WM_COPYDATA, 0, (LPARAM)&cData);

}

//hook ����------------------------------------------
void _declspec(naked)MySend() {

	_asm {
		mov edi, edi
		push ebp
		mov ebp, esp
		pushad
		pushfd

		push[ebp + 10h]
		push[ebp + 0ch]
		push[ebp + 08h]
		call MyGetSendData

		popfd
		popad
		jmp mSendJmp
	}
}

void WINAPI MyGetSendData(SOCKET sock, char * pData, int nSize) {

	//static int times = 0;
	//if (times++ < 5) {
	//	CString cstr = ((LPWSABUF)pData)->buf;
	//	AfxMessageBox(cstr);
	//}

	//return;

	//��ȡ���ھ��
	HWND hwnd = ::FindWindow(NULL, TEXT("CNJע�빤��������"));
	if (NULL == hwnd) {
		return;
	}

	//�жϼ�¼������ͣ��¼
	if (!bPauseRecord && debug) {

		//���hook����WSASend��ʹ������Ĵ���
		COPYDATASTRUCT cData = { 0 };
		cData.lpData = ((LPWSABUF)pData)->buf;
		cData.cbData = ((LPWSABUF)pData)->len;

		//���hook����send
		//COPYDATASTRUCT cData = { 0 };
		//cData.lpData = pData;
		//cData.cbData = nSize;

		::SendMessage(hWnd, WM_COPYDATA, 0, (LPARAM)&cData);
	}

	//��ȡ����ip��ַ
	sockaddr_in peersockaddr;
	int nsocksize = sizeof(sockaddr_in);
	getpeername(sock, (sockaddr*)&peersockaddr, &nsocksize);
}

//ж�ط��͹���
void UnhookWSASend(PVOID mApiAddr, PVOID mOldMem) {

	DWORD flOldProtect = 0;

	//�ı�HOOK���ڴ�����
	VirtualProtect(mApiAddr, 5, PAGE_EXECUTE_READWRITE, &flOldProtect);
	memcpy(mApiAddr, mOldMem, 5);
	VirtualProtect(mApiAddr, 5, flOldProtect, &flOldProtect);
}


//hook ��½-------------------------------------------
void _declspec(naked)MyLogin() {

	_asm {
		jmp mLoginJmp;
	}
}

void WINAPI MyGetLoginData(char * pData, int nSize)
{

	return;
}

void UnhookLogin(PVOID mApiAddr, PVOID mOldMem) {

	DWORD flOldProtect = 0;

	//�ı�HOOK���ڴ�����
	VirtualProtect(mApiAddr, 5, PAGE_EXECUTE_READWRITE, &flOldProtect);
	memcpy(mApiAddr, mOldMem, 5);
	VirtualProtect(mApiAddr, 5, flOldProtect, &flOldProtect);
}
//------------------------


//�����߳�
void MyWorkThread(LPVOID lp) {

	hWnd = ::FindWindow(NULL, TEXT("CNJע�빤��������"));
	if (hWnd) {

		//CWinThread *winthread = AfxBeginThread(MyControllingFunction, NULL);
		//g_ThreadId = winthread->m_nThreadID;
		g_WorkThreadHandle = CreateThread(NULL, 0, MyControllingFunction, NULL, 0, &g_ThreadId);
		if (g_WorkThreadHandle) {

			::SendMessage(hWnd, WM_THREAD_ID, 0, (LPARAM)g_ThreadId);
		}
	}

	//װ�ع���
	HMODULE hMod = LoadLibrary("ws2_32.dll");

	if (hMod) {
		//����exeʹ�õ���WSASend
		pWSASend = GetProcAddress(hMod, "WSASend");
		//΢��ʹ�õ���send
		//pWSASend = GetProcAddress(hMod, "send");
		mSendJmp = (DWORD)pWSASend + 5;	//���ص�ַ������mov ebp, esp��һ��ָ��ĵ�ַ
										//hook api
		memcpy(OldWSASendAddress, pWSASend, 5);
		MyHookApi(pWSASend, MySend);
	}

	//���Դ������໯,��ס���ڴ�����
	ApiUtils::hook_windproc(MyWindowProc);
}

//hook����
void MyHookApi(PVOID mApiAddr, PVOID mOurAddr) {

	DWORD flOldProtect = 0;

	//�ı�HOOK���ڴ�����
	VirtualProtect(mApiAddr, 5, PAGE_EXECUTE_READWRITE, &flOldProtect);
	*(PBYTE)mApiAddr = 0xE9;											//jmpԶ��ת�Ļ���ָ��Ĳ�����
	*(DWORD*)((DWORD)mApiAddr + 1) = (DWORD)mOurAddr - (DWORD)mApiAddr - 5;	//jmpԶ��ת��ƫ�Ƶ�ַ
																			//�ָ�HOOK���ڴ�����
	VirtualProtect(mApiAddr, 5, flOldProtect, &flOldProtect);
}

//������պ���
DWORD WINAPI MyControllingFunction(LPVOID pParam) {

	MSG msg;

	while (TRUE) {

		if (::PeekMessage(&msg, NULL, WM_THREAD_MIN, WM_THREAD_MAX, PM_REMOVE)) {

			switch (msg.message)
			{
			case WM_PAUSE_RECORD:
				bPauseRecord = TRUE;
				//AfxMessageBox(TEXT("���յ����ƶ˵���ͣ��¼������"));
				break;
			case WM_RECONTINUE_RECORD:
				bPauseRecord = FALSE;
				break;
			case WM_FREEDLL:
				//_asm int 3
				//UnhookWSASend(pWSASend, OldWSASendAddress);
				//��ģ���ַ���ͻؿ��ƶ�
				//::PostMessage(hWnd, WM_FREELIBRARY, 0, (LPARAM)AfxGetInstanceHandle());
				//AfxEndThread(0);
				CloseHandle(g_WorkThreadHandle);
				return 0;
			default:
				break;
			}
		}

		Sleep(100);

	}
	return 0;
}

int C΢������App::ExitInstance()
{
	// TODO: �ڴ����ר�ô����/����û���

	//�ϵ� ʹ��windbg���е���ʱʹ��
	//_asm int 3

	//�������߳�
	if (g_WorkThreadHandle) {

		//֪ͨ��������߳��˳�
		::PostThreadMessage(g_ThreadId, WM_FREEDLL, 0, 0);

		if (WAIT_TIMEOUT == WaitForSingleObject(g_WorkThreadHandle, 800)) {
			TerminateThread(g_WorkThreadHandle, -1);
			::PostMessage(hWnd, WM_FORCEEXIT, 0, 0);
		}
		else {
			::PostMessage(hWnd, WM_FREESUCCESS, 0, 0);
		}
		g_WorkThreadHandle = NULL;

	}

	//ж�ع���
	UnhookWSASend(pWSASend, OldWSASendAddress);

	//�ָ����ڹ���
	ApiUtils::unhook_windproc();

	return CWinApp::ExitInstance();
}