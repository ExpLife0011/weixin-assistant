#pragma once

#include "stdafx.h"

void MyHookApi(PVOID mApiAddr, PVOID mOurAddr);
void MyWorkThread(LPVOID lp);
void WINAPI MyGetSendData(SOCKET sock, char * pData, int nSize);
void WINAPI MyGetLoginData(char * pData, int nSize);

HWND hWnd;
BOOL bPauseRecord;
//UINT __cdecl MyControllingFunction(LPVOID pParam);
DWORD WINAPI MyControllingFunction(LPVOID pParam);

BYTE OldWSASendAddress[5];	//����WSASend����ǰ����ֽ�
PVOID pWSASend;	//WSASend������ַָ��
void UnhookWSASend(PVOID mApiAddr, PVOID mOldMem);

BYTE OldLoginAddress[5];
PVOID pLogin;
void UnhookLogin(PVOID mApiAddr, PVOID mOldMem);