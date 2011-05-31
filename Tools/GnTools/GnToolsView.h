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

// GnToolsView.h : CGnToolsView Ŭ������ �������̽�
//


#pragma once

#include <GnFrame.h>
#include "GtDrawMouseRectangle.h"

class CGnToolsView : public CView
{
private:
	GnFramePtr mGnFrame;
	UINT_PTR mTimerID;
	GtDrawMouseRectangle mDrawMouseRect;
	
	
protected: // serialization������ ��������ϴ�.
	CGnToolsView();
	DECLARE_DYNCREATE(CGnToolsView)

// Ư���Դϴ�.
public:
	CGnToolsDoc* GetDocument() const;

// �������Դϴ�.
public:
	virtual void OnDraw(CDC* pDC);  // �� �並 �׸��� ���� �����ǵǾ����ϴ�.
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);

	inline GnFrame* GetGnFrame() {
		return mGnFrame;
	}
	inline void SetGnFrame(GnFrame* val) {
		mGnFrame = val;
	}

// �����Դϴ�.
public:
	virtual ~CGnToolsView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ������ �޽��� �� �Լ�
protected:
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	DECLARE_MESSAGE_MAP()
public:
	virtual void OnInitialUpdate();

	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnSetFocus(CWnd* pOldWnd);
	afx_msg void OnAniPlay();
	afx_msg void OnAniPause();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
};

#ifndef _DEBUG  // GnToolsView.cpp�� ����� ����
inline CGnToolsDoc* CGnToolsView::GetDocument() const
   { return reinterpret_cast<CGnToolsDoc*>(m_pDocument); }
#endif

