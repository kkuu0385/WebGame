#ifndef GNTOOLS_H
#define GNTOOLS_H

#pragma once

#ifndef __AFXWIN_H__
	#error "PCH�� ���� �� ������ �����ϱ� ���� 'stdafx.h'�� �����մϴ�."
#endif

#include "resource.h"       // �� ��ȣ�Դϴ�.


// CGnToolsApp:
// �� Ŭ������ ������ ���ؼ��� GnTools.cpp�� �����Ͻʽÿ�.
//
class GnFrame;
GnFrame* GetActiveGnFrame();

class CGnToolsApp : public CWinAppEx
{
public:
	CGnToolsApp();


// �������Դϴ�.
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// �����Դϴ�.
	COleTemplateServer m_server;
		// ���� ����⿡ ���� ���� ��ü�Դϴ�.
	UINT  m_nAppLook;
	BOOL  m_bHiColorIcons;

	virtual void PreLoadState();
	virtual void LoadCustomState();
	virtual void SaveCustomState();

	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CGnToolsApp theApp;

#endif // GNTOOLS_H