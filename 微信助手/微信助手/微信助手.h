// ΢������.h : ΢������ DLL ����ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// C΢������App
// �йش���ʵ�ֵ���Ϣ������� ΢������.cpp
//

class C΢������App : public CWinApp
{
public:
	C΢������App();

// ��д
public:
	virtual BOOL InitInstance();

	DECLARE_MESSAGE_MAP()
	virtual int ExitInstance();
};
