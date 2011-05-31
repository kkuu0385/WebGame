#pragma once
#include "afxwin.h"


// GcNewObjectDlg ��ȭ �����Դϴ�.

class GcNewObjectDlg : public CDialogEx
{
	DECLARE_DYNAMIC(GcNewObjectDlg)

protected:
	CString mObjectName;
	CEdit mObjectNameEdt;

public:
	// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_GTNEWOBJECTDLG };

public:
	GcNewObjectDlg(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~GcNewObjectDlg();

	inline CString& GetObjectName() {
		return mObjectName;
	}

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
	virtual void OnOK();
public:
	virtual BOOL OnInitDialog();
};
