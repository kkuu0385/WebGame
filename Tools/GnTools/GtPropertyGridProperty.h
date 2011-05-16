#pragma once
class GtPropertyGridProperty  : public CMFCPropertyGridProperty
{
protected:
	bool mEnableGroupButton;
	int mGroupButtonWidth;
	CString mButtonName;

public:
	GtPropertyGridProperty(const CString& strGroupName, DWORD_PTR dwData = 0, BOOL bIsValueList = FALSE);

	GtPropertyGridProperty(const CString& strName, const COleVariant& varValue, LPCTSTR lpszDescr = NULL, DWORD_PTR dwData = 0,
		LPCTSTR lpszEditMask = NULL, LPCTSTR lpszEditTemplate = NULL, LPCTSTR lpszValidChars = NULL);
	virtual ~GtPropertyGridProperty(void);
	
	// �⺻���� �����Ѵ�.
	void SetDefaultValue();
	void SetEnableGroupButton(bool val, LPCTSTR pcName = NULL);

	// ��ư Ŭ�� �ȵǴ� �� ������ ��� �޾���
	virtual BOOL OnEdit(LPPOINT lptClick);
	// ����Ʈ �ڽ� ����Ŭ���ϸ� ��� ���� ���� ����Ʈ �ڽ� ���ԵǸ� �ٽ� ����� �ߵ�
	virtual BOOL OnDblClk(CPoint point);
	// �ؽ�Ʈ ���� �κп��� Ŀ�� �ٲ�°� �ȹٲ�� �ҷ��� �������̵�
	virtual BOOL OnSetCursor() const;	
	void AdjustButtonRect();

	// ���� ���̾�α׸� �������� ��ư�� �׸���
	void DrawButton(CDC* pDC);
	// ���� �����ϱ� ��ư�ʿ� ���콺����Ʈ�� �ִ��� Ȯ��
	// (��Ʈ �϶� ���� Ŭ���ϸ� Ȯ�� �Ǵ� ����Ⱑ �Ǵµ� �װ��� �������� ����)
	bool ButtonHitTest(CPoint point);

	inline bool GetEnableGroupButton() {
		return mEnableGroupButton;
	}	
	inline int GetGroupButtonWidth() {
		return mGroupButtonWidth;
	}
	inline void SetGroupButtonWidth(int val) {
		mGroupButtonWidth = val;
	}
};

