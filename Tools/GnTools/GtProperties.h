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

#pragma once
#include "GtPropertyGridCtrl.h"
#include "GtCollectionEntities.h"
#include "GtSequenceListDlg.h"
#include "GtToolBarForm.h"
#include "GtEditorPropSheet.h"

class GnSMTextureAniCtrl;
class GtProperties : public GtToolBarForm
{
protected:	
	bool mModified;
	CComboBox m_wndObjectCombo;
	GtPropertyGridCtrl m_wndPropList;
	GtSequenceListCtrl mSequenceListCtrl;
	GtCollectionEntities* mpEntities;
	GtActorObjectPtr mpsCurrentObject;

// �����Դϴ�.
public:
	GtProperties();
	virtual ~GtProperties();
	void AdjustLayout();

public:
	inline GtPropertyGridCtrl& GetWndPropList() { return m_wndPropList; }
	virtual void ReceiveMediateMessage(gtuint messageIndex, GtMediateObjectMessage* pInfo);	
	void ChangeProperty(GtMediateObjectMessage* pInfo);
	void ChangeSequence(GtMediateObjectMessage* pInfo);

protected:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnExpandAllProperties();	
	afx_msg void OnSortProperties();	
	afx_msg void OnProperties1();	
	afx_msg void OnProperties2();	
	afx_msg void OnSetFocus(CWnd* pOldWnd);

	DECLARE_MESSAGE_MAP()

	void InitPropList();
	void SetPropListFont();
	LRESULT OnPropertyChanged(WPARAM wparam, LPARAM lparam);	
public:
	void OnSaveObjectstate();
};

