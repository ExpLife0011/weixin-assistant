
// MFCWebDemo.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CMFCWebDemoApp: 
// �йش����ʵ�֣������ MFCWebDemo.cpp
//

class CMFCWebDemoApp : public CWinApp
{
public:
	CMFCWebDemoApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CMFCWebDemoApp theApp;