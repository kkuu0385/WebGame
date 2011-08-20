#include "StdAfx.h"
#include ".\proptreedlginfo.h"

CPropTreeDlgInfo::CPropTreeDlgInfo(void)
{
}

CPropTreeDlgInfo::~CPropTreeDlgInfo(void)
{
}
BEGIN_MESSAGE_MAP(CPropTreeDlgInfo, CDialog)
	ON_WM_PAINT()
END_MESSAGE_MAP()
/////////////////////////////////////////////////////////////////////////////
// CPropTreeInfo message handlers

void CPropTreeDlgInfo::SetPropOwner(CPropTree* pProp)
{
	m_pProp = pProp;
}
void CPropTreeDlgInfo::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰��մϴ�.
	// �׸��� �޽����� ���ؼ��� CPropertyPage::OnPaint()��(��) ȣ������ ���ʽÿ�.
	if ( this->GetSafeHwnd() != NULL )
	{
		CBrush test;
		CRect  rect;
		test.CreateSolidBrush(RGB(0xDD, 0x87, 0xFA));
		GetClientRect(&rect);
		dc.SelectObject(&test);
		dc.Rectangle(-1,-1,rect.Width()+1,rect.Height()+1);
		dc.SetBkMode(TRANSPARENT);

	}
}
