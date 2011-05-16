// GtTemplateListCtrl.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "GnTools.h"
#include "GtTemplateListCtrl.h"


// GtTemplateListCtrl

IMPLEMENT_DYNAMIC(GtTemplateListCtrl, CListCtrl)

GtTemplateListCtrl::GtTemplateListCtrl() : mSelectedItem(-1)
{

}

GtTemplateListCtrl::~GtTemplateListCtrl()
{
}


BEGIN_MESSAGE_MAP(GtTemplateListCtrl, CListCtrl)
	ON_NOTIFY_REFLECT(NM_CLICK, &GtTemplateListCtrl::OnNMClick)
END_MESSAGE_MAP()



// GtTemplateListCtrl �޽��� ó�����Դϴ�.




void GtTemplateListCtrl::OnNMClick(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	*pResult = 0;
	mSelectedItem = pNMItemActivate->iItem;
	mSelectedItemText = GetItemText( pNMItemActivate->iItem, 0 );
}
