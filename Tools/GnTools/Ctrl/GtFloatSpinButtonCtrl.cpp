// GtFloatSpinButtonCtrl.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "GnTools.h"
#include "GtFloatSpinButtonCtrl.h"
#define AFX_UM_UPDATESPIN (WM_USER + 101)

// GtFloatSpinButtonCtrl

IMPLEMENT_DYNAMIC(GtFloatSpinButtonCtrl, CMFCSpinButtonCtrl)

GtFloatSpinButtonCtrl::GtFloatSpinButtonCtrl() : mDelta(0.0f)
{

}

GtFloatSpinButtonCtrl::~GtFloatSpinButtonCtrl()
{
}


BEGIN_MESSAGE_MAP(GtFloatSpinButtonCtrl, CMFCSpinButtonCtrl)
	ON_NOTIFY_REFLECT(UDN_DELTAPOS, &GtFloatSpinButtonCtrl::OnDeltapos)
END_MESSAGE_MAP()



// GtFloatSpinButtonCtrl �޽��� ó�����Դϴ�.




void GtFloatSpinButtonCtrl::OnDeltapos(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMUPDOWN pNMUpDown = reinterpret_cast<LPNMUPDOWN>(pNMHDR);
	*pResult = 0;
	float fDelta = (float)pNMUpDown->iDelta;
	mDelta += fDelta / 1000;	
	GetParent()->PostMessage(AFX_UM_UPDATESPIN);
}
