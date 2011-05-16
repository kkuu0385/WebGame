#ifndef GNDX92DBUFFER_H
#define GNDX92DBUFFER_H

#include <Gn2DBackBuffer.h>

class GnDX92DBuffer : public Gn2DBackBuffer
{
private:
	static LPDIRECT3DSURFACE9 msCurrentBuffers[4];

protected:
	LPDIRECT3DSURFACE9 mpSurface;
	bool mIsDisplayBuffer;

public:
	inline GnDX92DBuffer(bool isDisplayBuffer = false) : mIsDisplayBuffer(isDisplayBuffer), mpSurface(NULL)
	{};
	virtual ~GnDX92DBuffer(){};

public:
	// ������ ����̽��� ���� �ߴ� ���� Ÿ���� msCurrentBuffers�� �ִٸ� NULL ��Ų��. 
	static void ClearRenderTarget(LPDIRECT3DDEVICE9 pDevice, gtuint numTarget);

	// msCurrentBuffers�� ���� ������ �����̽��� ���ٸ� ����̽��� Ÿ������ mpSurface�� �����ϰ�
	// msCurrentBuffers�� �����صд�.
	bool SetRenderTarget(LPDIRECT3DDEVICE9 pDevice, gtuint numTarget);	
	
	// �������� ������ ���������� Ȯ��.
	inline bool CanDisplay() { return mIsDisplayBuffer; }

	virtual void Release();	
};

#endif // GNDX92DBUFFER_H