// GtTasksPane.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "GnTools.h"
#include "GtTasksPane.h"


// GtTasksPane

IMPLEMENT_DYNAMIC(GtTasksPane, CMFCTasksPane)

GtTasksPane::GtTasksPane()
{

}

GtTasksPane::~GtTasksPane()
{
}


BEGIN_MESSAGE_MAP(GtTasksPane, CMFCTasksPane)
	ON_WM_CREATE()
END_MESSAGE_MAP()



// GtTasksPane �޽��� ó�����Դϴ�.





int GtTasksPane::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CMFCTasksPane::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  ���⿡ Ư��ȭ�� �ۼ� �ڵ带 �߰��մϴ�.

	return 0;
}

void GtTasksPane::SetVisibleCaptionBar(bool bShow)
{
	m_bHasGripper = false;
}