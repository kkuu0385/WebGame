// GcSequenceModifyDockable.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "CocosTool.h"
#include "GcSequenceModifyDockable.h"
#include "GcSequenceTimeDlg.h"
#include "GcSequenceCollisionDlg.h"
#include "GcActorExtraDataDlg.h"

const gtchar* GcSequenceModifyDockable::msSequenceCollisionDlgName = _T("Collision");
const gtchar* GcSequenceModifyDockable::msSequenceTimeDlgName = _T("TimeKey");
const gtchar* GcSequenceModifyDockable::msActorEventDlgName = _T("ActorEvent");

GcSequenceModifyDockable::GcSequenceModifyDockable() : mCurrentAniTime(0.0f)
{

}

GcSequenceModifyDockable::~GcSequenceModifyDockable()
{
}


BEGIN_MESSAGE_MAP(GcSequenceModifyDockable, GcToolBarDockable)
	ON_WM_CREATE()
	ON_WM_SIZE()
END_MESSAGE_MAP()



// GcSequenceModifyDockable �޽��� ó�����Դϴ�.




int GcSequenceModifyDockable::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CDockablePane::OnCreate(lpCreateStruct) == -1)
		return -1;

	if (!mTabCtrl.Create (CMFCTabCtrl::STYLE_FLAT, CRect (0, 0, 0, 0), this, 1))
	{
		TRACE0("Failed to create output tab window\n");
		return -1;      // fail to create
	}

	// Create toolbar:
	mTabCtrl.SetFlatFrame (FALSE, FALSE);
	mTabCtrl.AutoDestroyWindow (FALSE);

	AttachNeedMessage( GTMG_SELECTOBJECT );
	AttachNeedMessage( GTMG_SELECTSEQUENCE );
	AttachNeedMessage( GTMG_DESTORY );
	AttachNeedMessage( GTMG_TIMECHANGE );
	return 0;
}

void GcSequenceModifyDockable::AddTab(CWnd* pAddWnd, CString strName)
{
	mTabCtrl.AddTab( pAddWnd, strName );
}

void GcSequenceModifyDockable::RemoveAllTab()
{
	for (int i = 0; i < mTabCtrl.GetTabsNum (); i++)
	{
		CWnd* pWnd = mTabCtrl.GetTabWnd (i);
		pWnd->DestroyWindow ();
		delete pWnd;
	}
	if( mTabCtrl.GetSafeHwnd() )
		mTabCtrl.RemoveAllTabs();
}

void GcSequenceModifyDockable::RemoveSequenceTab()
{
	for (int i = 0; i < mTabCtrl.GetTabsNum (); i++)
	{
		CWnd* pWnd = mTabCtrl.GetTabWnd (i);
		CString name;
		pWnd->GetWindowText( name );
		if( name == msSequenceCollisionDlgName || name == msSequenceTimeDlgName )
		{
			if( mTabCtrl.GetSafeHwnd() )
				mTabCtrl.RemoveTab( i-- );
			pWnd->DestroyWindow();
			delete pWnd;
		}
	}
}

void GcSequenceModifyDockable::ReceiveMediateMessage(gtuint messageIndex
	, GcMediateObjectMessage* pMessage)
{
	switch( messageIndex )
	{
	case GTMG_TIMECHANGE:
		if( pMessage->mTempMessage )
			SetCurrentAniTime( *((float*)pMessage->mTempMessage) );
		break;
	case GTMG_SELECTOBJECT:
		{
			ChangeProperty( pMessage );
		}
		break;
	case GTMG_SELECTSEQUENCE:
		{
			ChangeSequence( pMessage );
		}
		break;
	}
}

void GcSequenceModifyDockable::ChangeProperty(GcMediateObjectMessage* pMessage)
{
	CWnd* focus = GetFocus();
	mpsCurrentObject = pMessage->mpObject;
	RemoveAllTab();
	
	if( mpsCurrentObject )
	{
		Gn2DMeshObject* meshObject = NULL;
		Gt2DActor* actor = GnDynamicCast(Gt2DActor,  mpsCurrentObject );
		if( actor == NULL )
		{
			Gt2DMesh* mesh = GnDynamicCast(Gt2DMesh,  mpsCurrentObject );
			meshObject = mesh->Get2DMeshObjecct();
		}
		else
			meshObject = actor->GetRootNode();
			
		if( meshObject )
		{
			GcActorExtraDataDlg* timeDlg = new GcActorExtraDataDlg();
			timeDlg->Create( GcActorExtraDataDlg::IDD, &mTabCtrl );		
			timeDlg->ResetData( mpsCurrentObject, meshObject );
			//timeDlg->SetCurrentAniTime( mCurrentAniTime );
			timeDlg->SetWindowText( msActorEventDlgName );
			AddTab( timeDlg, msActorEventDlgName );
		}		
	}

	::SetFocus( focus->GetSafeHwnd() );
}

void GcSequenceModifyDockable::ChangeSequence(GcMediateObjectMessage* pMessage)
{
	CWnd* focus = GetFocus();
	int activeTab = -1;
	if( mTabCtrl.GetSafeHwnd() )
	{
		activeTab = mTabCtrl.GetActiveTab();
	}
	GcSequenceMessage* sequenceMessage = (GcSequenceMessage*)pMessage;
	if( sequenceMessage->mpSequenceInfo == NULL )
	{
		RemoveSequenceTab();
		return;
	}
	RemoveSequenceTab();

	Gt2DActor* actor = (Gt2DActor*)(GtObject*)sequenceMessage->mpObject;
	Gt2DSequence* gtSequence = NULL;
	if( actor->GetGtSequence( sequenceMessage->mpSequenceInfo->GetSequenceID(), gtSequence )
		== false )
		return;

	GcSequenceTimeDlg* timeDlg = new GcSequenceTimeDlg();
	timeDlg->Create( GcSequenceTimeDlg::IDD, &mTabCtrl );
	timeDlg->ResetData( gtSequence );
	timeDlg->SetCurrentAniTime( mCurrentAniTime );
	timeDlg->SetWindowText( msSequenceTimeDlgName );
	AddTab( timeDlg, msSequenceTimeDlgName );

	GcSequenceCollisionDlg* collisionDlg = new GcSequenceCollisionDlg();
	collisionDlg->Create( GcSequenceCollisionDlg::IDD, &mTabCtrl );
	collisionDlg->ResetData( actor, gtSequence );
	collisionDlg->SetWindowText( msSequenceCollisionDlgName );
	AddTab( collisionDlg, msSequenceCollisionDlgName );

	if( activeTab != -1 )
		mTabCtrl.SetActiveTab( activeTab );

	::SetFocus( focus->GetSafeHwnd() );
}

void GcSequenceModifyDockable::OnSize(UINT nType, int cx, int cy)
{
	GcToolBarDockable::OnSize(nType, cx, cy);

	CRect rectClient;
	GetClientRect (rectClient);
	mTabCtrl.SetWindowPos (NULL, rectClient.left, rectClient.top, 
		rectClient.Width (), rectClient.Height (),
		SWP_NOACTIVATE | SWP_NOZORDER);
}


void GcSequenceModifyDockable::PostNcDestroy()
{
	// TODO: ���⿡ Ư��ȭ�� �ڵ带 �߰� ��/�Ǵ� �⺻ Ŭ������ ȣ���մϴ�.

	GcToolBarDockable::PostNcDestroy();
}
