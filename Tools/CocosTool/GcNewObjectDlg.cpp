// GcNewObjectDlg.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "CocosTool.h"
#include "GcNewObjectDlg.h"
#include "afxdialogex.h"


// GcNewObjectDlg ��ȭ �����Դϴ�.

IMPLEMENT_DYNAMIC(GcNewObjectDlg, CDialogEx)

	GcNewObjectDlg::GcNewObjectDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(GcNewObjectDlg::IDD, pParent)
{

}

GcNewObjectDlg::~GcNewObjectDlg()
{
}

void GcNewObjectDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDT_NEWOBJECTNAME, mObjectNameEdt);	
}


BEGIN_MESSAGE_MAP(GcNewObjectDlg, CDialogEx)
END_MESSAGE_MAP()


// GcNewObjectDlg �޽��� ó�����Դϴ�.


void GcNewObjectDlg::OnOK()
{
	mObjectNameEdt.GetWindowText( mObjectName );
	CDialogEx::OnOK();
}


BOOL GcNewObjectDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();		
	return TRUE;  // return TRUE unless you set the focus to a control
}
