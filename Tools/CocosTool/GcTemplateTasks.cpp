// ./Ctrl/GcTemplateTasks.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "CocosTool.h"
#include "GcTemplateTasks.h"


// GcTemplateTasks

IMPLEMENT_DYNAMIC(GcTemplateTasks, GcTasksPane)

GcTemplateTasks::GcTemplateTasks()
{

}

GcTemplateTasks::~GcTemplateTasks()
{
}


BEGIN_MESSAGE_MAP(GcTemplateTasks, GcTasksPane)
	ON_WM_CREATE()
END_MESSAGE_MAP()



// GcTemplateTasks �޽��� ó�����Դϴ�.
int GcTemplateTasks::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (GcTasksPane::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  ���⿡ Ư��ȭ�� �ۼ� �ڵ带 �߰��մϴ�.
	//EnableNavigationToolbar (FALSE);
	//EnableWrapLabels (FALSE);
	//EnableOffsetCustomControls (FALSE);


	DWORD defaultStyle = WS_CHILD | WS_VISIBLE | WS_CLIPSIBLINGS | WS_CLIPCHILDREN | CBRS_NOALIGN;
	if (!mTemplateList.Create(_T("FDSF"), this, CRect(0, 0, 0, 0), TRUE, ID_CTRL_TEMPLATELIST,
		defaultStyle ))
	{
		TRACE0("�Ӽ� â�� ������ ���߽��ϴ�.\n");
		return FALSE; // ������ ���߽��ϴ�.
	}

	int groupIndex = AddGroup (_T("Template List"), FALSE, TRUE);
	AddWindow (groupIndex, mTemplateList.GetSafeHwnd (), 300);

	SetVisibleCaptionBar(true);
	return 0;
}
