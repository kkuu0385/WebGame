// �� MFC ���� �ҽ� �ڵ�� MFC Microsoft Office Fluent ����� �������̽�("Fluent UI")�� 
// ����ϴ� ����� ���� �ָ�, MFC C++ ���̺귯�� ����Ʈ��� ���Ե� 
// Microsoft Foundation Classes Reference �� ���� ���� ������ ���� 
// �߰������� �����Ǵ� �����Դϴ�.  
// Fluent UI�� ����, ��� �Ǵ� �����ϴ� �� ���� ��� ����� ������ �����˴ϴ�.  
// Fluent UI ���̼��� ���α׷��� ���� �ڼ��� ������ 
// http://msdn.microsoft.com/officeui�� �����Ͻʽÿ�.
//
// Copyright (C) Microsoft Corporation
// ��� �Ǹ� ����.

#include "stdafx.h"
#include "GnTools.h"
#include "GtProperties.h"
#include "MainFrm.h"
#include "GtBasicPropEntity.h"
#include "Gt2DTexturePropEntity.h"
#include "GtTextureAnimationPropEntity.h"
#include "GtPropertyGridMultiFileProperty.h"
#include "GnObjectNew.h"
#include "GtEditorPropSheet.h"
#include "GtEditorPropSheetDlg.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

#define TEXTURE_ENTITY _T("Textures")
#define ANIMATION_ENTITY _T("Ani")
#define BASIC_ENTITY _T("Basic")

/////////////////////////////////////////////////////////////////////////////
// CResourceViewBar

GtProperties::GtProperties() : mpEntities(NULL), mModified(false)
{
}

GtProperties::~GtProperties()
{
	if( mpEntities )
		delete mpEntities;
}

BEGIN_MESSAGE_MAP(GtProperties, CDockablePane)
	ON_WM_CREATE()
	ON_WM_SIZE()
	ON_COMMAND(ID_EXPAND_ALL, OnSortProperties)
	ON_COMMAND(ID_SORTPROPERTIES, OnExpandAllProperties)
	ON_COMMAND(ID_PROPERTIES1, OnProperties1)
	ON_COMMAND(ID_PROPERTIES2, OnProperties2)
	ON_WM_SETFOCUS()
	ON_REGISTERED_MESSAGE(AFX_WM_PROPERTY_CHANGED, OnPropertyChanged)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CResourceViewBar �޽��� ó����

void GtProperties::AdjustLayout()
{
	if (GetSafeHwnd() == NULL)
		return;

	CRect rectClient,rectCombo, rectDlg;
	GetClientRect(rectClient);
	m_wndObjectCombo.GetWindowRect(&rectCombo);
	mSequenceListCtrl.GetWindowRect(&rectDlg);

	int cyCmb = rectCombo.Size().cy;
	int cyTlb = mToolBar.CalcFixedLayout(FALSE, TRUE).cy;
	int cyDlg =  rectDlg.Size().cy;	

	m_wndPropList.SetDescriptionRows(5);
	m_wndObjectCombo.SetWindowPos(NULL, rectClient.left, rectClient.top, rectClient.Width(), 200, SWP_NOACTIVATE | SWP_NOZORDER);	
	mSequenceListCtrl.SetWindowPos(NULL, rectClient.left, rectClient.top + cyCmb, rectClient.Width(), cyDlg, SWP_NOACTIVATE|  SWP_NOZORDER);
	mToolBar.SetWindowPos(NULL, rectClient.left, rectClient.top + cyCmb + cyDlg, rectClient.Width(), cyTlb, SWP_NOACTIVATE | SWP_NOZORDER);
	m_wndPropList.SetWindowPos(NULL, rectClient.left, rectClient.top + cyCmb + cyTlb + cyDlg, rectClient.Width(), rectClient.Height() -(cyCmb+cyTlb+cyDlg), SWP_NOACTIVATE | SWP_NOZORDER);
}

