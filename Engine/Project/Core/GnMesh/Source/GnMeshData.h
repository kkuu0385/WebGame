#ifndef GNDATASTREAM_H
#define GNDATASTREAM_H

class GnDataStreamList : public GnList<GnDataStream*>
{
public:
	GnDataStreamList();
	void AddDataStream(GnDataStream* element);
	void RemoveAllStream();

private:
	gtuint mStride;
};

// ���ؽ� ���۸� ��������� Ŭ����
class GNMESH_ENTRY GnMeshData : public GnObject
{
	GnDeclareRTTI;
	GnDeclareFlags(guint8);
	GnDeclareStream;
public:
	enum 
	{
		ADD_DATASTREAM_MASK = 0x01,
	};

protected:
	GnDataStreamList mDataStreams;

public:
	inline GnMeshData()
	{
		SetAddDataStream( false );
	};
	virtual ~GnMeshData();

	// ���� �ʿ��� ���ؽ� ������ ���� �Ѵ�.
	GnDataStream* AddDataStream(const GnDataStream::eFormat format, guint32 uiVertexCount);
	GnDataStream* GetDataStream(const GnDataStream::eFormat format, guint8 uiIndex = 0);
	virtual GnDataStream* CreateDataStream(GnDataStream::eFormat format, guint32 vertexCount) = 0;

	inline GnDataStreamList& GetDataStreams()
	{
		return mDataStreams;
	}

	inline void Update()
	{
		UpdateData();
	}

protected:	
	// GnDataStream�� �߰� �ǰų� ���� �Ǹ� true�� �Ǿ� �����͸� ������Ʈ(UpdateData) �Ѵ�.
	inline bool IsAddDataStream()
	{
		return GetBit( ADD_DATASTREAM_MASK );
	}
	inline void SetAddDataStream(bool val)
	{
		SetBit( val, ADD_DATASTREAM_MASK );
	}

protected:
	virtual void UpdateData() = 0;
};

#endif // GNDATASTREAM_H