#pragma once
#include "GtToolBarForm.h"
#include "GtTemplateListCtrl.h"

// �𵨸��̳�, ĳ����(����) ������Ʈ�� �̸��� �ҷ����� ��
class GnFrame;
class GtTemplateListForm : public GtToolBarForm
{
	DECLARE_DYNAMIC(GtTemplateListForm)

public:
	GtTemplateListForm();
	virtual ~GtTemplateListForm();

	struct TemplateListData
	{
		TemplateListData(){}
		TemplateListData( const gtchar* pcName, gint8 uiObjectType )
		{
			mObjectName = pcName;
			mObjectType = uiObjectType;
		}
		CString mObjectName;
		gint8 mObjectType;
	};	
	
protected:
	DECLARE_MESSAGE_MAP()
	int mLastSelectItem;
	GtTemplateListCtrl mListCtrl;
	CArray<TemplateListData> mTemplateList;

public:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnBtDeltemplate();
	afx_msg void OnBtNewtemplate();
	
	afx_msg void OnBtOpentemplate();
	
	// ���� ����� ���մ� ������Ʈ ����Ʈ�� ���� �ε� �Ѵ�.
	void SaveTemplateList(const gchar* filePath);
	void LoadTemplateList(const gchar* filePath);

protected:	
	virtual void ReciveNotiyfiMessage(WPARAM wParam, LPARAM lParam);
	GtObject* GetActorObject(CString itemText );
	void AddItem(CString itemName, gint8 iActortype, bool bSelected = false);
public:
	afx_msg void OnSaveObjectstate();
};


