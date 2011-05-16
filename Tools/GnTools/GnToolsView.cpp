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

// GnToolsView.cpp : CGnToolsView Ŭ������ ����
//

#include "stdafx.h"
// SHARED_HANDLERS�� �̸� ����, ����� �׸� �� �˻� ���� ó���⸦ �����ϴ� ATL ������Ʈ���� ������ �� ������
// �ش� ������Ʈ�� ���� �ڵ带 �����ϵ��� �� �ݴϴ�.
#ifndef SHARED_HANDLERS
#include "GnTools.h"
#endif

#include "GnToolsDoc.h"
#include "GnToolsView.h"
//#include "MainFrm.h"
#include <GnToolManager.h>
#include <GnFrame.h>
#include <GnTimer.h>
#include <GnSMTextureAniCtrl.h>
#include "GtWindowCreater.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#endif


IMPLEMENT_DYNCREATE(CGnToolsView, CView)

BEGIN_MESSAGE_MAP(CGnToolsView, CView)
	// ǥ�� �μ� ����Դϴ�.
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CGnToolsView::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
	ON_WM_SIZE()
	ON_WM_SETFOCUS()
	ON_COMMAND(ID_RBBT_PLAY, &CGnToolsView::OnAniPlay)
	ON_COMMAND(ID_RBBT_PAUSE, &CGnToolsView::OnAniPause)
	ON_WM_TIMER()
END_MESSAGE_MAP()

// CGnToolsView ����/�Ҹ�

CGnToolsView::CGnToolsView()
{
	// TODO: ���⿡ ���� �ڵ带 �߰��մϴ�.
	static int i = 0;
	mTimerID = i++;

}

CGnToolsView::~CGnToolsView()
{
}

BOOL CGnToolsView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs�� �����Ͽ� ���⿡��
	//  Window Ŭ���� �Ǵ� ��Ÿ���� �����մϴ�.

	return CView::PreCreateWindow(cs);
}

// CGnToolsView �׸���

void CGnToolsView::OnDraw(CDC* /*pDC*/)
{
	CGnToolsDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;
	
	if( GnToolManager::Singletone() )
		GnToolManager::Singletone()->Render(m_hWnd);
}


// CGnToolsView �μ�


void CGnToolsView::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL CGnToolsView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// �⺻���� �غ�
	return DoPreparePrinting(pInfo);
}

void CGnToolsView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: �μ��ϱ� ���� �߰� �ʱ�ȭ �۾��� �߰��մϴ�.
}

void CGnToolsView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: �μ� �� ���� �۾��� �߰��մϴ�.
}

void CGnToolsView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CGnToolsView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// CGnToolsView ����

#ifdef _DEBUG
void CGnToolsView::AssertValid() const
{
	CView::AssertValid();
}

void CGnToolsView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CGnToolsDoc* CGnToolsView::GetDocument() const // ����׵��� ���� ������ �ζ������� �����˴ϴ�.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CGnToolsDoc)));
	return (CGnToolsDoc*)m_pDocument;
}
#endif //_DEBUG


// CGnToolsView �޽��� ó����


void CGnToolsView::OnInitialUpdate()
{
	CView::OnInitialUpdate();

	mGnFrame = GnFrame::Create(m_hWnd);
	// TODO: ���⿡ Ư��ȭ�� �ڵ带 �߰� ��/�Ǵ� �⺻ Ŭ������ ȣ���մϴ�.
}


void CGnToolsView::OnSize(UINT nType, int cx, int cy)
{
	CView::OnSize(nType, cx, cy);
	if( mGnFrame )
		mGnFrame->RecreateRenderTarget(cx, cy);
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰��մϴ�.
}


void CGnToolsView::OnSetFocus(CWnd* pOldWnd)
{
	CView::OnSetFocus(pOldWnd);
}


void CGnToolsView::OnAniPlay()
{
	//if (AfxGetMainWnd()->IsKindOf(RUNTIME_CLASS(CMainFrame)))
	//{
		//GtProperties& properties = GetWindowCreater()->GetAniProperties();
		//GnSMTextureAniCtrl* textureAni = properties.CreateSMTextureAniCtrl();
		//if( textureAni )
		//{
		//	textureAni->SetLoop(true);
		//	mGnFrame->SetTimeCtrl(GnGetTicks(), textureAni);
		//}
	//}
	 SetTimer(mTimerID, 0, NULL);
}


void CGnToolsView::OnAniPause()
{	
	mGnFrame->Stop();
	KillTimer(mTimerID);
}


void CGnToolsView::OnTimer(UINT_PTR nIDEvent)
{
	CView::OnTimer(nIDEvent);
	
	float time = GnGetTicks();
	if( GnToolManager::Singletone() )
	{
		GnToolManager::Singletone()->Update( time, m_hWnd );
	}

	if( GnToolManager::Singletone() )
	{
		GnToolManager::Singletone()->Render(m_hWnd);
	}
}
