// GtToolLib.h : GtToolLib DLL�� �⺻ ��� �����Դϴ�.
//

#pragma once

#ifndef __AFXWIN_H__
	#error "PCH�� ���� �� ������ �����ϱ� ���� 'stdafx.h'�� �����մϴ�."
#endif

#include "resource.h"		// �� ��ȣ�Դϴ�.


// CGtToolLibApp
// �� Ŭ������ ������ ������ GtToolLib.cpp�� �����Ͻʽÿ�.
//

class CGtToolLibApp : public CWinApp
{
public:
	CGtToolLibApp();

// �������Դϴ�.
public:
	virtual BOOL InitInstance();

	DECLARE_MESSAGE_MAP()
};
