#pragma once
#include "GcToolBarDockable.h"
#include "GcTemplateListCtrl.h"
#include "GcTemplateDockable.h"
// �𵨸��̳�, ĳ����(����) ������Ʈ�� �̸��� �ҷ����� ��
class GnFrame;
class GcEffectTemplateDockable : public GcTemplateDockable
{
public:
	GcEffectTemplateDockable();
	virtual ~GcEffectTemplateDockable();

protected:
	Gt2DActorPtr mpsCurrentObject;

protected:	
	virtual void ReciveNotiyfiMessage(WPARAM wParam, LPARAM lParam);	
	Gt2DActor* GetActorObject(CString itemText );
	void SelectItem(int iIndex);

public:
	afx_msg void OnSaveObjectstate();
};


