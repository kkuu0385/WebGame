#ifndef GNDATASTREAMELEMENT_H
#define GNDATASTREAMELEMENT_H


class GNMESH_ENTRY GnDataStream : public GnMemoryObject
{
	GnDeclareDataStream;
public:
	enum eFormat
	{
		POSTION_STREAM,
		TEXTURE_STREAM,
		NORMAL_STREAM,
		COLOR_STREAM,
		SEMANTICS_DATASTREAM_MAX,
	};

	enum eLockType
	{
		LOCK_READ = 0x00000001,
		LOCK_WRITE = 0x00000002,
	};

protected:
	// mpVBBuffer�� mpIBBuffer�� �־��� �����͸� �����ϰ� �ִ� (�޸� �Ҵ���)
	void* mpLocalBuffer;
	// ���� ��Ʈ���� ���ؽ� �Ӽ� (POSTION_STREAM ���� TEXTURE_STREAM���� COLOR_STREAM ����)	
	// ������ �ѹ� ���� �Ǹ� ���� �� �� ����.
	eFormat mFormat; 
	guint32 mVertexCount;
	guint32 mOffset; // ���ؽ� �Ӽ��� ũ���� �����ϸ� ��	
	guint8 mNumStream; // ���ؽ����� ��Ʈ�� ��ȣ
	guint8 mUsageIndex;	// ���� ��Ʈ���� �ε��� ex) Tex1 Tex2
	bool mLocked; // ���� �� ����
	bool mUnshaped;	// ���� �ϼ� ���� ������ �ǹ�

public:
	GnDataStream(eFormat uFormat, guint32 uiCount);
	virtual ~GnDataStream();

	inline guint8 GetNumStream() const { return mNumStream; }
	inline void SetNumStream(guint8 val) { mNumStream = val; }
	inline guint8 GetUsageIndex() const { return mUsageIndex; }
	inline void SetUsageIndex(guint8 val) { mUsageIndex = val; }
	inline bool GetLocked() const { return mLocked; }
	inline void SetLocked(bool val) { mLocked = val; }
	inline guint32 GetOffset() { return mOffset; }
	inline void SetOffset(guint32 val) { mOffset = val; }
	inline eFormat GetFormat() { return mFormat; }

	inline gtuint GetStrideSize()
	{
		return GetStride(mFormat);
	}

	virtual gtuint GetStride(const eFormat format);
	inline void* Lock(guint8 uiLockMask) { return LockImp(uiLockMask); };
	inline void Unlock(guint8 uiLockMask) { UnlockImp(uiLockMask); };

	inline gtuint GetBufferSize() { return GetStrideSize() * GetVertexCount(); }
	inline guint32 GetVertexCount() { return mVertexCount; }
	inline void Resize(guint32 uiVertexCount)
	{
		Deallocate();
		mVertexCount = uiVertexCount;
		Allocate();
	}
	
protected:
	virtual void* LockImp(guint8 uiLockMask) = 0;
	virtual void UnlockImp(guint8 uiLockMask) = 0;

	virtual void Allocate() = 0;
	virtual void Deallocate() = 0;
};


#endif // GNDATASTREAMELEMENT_H