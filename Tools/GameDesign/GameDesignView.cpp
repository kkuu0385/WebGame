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

// GameDesignView.cpp : CGameDesignView Ŭ������ ����
//

#include "stdafx.h"
// SHARED_HANDLERS�� �̸� ����, ����� �׸� �� �˻� ���� ó���⸦ �����ϴ� ATL ������Ʈ���� ������ �� ������
// �ش� ������Ʈ�� ���� �ڵ带 �����ϵ��� �� �ݴϴ�.
#ifndef SHARED_HANDLERS
#include "GameDesign.h"
#endif

#include "GameDesignDoc.h"
#include "GameDesignView.h"
#include "GStageLevelDesignView.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CGameDesignView

IMPLEMENT_DYNCREATE(CGameDesignView, CTabView)

BEGIN_MESSAGE_MAP(CGameDesignView, CTabView)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
END_MESSAGE_MAP()

// CGameDesignView ����/�Ҹ�

CGameDesignView::CGameDesignView()
{
	// TODO: ���⿡ ���� �ڵ带 �߰��մϴ�.

}

CGameDesignView::~CGameDesignView()
{
}

void CGameDesignView::DoDataExchange(CDataExchange* pDX)
{
	CTabView::DoDataExchange(pDX);
}
// void CGameDesignView::Serialize(CArchive& ar)
// {
// 	GtConvertString filePath = ar.m_strFileName.GetString();
// 	GnStream stream;
// 	if (ar.IsStoring())
// 	{	// storing code
// 		stream.Save( filePath.GetAciiString() );
// 		CMFCTabCtrl& tab = GetTabControl();
// 		for( gint i = 0 ; i < tab.GetTabsNum() ; i++ )
// 		{
// 			GDesignFormView* view =  (GDesignFormView*)tab.GetTabWnd( i );
// 			view->Save( &stream );
// 		}
// 	}
// 	else
// 	{	// loading code
// 		stream.Load( filePath.GetAciiString() );
// 		CMFCTabCtrl& tab = GetTabControl();
// 		for( gint i = 0 ; i < tab.GetTabsNum() ; i++ )
// 		{
// 			GDesignFormView* view =  (GDesignFormView*)tab.GetTabWnd( i );
// 			view->Load( &stream );
// 		}
// 	}
// }

void CGameDesignView::OnInitialUpdate()
{
	CTabView::OnInitialUpdate();

	CString name = GetDocument()->GetOpenPathName();
	if( name.GetLength() > 0 )
	{
		Load( name.GetString() );
	}
	else
	{
		GtConvertString convertName = GStageLevelDesignView::GetStaicName();
		AddView( RUNTIME_CLASS(GStageLevelDesignView), convertName.c_str(), 100 );
	}
}

void CGameDesignView::Save(LPCTSTR lpszPathName)
{
	GtConvertString filePath = lpszPathName;
	GnStream stream;
	if( stream.Save( filePath.GetAciiString() ) )
	{
		CMFCTabCtrl& tab = GetTabControl();
		gint32 tabCount = tab.GetTabsNum();

		stream.SaveStream( tabCount );
		for( gint32 i = 0 ; i < tabCount ; i++ )
		{
			GDesignFormView* view =  (GDesignFormView*)tab.GetTabWnd( i );
			gstring viewName = view->GetName();
			stream.SaveStream( viewName.c_str() );
		}

		for( gint i = 0 ; i < tabCount ; i++ )
		{
			GDesignFormView* view =  (GDesignFormView*)tab.GetTabWnd( i );		
			view->Save( &stream );
		}
	}	
}

void CGameDesignView::Load(LPCTSTR lpszPathName)
{
	GtConvertString filePath = lpszPathName;
	GnStream stream;
	if( stream.Load( filePath.GetAciiString() ) )
	{
		gint32 tabCount = 0;
		stream.LoadStream( tabCount );
		for( gint32 i = 0 ; i < tabCount ; i++ )
		{
			gchar viewName[256] = { 0, };
			gushort nameLen = 0;
			stream.LoadStream( nameLen );
			stream.LoadStreams( viewName, nameLen );
			CRuntimeClass* runtime = GDesignFormView::GetCreateFormViewFunction( viewName )();
			GtConvertString convertName = viewName;
			AddView( runtime, convertName.c_str(), 100 );
		}

		CMFCTabCtrl& tab = GetTabControl();
		for( gint i = 0 ; i < tabCount ; i++ )
		{
			GDesignFormView* view =  (GDesignFormView*)tab.GetTabWnd( i );
			view->Load( &stream );
		}
	}
}

void CGameDesignView::OnActivateView(CView* pView)
{
	CTabView::OnActivateView( pView );
// 	CFrameWnd* pFrame = AFXGetParentFrame(this);
// 	ASSERT_VALID(pFrame);
// 
// 	pFrame->SetActiveView( this );
}

void CGameDesignView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CGameDesignView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// CGameDesignView ����

#ifdef _DEBUG
void CGameDesignView::AssertValid() const
{
	CTabView::AssertValid();
}

void CGameDesignView::Dump(CDumpContext& dc) const
{
	CTabView::Dump(dc);
}

CGameDesignDoc* CGameDesignView::GetDocument() const // ����׵��� ���� ������ �ζ������� �����˴ϴ�.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CGameDesignDoc)));
	return (CGameDesignDoc*)m_pDocument;
}
#endif //_DEBUG


