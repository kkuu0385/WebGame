// GcTasksPane.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "CocosTool.h"
#include "GcTasksPane.h"


// GcTasksPane

IMPLEMENT_DYNAMIC(GcTasksPane, CMFCTasksPane)

GcTasksPane::GcTasksPane()
{

}

GcTasksPane::~GcTasksPane()
{
}


BEGIN_MESSAGE_MAP(GcTasksPane, CMFCTasksPane)
	ON_WM_CREATE()
END_MESSAGE_MAP()



// GcTasksPane �޽��� ó�����Դϴ�.





int GcTasksPane::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CMFCTasksPane::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  ���⿡ Ư��ȭ�� �ۼ� �ڵ带 �߰��մϴ�.

	return 0;
}

void GcTasksPane::SetVisibleCaptionBar(bool bShow)
{
	m_bHasGripper = false;
}