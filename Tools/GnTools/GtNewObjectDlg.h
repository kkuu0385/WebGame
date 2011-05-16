#pragma once
#include "afxwin.h"


// GtNewObjectDlg ��ȭ �����Դϴ�.

class GtNewObjectDlg : public CDialogEx
{
	DECLARE_DYNAMIC(GtNewObjectDlg)

protected:
	CString mObjectName;
	CEdit mObjectNameEdt;

public:
	// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_GTNEWOBJECTDLG };

public:
	GtNewObjectDlg(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~GtNewObjectDlg();

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
