// ./Ctrl/GtTemplateTasksPane.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "GnTools.h"
#include "./Ctrl/GtTemplateTasksPane.h"


// GtTemplateTasksPane

IMPLEMENT_DYNAMIC(GtTemplateTasksPane, GtTasksPane)

GtTemplateTasksPane::GtTemplateTasksPane()
{

}

GtTemplateTasksPane::~GtTemplateTasksPane()
{
}


BEGIN_MESSAGE_MAP(GtTemplateTasksPane, GtTasksPane)
	ON_WM_CREATE()
END_MESSAGE_MAP()



// GtTemplateTasksPane �޽��� ó�����Դϴ�.
int GtTemplateTasksPane::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (GtTasksPane::OnCreate(lpCreateStruct) == -1)
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
