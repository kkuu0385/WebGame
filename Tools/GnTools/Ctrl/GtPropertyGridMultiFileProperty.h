#pragma once
#include "GtOpenDialog.h"

class GtPropertyGridMultiFileProperty : public CMFCPropertyGridFileProperty
{
	DECLARE_DYNAMIC(GtPropertyGridMultiFileProperty)

public:

	GtPropertyGridMultiFileProperty(const CString& strName, const CString& strFolderName, bool bGroup = false,
		DWORD_PTR dwData = 0, LPCTSTR lpszDescr = NULL);
	GtPropertyGridMultiFileProperty(const CString& strName, BOOL bOpenFileDialog, const CString& strFileName,
		bool bGroup = false, LPCTSTR lpszDefExt = NULL,
		DWORD dwFlags = OFN_ALLOWMULTISELECT | OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT | OFN_NOCHANGEDIR,
		LPCTSTR lpszFilter = NULL, LPCTSTR lpszDescr = NULL, DWORD_PTR dwData = 0);
	virtual ~GtPropertyGridMultiFileProperty();

	// Overrides
public:
	virtual void OnClickButton(CPoint point);

	// ��ư Ŭ�� �ȵǴ� �� ������ ��� �޾���
	virtual BOOL OnEdit(LPPOINT lptClick);
	// ����Ʈ �ڽ� ����Ŭ���ϸ� ��� ���� ���� ����Ʈ �ڽ� ���ԵǸ� �ٽ� ����� �ߵ�
	virtual BOOL OnDblClk(CPoint point){ return FALSE; }

	virtual BOOL OnSetCursor() const;	
	virtual void AdjustButtonRect();	

	// ���� ���̾�α׸� �������� ��ư�� �׸���
	virtual void DrawButton(CDC* pDC);
	// ���� �����ϱ� ��ư�ʿ� ���콺����Ʈ�� �ִ��� Ȯ��
	// (��Ʈ �϶� ���� Ŭ���ϸ� Ȯ�� �Ǵ� ����Ⱑ �Ǵµ� �װ��� �������� ����)
	bool ButtonHitTest(CPoint point);
	
	CString GetPath(int iIndex);

};

