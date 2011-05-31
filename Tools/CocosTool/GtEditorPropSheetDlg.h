#pragma once
#include "GtEditorPropSheet.h"
#include "GcPropertyGridCtrl.h"


// GtEditorPropSheetDlg ��ȭ �����Դϴ�.

class GtEditorPropSheetDlg : public CDialogEx
{
	DECLARE_DYNAMIC(GtEditorPropSheetDlg)
public:
	enum { IDD = IDD_GtEditorPropSheetDlg2 };

protected:
	GtEditorPropSheet mEditorSheet;
	GcPropertyGridCtrl mPropList;

public:
	GtEditorPropSheetDlg(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~GtEditorPropSheetDlg();

	void AdjustLayout();

	inline GtEditorPropSheet* GetEditorSheet() {
		return &mEditorSheet;
	}
	inline GcPropertyGridCtrl* GetPropList() {
		return &mPropList;
	}
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
};
