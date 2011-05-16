#pragma once
#include "gtpropertyentity.h"
#include "GtPropertyGridProperty.h"

class GtSequenceInfoPropEntity : public GtPropertyEntity
{
private:
	class MainPropertyGridProperty : public GtPropertyGridProperty
	{
	public:
		MainPropertyGridProperty(const CString& strName, const COleVariant& varValue);

	protected:
		virtual BOOL HasButton() const { return TRUE; }
		virtual void OnClickButton(CPoint point);
	};

public:
	enum eMessage
	{
		MSG_FILENAME = 50,
		MSG_SEQUENCEID,
	};

	GtDeclareEntity(GtSequenceInfoPropEntity);
public:
	GtSequenceInfoPropEntity(void);
	virtual ~GtSequenceInfoPropEntity(void);

	virtual bool Init();
	CString GetFileName();	
	CString GetCurrenctSequenceName();
	//���� ���� ���� �Ǿ��ִ� �����͸� �Է�
	void SetNames(LPCTSTR ptcSequenceName, LPCTSTR ptcFileName);

	// pObject ������ ������Ƽ�� �Է�
	virtual bool ParseToEntity(GtStreamObject* pObject);
	// ������Ƽ ������ pObject�� �Է�
	virtual bool ParseToObject(GtObject* pObject);

protected:
	CMFCPropertyGridProperty* GetSequenceFileNameProp() {
		return mpProperty->GetSubItem(1);
	}

	CMFCPropertyGridProperty* GetSequenceNameProp() {
		return mpProperty->GetSubItem(0);
	}
};

