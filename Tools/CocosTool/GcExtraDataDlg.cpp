// GcExtraDataDlg.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "CocosTool.h"
#include "GcExtraDataDlg.h"
#include "afxdialogex.h"


// GcExtraDataDlg ��ȭ �����Դϴ�.

IMPLEMENT_DYNAMIC(GcExtraDataDlg, CDialogEx)

GcExtraDataDlg::GcExtraDataDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(GcExtraDataDlg::IDD, pParent)
{

}

GcExtraDataDlg::~GcExtraDataDlg()
{
	mExtraDataPropEntity.SetNullProperty();
}

void GcExtraDataDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LISTACTOREVENT, mActorEventList);
	DDX_Control(pDX, IDC_ACTOREVENT_LOCATION, mActorEventPropLocation);
}

BEGIN_MESSAGE_MAP(GcExtraDataDlg, CDialogEx)
	ON_WM_SIZE()
END_MESSAGE_MAP()



BOOL GcExtraDataDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	mListName = _T("ExtraData List");
	mActorEventList.SetStandardButtons( AFX_VSLISTBOX_BTN_NEW | AFX_VSLISTBOX_BTN_DELETE );
	mActorEventList.EnableBrowseButton( false );

	CRect rectPropList;
	mActorEventPropLocation.GetClientRect(&rectPropList);
	mActorEventPropLocation.MapWindowPoints(this, &rectPropList);

	mActorEventProp.Create( WS_CHILD | WS_VISIBLE , rectPropList, this, 2 );
	mActorEventProp.EnableHeaderCtrl(FALSE);
	mActorEventProp.EnableDescriptionArea();
	mActorEventProp.SetVSDotNetLook();
	mActorEventProp.MarkModifiedProperties();
	mActorEventProp.AddProperty( mExtraDataPropEntity.GetProperty() );

	mActorEventList.EnableWindow( false );
	EnablePropertyGridCtrl( false );
	return TRUE;  // return TRUE unless you set the focus to a control
	// ����: OCX �Ӽ� �������� FALSE�� ��ȯ�ؾ� �մϴ�.
}

void GcExtraDataDlg::OnSize(UINT nType, int cx, int cy)
{
	CDialogEx::OnSize(nType, cx, cy);

	if (GetSafeHwnd() == NULL)
		return;	

	CRect rect;
	if( mActorEventProp.GetSafeHwnd() )
	{
		mActorEventProp.GetWindowRect( rect );
		ScreenToClient( rect );
		mActorEventProp.SetWindowPos(NULL, rect.left,  rect.top, rect.Size().cx, cy
			, SWP_NOACTIVATE | SWP_NOZORDER);
	}

	if( mActorEventList.GetSafeHwnd() )
	{
		mActorEventList.GetWindowRect( rect );
		ScreenToClient( rect );
		mActorEventList.SetWindowPos(NULL, rect.left,  rect.top, rect.Size().cx, cy
			, SWP_NOACTIVATE | SWP_NOZORDER);
	}
}

void GcExtraDataDlg::ResetData(GtObject* pObject, Gn2DMeshObject* pMeshObject)
{
	mpObject = pObject;
	mpMeshObject = pMeshObject;
	if( pObject == NULL || pMeshObject == NULL)
	{
		mActorEventList.EnableWindow( false );
		EnablePropertyGridCtrl( false );
	}
	mActorEventList.EnableWindow();
	mActorEventList.ResetData( pObject, pMeshObject );

	GtConvertString convert = mpObject->GetObjectName();
	CString name = convert.c_str();
	name += _T(" - ");
	name += mListName;
	mActorEventList.SetWindowText( name );
}

void GcExtraDataDlg::EnablePropertyGridCtrl(bool bEnable)
{
	mActorEventProp.EnableWindow( bEnable );
	COLORREF color = RGB(220, 220, 220);
	if( bEnable )
	{
		color = (COLORREF)-1;
		mActorEventProp.SetCustomColors( color, color, color, color, color, color, color );
	}
	else
	{
		mActorEventProp.SetCustomColors( color, color+RGB(20, 20, 20), color+RGB(10, 10, 10)
			, color+RGB(20, 20, 20), color, color+RGB(20, 20, 20), color );
	}
	
	mActorEventProp.RedrawWindow();
}

BOOL GcExtraDataDlg::OnNotify(WPARAM wParam, LPARAM lParam, LRESULT* pResult)
{
	GTVSITEMACTIVATE* item = (GTVSITEMACTIVATE*)lParam;
	switch( wParam )
	{
	case GTMG_VSLISTITEM_BEFOREREMOVE:
		{
			if( item->iItem == -1 )
				break;

			EnablePropertyGridCtrl( false );
		}
		break;
	case GTMG_VSLISTITEM_SELECTCHANGED:
		{
			if( item->iItem == -1 )
				break;

			EnablePropertyGridCtrl( true );
			GcExtraDataPropEntity::ThisEntityData data;
			data.mpObject = mpObject;
			data.mpMeshObject = mpMeshObject;
			data.mSelectRectIndex = item->iItem;
			if( item->iItem == -1 )
				break;

			mExtraDataPropEntity.ParseToEntity( &data );
		}
		break;
	case GTMG_VSLISTITEM_AFTERADD:
		{
			if( item->iItem == -1 )
				break;
		}
		break;
	}
	return CDialogEx::OnNotify(wParam, lParam, pResult);
}
