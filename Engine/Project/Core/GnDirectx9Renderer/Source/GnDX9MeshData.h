#ifndef GNDX9DATASTREAM_H
#define GNDX9DATASTREAM_H

#include "GnMeshData.h"

class GnDX9DataStream;
class GNDIRECTX9RENDERER_ENTRY GnDX9MeshData : public GnMeshData
{
protected:
	enum
	{
		MAX_DECLARATION_SIZE = 10,
	};
protected:
	LPDIRECT3DVERTEXDECLARATION9 mpDeclaration;
	
public:
	GnDX9MeshData();
	virtual ~GnDX9MeshData();

	virtual GnDataStream* CreateDataStream(GnDataStream::eFormat format, guint32 vertexCount);
	// IsChangedDataStream�� true�� GnDataStream�� ���۸� �ٽ� �����
	// IsAddDataStream�� true�̸� LPDIRECT3DVERTEXDECLARATION9�ٽ� �����ϰ� GnDataStream�� ���۵� �ٽ� �����
	virtual void UpdateData();

	inline LPDIRECT3DVERTEXDECLARATION9 GetDeclaration() const { return mpDeclaration; }
	

protected:
	// ������ ��Ʈ���� ���� 
	bool GetVertexElement9(GnDX9DataStream* pDataStream, D3DVERTEXELEMENT9& outVertexElement);

};

#endif // GNDX9DATASTREAM_H