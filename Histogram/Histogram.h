
// Histogram.h : PROJECT_NAME ���� ���α׷��� ���� �� ��� �����Դϴ�.
//

#pragma once

#ifndef __AFXWIN_H__
	#error "PCH�� ���� �� ������ �����ϱ� ���� 'stdafx.h'�� �����մϴ�."
#endif

#include "resource.h"		// �� ��ȣ�Դϴ�.


// CHistogramApp:
// �� Ŭ������ ������ ���ؼ��� Histogram.cpp�� �����Ͻʽÿ�.
//

class CHistogramApp : public CWinApp
{
public:
	CHistogramApp();

// �������Դϴ�.
public:
	virtual BOOL InitInstance();

// �����Դϴ�.

	DECLARE_MESSAGE_MAP()
};

extern CHistogramApp theApp;