int GtProperties::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CDockablePane::OnCreate(lpCreateStruct) == -1)
		return -1;

	AttachNeedMessage( GTMG_SELECTOBJECT );
	AttachNeedMessage( GTMG_SELECTSEQUENCE );

	CRect rectDummy;
	rectDummy.SetRectEmpty();
	// �޺� ���ڸ� ����ϴ�.
	DWORD dwViewStyle = WS_CHILD | WS_VISIBLE | CBS_DROPDOWNLIST | WS_BORDER | CBS_SORT | WS_CLIPSIBLINGS | WS_CLIPCHILDREN;
	if (!m_wndObjectCombo.Create(dwViewStyle, rectDummy, this, 1))
	{
		TRACE0("�Ӽ� �޺� ���ڸ� ������ ���߽��ϴ�. \n");
		return -1;      // ������ ���߽��ϴ�.
	}

	dwViewStyle = WS_CHILD | WS_VISIBLE | LVS_REPORT;
	rectDummy.right = 50;
	rectDummy.bottom = 250;
	if ( !mSequenceListCtrl.Create( dwViewStyle, rectDummy, this, 2 ) )
	{
		TRACE0("���� �並 ������ ���߽��ϴ�.\n");
		return -1;      // ������ ���߽��ϴ�.
	}

	m_wndObjectCombo.AddString(_T("���� ���α׷�"));
	m_wndObjectCombo.AddString(_T("�Ӽ� â"));
	m_wndObjectCombo.SetCurSel(0);

	if( !m_wndPropList.Create(WS_VISIBLE | WS_CHILD, rectDummy, this, 3))
	{
		TRACE0("�Ӽ� ǥ�� ������ ���߽��ϴ�. \n");
		return -1;      // ������ ���߽��ϴ�.
	}

	InitPropList();

	mToolBar.Create(this, AFX_DEFAULT_TOOLBAR_STYLE, IDR_PROPERTIES);
	mToolBar.LoadToolBar(IDR_PROPERTIES, 0, 0, TRUE /* ��� */);
	mToolBar.CleanUpLockedImages();
	mToolBar.LoadBitmap(theApp.m_bHiColorIcons ? IDB_PROPERTIES_HC : IDR_PROPERTIES, 0, 0, TRUE /* ��� */);

	mToolBar.SetPaneStyle(mToolBar.GetPaneStyle() | CBRS_TOOLTIPS | CBRS_FLYBY);
	mToolBar.SetPaneStyle(mToolBar.GetPaneStyle() & ~(CBRS_GRIPPER | CBRS_SIZE_DYNAMIC | CBRS_BORDER_TOP | CBRS_BORDER_BOTTOM | CBRS_BORDER_LEFT | CBRS_BORDER_RIGHT));
	mToolBar.SetOwner(this);
	// ��� ����� �θ� �������� �ƴ� �� ��Ʈ���� ���� ����õ˴ϴ�.
	mToolBar.SetRouteCommandsViaFrame(FALSE);

	AdjustLayout();
	return 0;
}

void GtProperties::OnSize(UINT nType, int cx, int cy)
{
	CDockablePane::OnSize(nType, cx, cy);
	AdjustLayout();
}

void GtProperties::OnSortProperties()
{
	GnLogA( "Start Save" );
	if( mpsCurrentObject == NULL )
		return;

	GtToolSettings::CreateDirectoryInWorkDirectory( mpsCurrentObject->GetObjectName() );
	mpsCurrentObject->SaveStream();
	GnLogA( "End Save" );
}

void GtProperties::OnExpandAllProperties()
{
	if( mpsCurrentObject == NULL )
		return;

	UpdateData();

	GtEditorPropSheetDlg* editorSheetDlg = new GtEditorPropSheetDlg(this);	
	GtEditorPropSheet* sheet = editorSheetDlg->GetEditorSheet();

	GtSequenceInfo* sequence = GnObjectNew<GtSequenceInfo>::Create();
	sheet->SetObject( mpsCurrentObject, sequence );
	sheet->SetModifyMode( 0 );
	INT_PTR ret = editorSheetDlg->DoModal();
	if(  ret == IDOK )
	{
		mSequenceListCtrl.AddSequence( sequence );
		mModified = true;
	}
	else if( ret == IDCANCEL )
	{
		GnObjectNew<GtSequenceInfo>::Delete( sequence );
	}	

	delete editorSheetDlg;
}

