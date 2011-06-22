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

// MainFrm.cpp : CMainFrame Ŭ������ ����
//

#include "stdafx.h"
#include "CocosTool.h"

#include "MainFrm.h"
#include "GtToolEBM.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CMainFrame

IMPLEMENT_DYNCREATE(CMainFrame, CFrameWndEx)

BEGIN_MESSAGE_MAP(CMainFrame, CFrameWndEx)
	ON_WM_CREATE()
	ON_COMMAND(ID_VIEW_CAPTION_BAR, &CMainFrame::OnViewCaptionBar)
	ON_UPDATE_COMMAND_UI(ID_VIEW_CAPTION_BAR, &CMainFrame::OnUpdateViewCaptionBar)
	ON_COMMAND(ID_TOOLS_OPTIONS, &CMainFrame::OnOptions)
	ON_COMMAND(IDC_SAVE_OBJECTSTATE, &CMainFrame::OnSaveObjectState)
	ON_COMMAND(ID_VIEW_SEQUENCEDOCKABLE, &CMainFrame::OnViewSequencedockable)
	ON_UPDATE_COMMAND_UI(ID_VIEW_SEQUENCEDOCKABLE, &CMainFrame::OnUpdateViewSequencedockable)
END_MESSAGE_MAP()

// CMainFrame ����/�Ҹ�

CMainFrame::CMainFrame() : mpObject(NULL)
{
	// TODO: ���⿡ ��� �ʱ�ȭ �ڵ带 �߰��մϴ�.
}

CMainFrame::~CMainFrame()
{
}

// CMainFrame ����

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
	CFrameWndEx::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	CFrameWndEx::Dump(dc);
}
#endif //_DEBUG



int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CFrameWndEx::OnCreate(lpCreateStruct) == -1)
		return -1;

	GtToolEBM::StartupEBM();

	BOOL bNameValid;

	// ��� ����� �������̽� ��Ҹ� �׸��� �� ����ϴ� ���־� �����ڸ� �����մϴ�.
	CMFCVisualManagerOffice2007::SetStyle(CMFCVisualManagerOffice2007::Office2007_Aqua);
	CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerOffice2007));
	//CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerWindows7));
	//CDockingManager::SetDockingMode(DT_SMART);
	//m_wndRibbonBar.SetWindows7Look(TRUE);

	m_wndRibbonBar.Create(this);
	m_wndRibbonBar.LoadFromResource(IDR_RIBBON);

	if (!m_wndStatusBar.Create(this))
	{
		TRACE0("���� ǥ������ ������ ���߽��ϴ�.\n");
		return -1;      // ������ ���߽��ϴ�.
	}

	CString strTitlePane1;
	CString strTitlePane2;
	bNameValid = strTitlePane1.LoadString(IDS_STATUS_PANE1);
	ASSERT(bNameValid);
	bNameValid = strTitlePane2.LoadString(IDS_STATUS_PANE2);
	ASSERT(bNameValid);
	m_wndStatusBar.AddElement(new CMFCRibbonStatusBarPane(ID_STATUSBAR_PANE1, strTitlePane1, TRUE), strTitlePane1);
	m_wndStatusBar.AddExtendedElement(new CMFCRibbonStatusBarPane(ID_STATUSBAR_PANE2, strTitlePane2, TRUE), strTitlePane2);

	// Visual Studio 2005 ��Ÿ�� ��ŷ â ������ Ȱ��ȭ�մϴ�.
	CDockingManager::SetDockingMode(DT_SMART);
	// Visual Studio 2005 ��Ÿ�� ��ŷ â �ڵ� ���� ������ Ȱ��ȭ�մϴ�.
	EnableAutoHidePanes(CBRS_ALIGN_ANY);

	// Ž�� â�� ���ʿ� ��������Ƿ� �Ͻ������� ���ʿ� ��ŷ�� ��Ȱ��ȭ�մϴ�.
	EnableDocking(CBRS_ALIGN_TOP | CBRS_ALIGN_BOTTOM | CBRS_ALIGN_RIGHT);

	// "Outlook" Ž�� ������ ����� ��ġ�մϴ�.
	if (!CreateOutlookBar(m_wndNavigationBar, ID_VIEW_NAVIGATION, 250))
	{
		TRACE0("Ž�� â�� ������ ���߽��ϴ�.\n");
		return -1;      // ������ ���߽��ϴ�.
	}
	
	if (!CreateDockableBar())
	{
		TRACE0("��ŷ â�� ������ ���߽��ϴ�.\n");
		return -1;      // ������ ���߽��ϴ�.
	}

	// ĸ�� ǥ������ ����ϴ�.
	if (!CreateCaptionBar())
	{
		TRACE0("ĸ�� ǥ������ ������ ���߽��ϴ�.\n");
		return -1;      // ������ ���߽��ϴ�.
	}

	// Outlook ǥ������ ��������� ���ʿ� ��ŷ�� �� �ֵ��� ����ؾ� �մϴ�.
	EnableDocking(CBRS_ALIGN_LEFT);
	EnableAutoHidePanes(CBRS_ALIGN_RIGHT);

	AttachNeedMessage( GTMG_SELECTOBJECT );
	AttachNeedMessage( GTMG_DESTORY );
	return 0;
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if( !CFrameWndEx::PreCreateWindow(cs) )
		return FALSE;
	// TODO: CREATESTRUCT cs�� �����Ͽ� ���⿡��
	//  Window Ŭ���� �Ǵ� ��Ÿ���� �����մϴ�.

	cs.style = WS_OVERLAPPED | WS_CAPTION | FWS_ADDTOTITLE
		| WS_THICKFRAME | WS_MINIMIZEBOX | WS_MAXIMIZEBOX;

	return TRUE;
}

