#pragma once
#include "afxwin.h"


// GcCreateCollisionDlg ��ȭ �����Դϴ�.

class GcCreateCollisionDlg : public CDialogEx
{
	DECLARE_DYNAMIC(GcCreateCollisionDlg)
public:
	enum { IDD = IDD_GCCREATECOLLISIONDLG };

protected:
	CComboBox mCollisionType;
	int mSelectedCollisionType;

public:
	GcCreateCollisionDlg(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~GcCreateCollisionDlg();

	inline int GetSelectedCollisionType() {
		return mSelectedCollisionType;
	}

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
};
