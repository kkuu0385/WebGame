#pragma once
#include "afxwin.h"


// CreateAnimationKeyDlg ��ȭ �����Դϴ�.

class CreateAnimationKeyDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CreateAnimationKeyDlg)
public:
	enum { IDD = IDD_ADDANIMATIONKEY };

public:
	CreateAnimationKeyDlg(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CreateAnimationKeyDlg();

	inline CString GetSelectString() {
		return mSelectString;
	}
	inline int GetSelectType() {
		return mSelectType;
	}

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
protected:
	CComboBox mAnimationKeyType;
	CString mSelectString;
	int mSelectType;
public:
	virtual BOOL OnInitDialog();
};