BOOL CMainFrame::CreateOutlookBar(CMFCOutlookBar& bar, UINT uiID, int nInitialWidth)
{
	bar.SetMode2003();

	BOOL bNameValid;
	CString strTemp;
	bNameValid = strTemp.LoadString(IDS_SHORTCUTS);
	ASSERT(bNameValid);
	if (!bar.Create(strTemp, this, CRect(0, 0, nInitialWidth, 32000), uiID, WS_CHILD | WS_VISIBLE | CBRS_LEFT))
	{
		return FALSE; // ������ ���߽��ϴ�.
	}

	CMFCOutlookBarTabCtrl* pOutlookBar = (CMFCOutlookBarTabCtrl*)bar.GetUnderlyingWindow();

	if (pOutlookBar == NULL)
	{
		ASSERT(FALSE);
		return FALSE;
	}

	pOutlookBar->EnableInPlaceEdit(TRUE);

	static UINT uiPageID = 1;

	// �����̰ų�, �ڵ����� ����ų�, ũ�⸦ ������ �� ������ ���� ���� �����ϴ�.
	DWORD dwStyle = AFX_CBRS_FLOAT | AFX_CBRS_AUTOHIDE | AFX_CBRS_RESIZE;
	CRect rectDummy(0, 0, 0, 0);

	//const DWORD dwTreeStyle = WS_CHILD | WS_VISIBLE | TVS_HASLINES | TVS_LINESATROOT | TVS_HASBUTTONS;

	//tree.Create(dwTreeStyle, rectDummy, &bar, 1200);
	//bNameValid = strTemp.LoadString(IDS_FOLDERS);
	//ASSERT(bNameValid);
	//pOutlookBar->AddControl(&tree, strTemp, 2, TRUE, dwStyle);

	//calendar.Create(rectDummy, &bar, 1201);
	//bNameValid = strTemp.LoadString(IDS_CALENDAR);
	//ASSERT(bNameValid);
	//pOutlookBar->AddControl(&calendar, strTemp, 3, TRUE, dwStyle);
	strTemp = _T("Tamplate Tasks");
	DWORD defaultStyle = WS_CHILD | WS_VISIBLE | WS_CLIPSIBLINGS | WS_CLIPCHILDREN | CBRS_NOALIGN;
	if (!m_wndTemplateTasksPane.Create(strTemp, &bar, rectDummy, TRUE,
		ID_VIEW_TEMPLATETASKPANE, defaultStyle ))
	{
		TRACE0("�Ӽ� â�� ������ ���߽��ϴ�.\n");
		return FALSE; // ������ ���߽��ϴ�.
	}
	pOutlookBar->AddControl(&m_wndTemplateTasksPane, strTemp, 2, TRUE, dwStyle);

	bar.SetPaneStyle(bar.GetPaneStyle() | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC);

	pOutlookBar->SetImageList(theApp.m_bHiColorIcons ? IDB_PAGES_HC : IDB_PAGES, 24);
	pOutlookBar->SetToolbarImageList(theApp.m_bHiColorIcons ? IDB_PAGES_SMALL_HC : IDB_PAGES_SMALL, 16);
	pOutlookBar->RecalcLayout();

	BOOL bAnimation = theApp.GetInt(_T("OutlookAnimation"), TRUE);
	CMFCOutlookBarTabCtrl::EnableAnimation(bAnimation);

	bar.SetButtonsFont(&afxGlobalData.fontBold);

	return TRUE;
}

