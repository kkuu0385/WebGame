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
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
	ON_WM_SIZE()
	ON_WM_SETFOCUS()
	ON_COMMAND(ID_RBBT_PLAY, &CGnToolsView::OnAniPlay)
	ON_COMMAND(ID_RBBT_PAUSE, &CGnToolsView::OnAniPause)
	ON_WM_TIMER()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
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

void CGnToolsView::OnDraw(CDC* pDC)
{
	CGnToolsDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	float time = GnGetTicks();
	if( GnToolManager::Singletone() )
	{
		GnToolManager::Singletone()->Update( time, m_hWnd );
	}

	if( GnToolManager::Singletone() )
	{
		GnToolManager::Singletone()->Render(m_hWnd);
	}

	if( pDC )
	{
		mDrawMouseRect.Draw( pDC );
	}


	//CDC* pdc = GetDC();
	//HGDIOBJ hOriginal = nullptr;
	//hOriginal = ::SelectObject( pdc, ::GetStockObject( DC_PEN ) );

	//HPEN hBlackPen = ::CreatePen( PS_SOLID, 3, 0 );
	//::SelectObject( pdc, hBlackPen );

	//::Ellipse( pdc, 300, 50, 500, 250 );

	//::DeleteObject( hBlackPen );
	//::SelectObject( pdc, hOriginal );
	//DrawLine(pDC,100,100,100,100, 50);
	
	//if( GnToolManager::Singletone() )
	//	GnToolManager::Singletone()->Render(m_hWnd);
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
}


void CGnToolsView::OnSize(UINT nType, int cx, int cy)
{
	CView::OnSize(nType, cx, cy);
	if( mGnFrame )
		mGnFrame->RecreateRenderTarget(cx, cy);
}


void CGnToolsView::OnSetFocus(CWnd* pOldWnd)
{
	CView::OnSetFocus(pOldWnd);
}


void CGnToolsView::OnAniPlay()
{
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
	 Invalidate(FALSE);
	//Graphics G(pDC->m_hDC);
	//Pen P( Color(255, 0, 0), 1.0f );
	//P.SetDashStyle( DashStyleDot );
	//Point pt1(100, 100);
	//Point pt2(1000, 100);
	//
	//G.DrawLine(&P, pt1, pt2);

	//pt1.X = 500;
	//pt1.Y = 0;
	//pt2.X = 500;
	//pt2.Y = 200;
	//G.DrawLine(&P, pt1, pt2);
}

void CGnToolsView::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.
	CView::OnLButtonDown(nFlags, point);

	mDrawMouseRect.SetDraw( true );
	mDrawMouseRect.SetStartPoint( point.x, point.y );
	mDrawMouseRect.SetEndPoint( 0, 0 );
}

void CGnToolsView::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.
	CView::OnLButtonUp( nFlags, point );

	mDrawMouseRect.SetDraw( false );	
}


void CGnToolsView::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.
	CView::OnMouseMove(nFlags, point);
	//ScreenToClient(&point);	
	if( mDrawMouseRect.GetDraw() )
	{
		Point startPt = mDrawMouseRect.GetStartPoint();
		Point endPt = mDrawMouseRect.GetEndPoint();
		if( startPt.X > point.x )
		{
			endPt.X = startPt.X;
			startPt.X = point.x;			
		}
		else
		{
			startPt.X = startPt.X;
			endPt.X = point.x;
		}

		if( startPt.Y > point.y )
		{
			endPt.Y = startPt.Y;
			startPt.Y = point.y;			
		}
		else
		{
			startPt.Y = startPt.Y;
			endPt.Y = point.y;
		}

		mDrawMouseRect.SetDrawRect( Rect(startPt.X, startPt.Y
			, abs(startPt.X - endPt.X), abs(startPt.Y - endPt.Y) ) );
	}
}

