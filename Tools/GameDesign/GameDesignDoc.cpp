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

// GameDesignDoc.cpp : CGameDesignDoc Ŭ������ ����
//

#include "stdafx.h"
// SHARED_HANDLERS�� �̸� ����, ����� �׸� �� �˻� ���� ó���⸦ �����ϴ� ATL ������Ʈ���� ������ �� ������
// �ش� ������Ʈ�� ���� �ڵ带 �����ϵ��� �� �ݴϴ�.
#ifndef SHARED_HANDLERS
#include "GameDesign.h"
#endif

#include "GameDesignDoc.h"
#include "GameDesignView.h"
#include <propkey.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CGameDesignDoc

IMPLEMENT_DYNCREATE(CGameDesignDoc, CDocument)

BEGIN_MESSAGE_MAP(CGameDesignDoc, CDocument)
END_MESSAGE_MAP()


// CGameDesignDoc ����/�Ҹ�

CGameDesignDoc::CGameDesignDoc()
{
	// TODO: ���⿡ ��ȸ�� ���� �ڵ带 �߰��մϴ�.

}

CGameDesignDoc::~CGameDesignDoc()
{
}

BOOL CGameDesignDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: ���⿡ ���ʱ�ȭ �ڵ带 �߰��մϴ�.
	// SDI ������ �� ������ �ٽ� ����մϴ�.

	return TRUE;
}

BOOL CGameDesignDoc::OnOpenDocument(LPCTSTR lpszPathName)
{
	if ( !CDocument::OnOpenDocument(lpszPathName) )
		return FALSE;

	mOpenPathName = lpszPathName;
	return TRUE;
}
BOOL CGameDesignDoc::OnSaveDocument(LPCTSTR lpszPathName)
{
	if ( !CDocument::OnSaveDocument( lpszPathName ) )
		return FALSE;

	GetActiveView()->Save( lpszPathName );
	return TRUE;
}

// CGameDesignDoc serialization

void CGameDesignDoc::Serialize(CArchive& ar)
{
	//GetActiveView()->Serialize( ar );
// 	if (ar.IsStoring())
// 	{
// 		// TODO: ���⿡ ���� �ڵ带 �߰��մϴ�.
// 		GetActiveView()->Serialize( ar );
// 	}
// 	else
// 	{
// 		// TODO: ���⿡ �ε� �ڵ带 �߰��մϴ�.
// 		GetActiveView()->Serialize( ar );
// 	}
}

#ifdef SHARED_HANDLERS

// ����� �׸��� �����մϴ�.
void CGameDesignDoc::OnDrawThumbnail(CDC& dc, LPRECT lprcBounds)
{
	// ������ �����͸� �׸����� �� �ڵ带 �����Ͻʽÿ�.
	dc.FillSolidRect(lprcBounds, RGB(255, 255, 255));

	CString strText = _T("TODO: implement thumbnail drawing here");
	LOGFONT lf;

	CFont* pDefaultGUIFont = CFont::FromHandle((HFONT) GetStockObject(DEFAULT_GUI_FONT));
	pDefaultGUIFont->GetLogFont(&lf);
	lf.lfHeight = 36;

	CFont fontDraw;
	fontDraw.CreateFontIndirect(&lf);

	CFont* pOldFont = dc.SelectObject(&fontDraw);
	dc.DrawText(strText, lprcBounds, DT_CENTER | DT_WORDBREAK);
	dc.SelectObject(pOldFont);
}

// �˻� ó���⸦ �����մϴ�.
void CGameDesignDoc::InitializeSearchContent()
{
	CString strSearchContent;
	// ������ �����Ϳ��� �˻� �������� �����մϴ�.
	// ������ �κ��� ";"�� ���еǾ�� �մϴ�.

	// ��: strSearchContent = _T("point;rectangle;circle;ole object;");
	SetSearchContent(strSearchContent);
}

void CGameDesignDoc::SetSearchContent(const CString& value)
{
	if (value.IsEmpty())
	{
		RemoveChunk(PKEY_Search_Contents.fmtid, PKEY_Search_Contents.pid);
	}
	else
	{
		CMFCFilterChunkValueImpl *pChunk = NULL;
		ATLTRY(pChunk = new CMFCFilterChunkValueImpl);
		if (pChunk != NULL)
		{
			pChunk->SetTextValue(PKEY_Search_Contents, value, CHUNK_TEXT);
			SetChunkValue(pChunk);
		}
	}
}

#endif // SHARED_HANDLERS

// CGameDesignDoc ����

#ifdef _DEBUG
void CGameDesignDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CGameDesignDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CGameDesignDoc ���
