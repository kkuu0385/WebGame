#pragma once

class GtObject : public GnSmartObject
{
	GnSimpleString mObjectName;
	bool mNewItem; // ������ ���� ������� ������Ʈ���� Ȯ��	
	bool mModifed;

public:
	GtObject(void);
	~GtObject(void);

	virtual gint8 GetType() {
		return GINT8_MAX;
	}
	virtual bool SaveData(const gchar* pcBasePath = NULL) { return false; }
	virtual bool LoadData() { return false; }
	virtual bool CreateData() { return false; }

	inline bool IsNewItem() {
		return mNewItem;
	}
	inline void SetNewItem(bool bNewItem) {
		mNewItem = bNewItem;
	}
	inline bool IsModifed() {
		return mModifed;
	}
	inline void SetModifed(bool val) {
		mModifed = val;
	}
	inline const gchar* GetObjectName() {
		return mObjectName;
	}
	virtual void SetObjectName(const gchar* pcVal);
		
};

GnSmartPointer(GtObject);