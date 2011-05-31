// GcTemplateListCtrl.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "CocosTool.h"
#include "GcTemplateListCtrl.h"


// GcTemplateListCtrl

IMPLEMENT_DYNAMIC(GcTemplateListCtrl, CListCtrl)

GcTemplateListCtrl::GcTemplateListCtrl() : mSelectedItem(-1)
{

}

GcTemplateListCtrl::~GcTemplateListCtrl()
{
}


BEGIN_MESSAGE_MAP(GcTemplateListCtrl, CListCtrl)
	ON_NOTIFY_REFLECT(NM_CLICK, &GcTemplateListCtrl::OnNMClick)
END_MESSAGE_MAP()



// GcTemplateListCtrl �޽��� ó�����Դϴ�.




void GcTemplateListCtrl::OnNMClick(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	*pResult = 0;
	mSelectedItem = pNMItemActivate->iItem;
	mSelectedItemText = GetItemText( pNMItemActivate->iItem, 0 );
}
