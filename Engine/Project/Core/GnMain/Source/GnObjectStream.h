#ifndef GNMODELSTREAM_H
#define GNMODELSTREAM_H
#include <GnTStringMap.h>
#include "GnStream.h"

class GnObjectStream : public GnStream
{
public:
	static const guint32 NULL_LINKID = UINT32_MAX - 1;

protected:
	GnTPrimitiveArray<GnObject*> mRootLevelObjects; // save, load ���
	GnTPrimitiveArray<GnObject*> mObjectLists; // save, load ���
	GnTObjectArray<GnSimpleString> mFixedStrings; // save, load ���
	GnTPrimitiveArray<guint32> mLinkIDs;	// load ���
	GnTPrimitiveArray<guint32> mMultiLinkIDBlocks;	// load ���
	GnTMap<const GnObject*, guint32> mRegObjects; // save ���
	gtuint mLinkIndex;
	gtuint mLinkBlockIndex;

public:
	GnObjectStream();
	virtual ~GnObjectStream(){};

	virtual bool Load(const gchar* pcFilePath);
	virtual bool Save(const gchar* pcFilePath);

	// ������ �����͸� ������ �����Ϳ� ���̵� ���� �ϱ� ���� mRegObjects�� ������Ʈ�� �Բ� linkID�� ����
	bool RegisterSaveObject(GnObject* pObject); // Save���
	bool RegisterFixedString(GnSimpleString& str); // Save���
	guint32 GetStringID(const GnSimpleString& str);
	void SaveFixedString(const GnSimpleString& str); // Save ���
	void LoadFixedString(GnSimpleString& str);

	GnObject* GetObjectFromLinkID(); // Load��
	guint32 LoadMultipleLinkIDs(); // Load��
	guint32 GetLinkID(const GnObject* pObject);

	inline gtuint GetObjectCount() {
		return mRootLevelObjects.GetSize();
	}

	inline GnObject* GetObject(gtuint uiIndex) {		
		return mRootLevelObjects.GetAt(uiIndex);
	}

	inline void InsertRootObjects(GnObject* pObject) {
		mRootLevelObjects.Add( pObject );
	}

	inline guint32 GetNumberOfLinkIDs()
	{
		GnAssert( mMultiLinkIDBlocks.GetSize() > mLinkBlockIndex );
		return mMultiLinkIDBlocks.GetAt( mLinkBlockIndex++ );
	}
	inline void LoadLinkID() {
		guint32 linkID = 0;
		LoadStream(linkID);
		mLinkIDs.Add(linkID);
	}

	inline void SaveLinkID(const GnObject* pObject) {
		guint32 linkID = GetLinkID(pObject);
		SaveStream(linkID);
	}

protected:
	bool LoadHeader();
	void RegisterObject();
	void SaveHeader();
	bool LoadRTTI();
	void SaveRTTI();
	void LoadFixedStrings();
	void SaveFixedStrings();
	void LoadRTTiString(gchar* pcStr);
	void SaveObject();
	void LinkObject();
	bool LoadObject();
	void SaveRootObject();
	bool LoadRootObject();

	void RemoveAllObjects();
	void ResetLoadDatas();
};

#endif // GNMODELSTREAM_H