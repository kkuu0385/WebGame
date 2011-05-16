// GtNewObjectDlg.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "GnTools.h"
#include "GtNewObjectDlg.h"
#include "afxdialogex.h"


// GtNewObjectDlg ��ȭ �����Դϴ�.

IMPLEMENT_DYNAMIC(GtNewObjectDlg, CDialogEx)

GtNewObjectDlg::GtNewObjectDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(GtNewObjectDlg::IDD, pParent)
{

}

GtNewObjectDlg::~GtNewObjectDlg()
{
}

void GtNewObjectDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDT_NEWOBJECTNAME, mObjectNameEdt);	
}


BEGIN_MESSAGE_MAP(GtNewObjectDlg, CDialogEx)
END_MESSAGE_MAP()


// GtNewObjectDlg �޽��� ó�����Դϴ�.


void GtNewObjectDlg::OnOK()
{
	mObjectNameEdt.GetWindowText( mObjectName );
	CDialogEx::OnOK();
}


BOOL GtNewObjectDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();		
	return TRUE;  // return TRUE unless you set the focus to a control
}
