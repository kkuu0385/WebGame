#pragma once

#include "resource.h"

class CGameDesignDoc;
class CGameDesignView : public CTabView
{
protected: // serialization������ ��������ϴ�.
	CGameDesignView();
	DECLARE_DYNCREATE(CGameDesignView)

public:
	virtual void OnInitialUpdate();
	void Save(LPCTSTR lpszPathName);
	void Load(LPCTSTR lpszPathName);

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.
	virtual void OnActivateView(CView* pView);

// Ư���Դϴ�.
public:
	CGameDesignDoc* GetDocument() const;

public:
	BOOL IsScrollBar () const {
		return TRUE;
	}


// �����Դϴ�.
public:
	virtual ~CGameDesignView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ������ �޽��� �� �Լ�
protected:
	afx_msg void OnFilePrintPreview();
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	DECLARE_MESSAGE_MAP()

public:
};

#ifndef _DEBUG  // GStageLevelDesignView.cpp�� ����� ����
inline CGameDesignDoc* CGameDesignView::GetDocument() const
   { return reinterpret_cast<CGameDesignDoc*>(m_pDocument); }
#endif