void GtProperties::OnProperties1()
{
	//if( mpsCurrentObject == NULL )
	//	return;

	//UpdateData();

	//GtEditorPropSheetDlg* editorSheetDlg = new GtEditorPropSheetDlg(this);	
	//GtEditorPropSheet* sheet = editorSheetDlg->GetEditorSheet();

	//GtSequenceInfo* sequence = GnObjectNew<GtSequenceInfo>::Create();
	//sheet->SetObject( mpsCurrentObject, sequence );
	//sheet->SetModifyMode( 0 );
	//INT_PTR ret = editorSheetDlg->DoModal();
	//if(  ret == IDOK )
	//{
	//	mSequenceListCtrl.AddSequence( sequence );
	//	mModified = true;
	//}
	//else if( ret == IDCANCEL )
	//{
	//	GnObjectNew<GtSequenceInfo>::Delete( sequence );
	//}	

	//delete editorSheetDlg;
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
	mSequenceListCtrl.RemoveCurrentSequence();
}

void GtProperties::OnProperties2()
{
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
	mSequenceListCtrl.RemoveCurrentSequence();
}

void GtProperties::InitPropList()
{
	m_wndPropList.EnableHeaderCtrl(FALSE);
	m_wndPropList.EnableDescriptionArea();
	//m_wndPropList.SetVSDotNetLook();
	m_wndPropList.MarkModifiedProperties();

	mpEntities = new GtCollectionEntities(&m_wndPropList);
}

void GtProperties::OnSetFocus(CWnd* pOldWnd)
{
	CDockablePane::OnSetFocus(pOldWnd);
	m_wndPropList.SetFocus();
}

LRESULT GtProperties::OnPropertyChanged(WPARAM wparam, LPARAM lparam)
{
	CMFCPropertyGridProperty *pProp = (CMFCPropertyGridProperty*)lparam;
	if (!pProp) return 0;

	GnTPrimitiveArray<GtPropertyEntity*> entities;
	mpEntities->GetEntities( entities );
	for( gtuint i = 0 ; i < entities.GetSize() ; i++ )
	{
		GtPropertyEntity* propEntity = entities.GetAt( i );
		propEntity->ApplyObjectData( pProp, mpsCurrentObject );
	}

	return 1;
}

void GtProperties::ReceiveMediateMessage(gtuint messageIndex, GtMediateObjectMessage* pInfo)
{
	switch( messageIndex )
	{
	case GTMG_SELECTOBJECT:
		{
			ChangeProperty( pInfo );
		}
		break;
	case GTMG_SELECTSEQUENCE:
		{
			ChangeSequence( pInfo );
		}
		break;
	}
}

void GtProperties::ChangeProperty(GtMediateObjectMessage* pInfo)
{
	mpEntities->DetachAllEntity();
	GtObjectMessage* objectInfo = (GtObjectMessage*)pInfo;
	mModified = false;	
	mpsCurrentObject = (GtActorObject*)objectInfo->mpObject;
	if( mpsCurrentObject->GetType() != GtActorObject::GTPLANEACTORTYPE )
		return;

	mSequenceListCtrl.ResetData( mpsCurrentObject );	
}

void GtProperties::ChangeSequence(GtMediateObjectMessage* pInfo)
{
	mpEntities->DetachAllEntity();
	GtSequenceMessage* objectInfo = (GtSequenceMessage*)pInfo;
	GtSequenceInfo* sequenceInfo = objectInfo->mpSequenceInfo;
	if( sequenceInfo == NULL )
		return;
	
	for( gtuint i = 0 ; i < sequenceInfo->GetTimeControllerCount() ; i++ )
	{
		GtTimeController* ctrl = sequenceInfo->GetTimeController( i );
		GtTextureAnimationPropEntity* textureProp = GnObjectNew<GtTextureAnimationPropEntity>::Create();
		textureProp->ParseToEntity( ctrl );
		mpEntities->AttachEntity( textureProp );
	}
}

void GtProperties::OnSaveObjectstate()
{
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
	if( mpsCurrentObject == NULL )
		return;

	GtToolSettings::CreateDirectoryInWorkDirectory( mpsCurrentObject->GetObjectName() );
	mpsCurrentObject->SaveStream();
}
