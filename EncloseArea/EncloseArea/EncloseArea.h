
// EncloseArea.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CEncloseAreaApp:
// �йش����ʵ�֣������ EncloseArea.cpp
//

class CEncloseAreaApp : public CWinApp
{
public:
	CEncloseAreaApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CEncloseAreaApp theApp;