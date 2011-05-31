// GcCreateCollisionDlg.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "CocosTool.h"
#include "GcCreateCollisionDlg.h"
#include "afxdialogex.h"


// GcCreateCollisionDlg ��ȭ �����Դϴ�.

IMPLEMENT_DYNAMIC(GcCreateCollisionDlg, CDialogEx)

GcCreateCollisionDlg::GcCreateCollisionDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(GcCreateCollisionDlg::IDD, pParent), mSelectedCollisionType(0)
{

}

GcCreateCollisionDlg::~GcCreateCollisionDlg()
{
}

void GcCreateCollisionDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_CB_COLLISIONTYPE, mCollisionType);
	DDX_CBIndex(pDX, IDC_CB_COLLISIONTYPE, mSelectedCollisionType);
}


BEGIN_MESSAGE_MAP(GcCreateCollisionDlg, CDialogEx)
END_MESSAGE_MAP()


// GcCreateCollisionDlg �޽��� ó�����Դϴ�.


BOOL GcCreateCollisionDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	mCollisionType.SetCurSel(1);
	return TRUE;  // return TRUE unless you set the focus to a control
}
