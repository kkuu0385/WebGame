#pragma once
#include "afxwin.h"


// GcNewObjectDlg ��ȭ �����Դϴ�.

class GcNewObjectDlg : public CDialogEx
{
	DECLARE_DYNAMIC(GcNewObjectDlg)
private:
	CComboBox mCBObjectType;
	int mObjectType;
	int mShowObjectType;
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
	inline int GetObjectType() {
		return mObjectType;
	}
	inline void HideObjectTypeComboBox() {
		mShowObjectType = SW_HIDE;
	}

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
	virtual void OnOK();
public:
	virtual BOOL OnInitDialog();
};
