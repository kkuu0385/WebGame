// GcSequenceTimeDlg.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "CocosTool.h"
#include "GcSequenceTimeDlg.h"
#include "afxdialogex.h"


// GcSequenceTimeDlg ��ȭ �����Դϴ�.

IMPLEMENT_DYNAMIC(GcSequenceTimeDlg, CDialogEx)

GcSequenceTimeDlg::GcSequenceTimeDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(GcSequenceTimeDlg::IDD, pParent)
{
	AttachNeedMessage( GTMG_TIMECHANGE );
}

GcSequenceTimeDlg::~GcSequenceTimeDlg()
{
	DetachNeedMessage( GTMG_TIMECHANGE );
	mAnimationKeyPropEntity.SetNullProperty();
}

void GcSequenceTimeDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LISTANIMATIONKEY, mAnimationKeyList);
	DDX_Control(pDX, IDC_KEYANIMATION_LOCATION, mAnimationKeyLocaton);
}


BEGIN_MESSAGE_MAP(GcSequenceTimeDlg, CDialogEx)
	ON_BN_CLICKED(IDC_APPLY_CURRENTTIMEANIKEY, &GcSequenceTimeDlg::OnBnClickedApplyCurrenttimeanikey)
END_MESSAGE_MAP()

BOOL GcSequenceTimeDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	mAnimationKeyList.SetWindowText( _T("AnimationKey List") );
	mAnimationKeyList.SetStandardButtons( AFX_VSLISTBOX_BTN_NEW | AFX_VSLISTBOX_BTN_DELETE );
	mAnimationKeyList.EnableBrowseButton( false );

	CRect rectPropList;
	mAnimationKeyLocaton.GetClientRect(&rectPropList);
	mAnimationKeyLocaton.MapWindowPoints(this, &rectPropList);

	mAnimationKeyProp.Create( WS_CHILD | WS_VISIBLE , rectPropList, this, 2 );
	mAnimationKeyProp.EnableHeaderCtrl(FALSE);
	mAnimationKeyProp.EnableDescriptionArea();
	mAnimationKeyProp.SetVSDotNetLook();
	mAnimationKeyProp.MarkModifiedProperties();
	mAnimationKeyProp.AddProperty( mAnimationKeyPropEntity.GetProperty() );
	return TRUE;
}

void GcSequenceTimeDlg::ResetData(Gt2DSequence* val)
{
	mpSequence = val;
	mAnimationKeyList.ResetData( mpSequence );
}

void GcSequenceTimeDlg::SetCurrentAniTime(float val)
{
	mCurrentAniTime = val;
	mAnimationKeyList.SetCurrentTime( val );
}

void GcSequenceTimeDlg::ReceiveMediateMessage(gtuint messageIndex
	, GcMediateObjectMessage* pMessage)
{
	switch( messageIndex )
	{
	case GTMG_TIMECHANGE:
		if( pMessage->mTempMessage )
			SetCurrentAniTime( *((float*)pMessage->mTempMessage) );
		break;
	}
}

BOOL GcSequenceTimeDlg::OnNotify(WPARAM wParam, LPARAM lParam, LRESULT* pResult)
{
	// TODO: ���⿡ Ư��ȭ�� �ڵ带 �߰� ��/�Ǵ� �⺻ Ŭ������ ȣ���մϴ�.
	GTVSITEMACTIVATE* item = (GTVSITEMACTIVATE*)lParam;
	switch( wParam )
	{
	case GTMG_VSLISTITEM_BEFOREREMOVE:
		{
			if( item->iItem == -1 )
				break;
		}
		break;
	case GTMG_VSLISTITEM_SELECTCHANGED:
		{
			if( item->iItem == -1 )
				break;
			GcAnimationKeyPropEntity::ThisEntityData data;
			data.mpObject = mpSequence;
			data.mAniKeyIndex = mAnimationKeyList.GetAniKeyIndex( item->iItem );
			if( data.mAniKeyIndex == -1 )
				break;

			mAnimationKeyPropEntity.ParseToEntity( &data );
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

void GcSequenceTimeDlg::OnBnClickedApplyCurrenttimeanikey()
{
	mAnimationKeyPropEntity.SetCurrentTime( mCurrentAniTime );
}
