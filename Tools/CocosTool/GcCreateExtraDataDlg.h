#pragma once


// GcCreateExtraDataDlg ��ȭ �����Դϴ�.

class GcCreateExtraDataDlg : public CDialogEx
{
	DECLARE_DYNAMIC(GcCreateExtraDataDlg)
public:
	enum { IDD = IDD_GCCREATEEXTRADATA };

protected:
	CComboBox mComboExtraDataType;
	int mSelectedExtraDataType;

public:
	GcCreateExtraDataDlg(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~GcCreateExtraDataDlg();

public:
	inline int GetSelectedExtraDataType() {
		return mSelectedExtraDataType;
	}

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
};