BOOL CMainFrame::CreateDockableBar()
{
	DWORD dwStyle = WS_CHILD | WS_VISIBLE | WS_CLIPSIBLINGS | WS_CLIPCHILDREN 
		| CBRS_LEFT | CBRS_FLOAT_MULTI;	
	if (!mSequenceDockable.Create( _T("Sequence") , this, CRect(0, 0, 200, 200), TRUE
		, ID_VIEW_SEQUENCEDOCKABLE, dwStyle) )
	{
		TRACE0("�Ӽ� â�� ������ ���߽��ϴ�.\n");
		return false; // ������ ���߽��ϴ�.
	}

	mSequenceDockable.EnableDocking(CBRS_ALIGN_ANY);
	

	if (!mSequenceModifyDockable.Create (_T("Source Code"), this, CRect (0, 0, 150, 150),
		TRUE /* Has gripper */, ID_VIEW_SEQUENCEMODIFYDOCKABLE,
		WS_CHILD | WS_VISIBLE | CBRS_BOTTOM | CBRS_FLOAT_MULTI,
		AFX_CBRS_REGULAR_TABS, AFX_CBRS_RESIZE | AFX_CBRS_AUTOHIDE))
	{
		TRACE0("Failed to create output bar\n");
		return -1;      // fail to create
	}

	DockPane( &mSequenceModifyDockable );
	DockPane( &mSequenceDockable );
	
	return true;
}

BOOL CMainFrame::CreateCaptionBar()
{
	if (!m_wndCaptionBar.Create(WS_CHILD | WS_VISIBLE | WS_CLIPSIBLINGS, this, ID_VIEW_CAPTION_BAR, -1, TRUE))
	{
		TRACE0("ĸ�� ǥ������ ������ ���߽��ϴ�.\n");
		return FALSE;
	}

	BOOL bNameValid;

	CString strTemp, strTemp2;
	bNameValid = strTemp.LoadString(IDS_CAPTION_BUTTON);
	ASSERT(bNameValid);
	m_wndCaptionBar.SetButton(strTemp, ID_TOOLS_OPTIONS, CMFCCaptionBar::ALIGN_LEFT, FALSE);
	bNameValid = strTemp.LoadString(IDS_CAPTION_BUTTON_TIP);
	ASSERT(bNameValid);
	m_wndCaptionBar.SetButtonToolTip(strTemp);

	bNameValid = strTemp.LoadString(IDS_CAPTION_TEXT);
	ASSERT(bNameValid);
	m_wndCaptionBar.SetText(strTemp, CMFCCaptionBar::ALIGN_LEFT);

	m_wndCaptionBar.SetBitmap(IDB_INFO, RGB(255, 255, 255), FALSE, CMFCCaptionBar::ALIGN_LEFT);
	bNameValid = strTemp.LoadString(IDS_CAPTION_IMAGE_TIP);
	ASSERT(bNameValid);
	bNameValid = strTemp2.LoadString(IDS_CAPTION_IMAGE_TEXT);
	ASSERT(bNameValid);
	m_wndCaptionBar.SetImageToolTip(strTemp, strTemp2);

	return TRUE;
}

// CMainFrame �޽��� ó����

void CMainFrame::OnViewCaptionBar()
{
	m_wndCaptionBar.ShowWindow(m_wndCaptionBar.IsVisible() ? SW_HIDE : SW_SHOW);
	RecalcLayout(FALSE);
}

void CMainFrame::OnUpdateViewCaptionBar(CCmdUI* pCmdUI)
{
	pCmdUI->SetCheck(m_wndCaptionBar.IsVisible());
}

void CMainFrame::OnViewSequencedockable()
{
	mSequenceDockable.ShowWindow(mSequenceDockable.IsVisible() ? SW_HIDE : SW_SHOW);
	RecalcLayout(FALSE);
}

void CMainFrame::OnUpdateViewSequencedockable(CCmdUI *pCmdUI)
{
	pCmdUI->SetCheck(mSequenceDockable.IsVisible());
}

void CMainFrame::OnOptions()
{
	CMFCRibbonCustomizeDialog *pOptionsDlg = new CMFCRibbonCustomizeDialog(this, &m_wndRibbonBar);
	ASSERT(pOptionsDlg != NULL);

	pOptionsDlg->DoModal();
	delete pOptionsDlg;
}


BOOL CMainFrame::DestroyWindow()
{
	GcObjectMessage info;
	info.mpObject = NULL;
	info.mpSender = this;
	SendMediateMessage( GTMG_SELECTOBJECT, &info );

	if( CFrameWndEx::DestroyWindow() == false )
		return false;

	GetObjectFactory()->RemvoeAllObject();
	//SendMediateMessage( GTMG_DESTORY, NULL );	
	GtToolEBM::ShutdownEBM();

	// ���������� ���� �Ƚ��� �ָ� ����
	CCDirector::sharedDirector()->end();
	CCDirector::sharedDirector()->mainLoop();
	CCDirector::destoryDirector();	
	return true;
}

void CMainFrame::ReceiveMediateMessage(gtuint messageIndex, GcMediateObjectMessage* pSanderInfo)
{
	switch( messageIndex )
	{
	case GTMG_DESTORY:
		mpObject = NULL;
		break;
	case GTMG_SELECTOBJECT:
		{
			mpObject = pSanderInfo->mpObject;
		}
		break;
	}
}


void CMainFrame::OnSaveObjectState()
{
	GetObjectFactory()->SaveObjects( true );
	if( mpObject )
		GetObjectFactory()->AddObject( mpObject );
	m_wndTemplateTasksPane.GetTemplateList().OnSaveObjectstate();
}