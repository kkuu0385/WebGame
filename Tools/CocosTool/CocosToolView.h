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

// CocosToolView.h : CCocosToolView Ŭ������ �������̽�
//

#pragma once


#include "GtCocos2DApp.h"
#include "GcMediateObject.h"
#include "afxwin.h"
#include "CategoryAnimationManager.h"
class CCocosToolView : public CFormView, GcMediateObject
{
	BOOL PreTranslateMessage(MSG* pMsg)
	{
		if(pMsg->message == WM_CHAR)
		{
			SendMessage(pMsg->message, pMsg->wParam, pMsg->lParam);
			return TRUE;
		}

		return CFormView::PreTranslateMessage(pMsg);
	}
protected: // serialization������ ��������ϴ�.
	CCocosToolView();
	DECLARE_DYNCREATE(CCocosToolView)

// Ư���Դϴ�.
public:
	enum { IDD = IDD_MAINRENDERVIEW };

private:
	GtCocos2DApp* mpApp;
	Gt2DActorPtr mpsActor;
	Gt2DSequencePtr mpsSequence;
	GnDrawPrimitivesPtr mpsDrawSequenceRect;
	CString mStrCurrentTime;
	float mfCurrentTime;
	float mBforeTime;
	float mfStartTime;
	float mfEndTime;
	float mfTick;
	float mfLastTick;
	CategoryAnimationManager mCategoryAnimation;
	GnLayerDrawPrimitives* mpDrawLayer;
	CMFCSpinButtonCtrl* mpSpinCurrentTime;
	int	mBackgroundMoveRange;
	UINT_PTR mTimerID;

protected:
	CStatic mLoactionRender;
	bool mModifyCollsionBoxsCheck;


public:
	void SetCurrentTime(float val);
	inline float GetCurrentTime() {
		return mfCurrentTime;
	}

protected:
	void SetCurrentTimeFromOnTimer();
	void Loadbackground(const gchar* pcFilePath);

public:
	virtual ~CCocosToolView();
	virtual void OnDraw(CDC* pDC);  // �� �並 �׸��� ���� �����ǵǾ����ϴ�.
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);

// ������ �޽��� �� �Լ�
protected:
	CCocosToolDoc* GetDocument() const;
	afx_msg void OnFilePrintPreview();
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	virtual void ReceiveMediateMessage(gtuint messageIndex, GcMediateObjectMessage* pSanderInfo);

	void ChageSequenceAniTime( Gt2DSequence* sequence );
	void AddCurrentActorToLayerDrawPprimitives();
	DECLARE_MESSAGE_MAP()
	

public:
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif
	virtual void OnInitialUpdate();
	virtual void DoDataExchange(CDataExchange* pDX);	
	virtual void PostNcDestroy();
	afx_msg void OnAniPlay();
	afx_msg void OnAniPause();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	
	afx_msg void OnModifyCollisionboxs();
	afx_msg void OnUpdateModifyCollisionboxs(CCmdUI *pCmdUI);
	afx_msg void OnAnicurrenttime();
	afx_msg void OnAnitimeslider();
	afx_msg void OnBtLoadbackground();
	virtual LRESULT WindowProc(UINT message, WPARAM wParam, LPARAM lParam);
	afx_msg void OnBackgroundMoverange();
};

#ifndef _DEBUG  // CocosToolView.cpp�� ����� ����
inline CCocosToolDoc* CCocosToolView::GetDocument() const
   { return reinterpret_cast<CCocosToolDoc*>(m_pDocument); }
#endif

