#ifndef GNDIRECTX9RENDERER_H
#define GNDIRECTX9RENDERER_H

#include <GnRenderer.h>
#include "GnDirectx9Define.h"
#include "GnDirectx9RendererType.h"
#include "GnDirectx9Renderer.h"

#pragma comment (lib, "d3dxof.lib")
#pragma comment (lib, "dxguid.lib")
#pragma comment (lib, "d3d9.lib")
#ifdef GNDEBUG
#pragma comment (lib, "d3dx9d.lib")
#else
#pragma comment (lib, "d3dx9.lib")
#endif


class GnDX92DBuffer;
class GnScreenMesh;
class GnCamera;
class GnDirectx9Renderer : public GnRenderer
{
protected:
	LPDIRECT3DDEVICE9 mpDevice;
	LPDIRECT3D9 mpD3D;
	GnList<GnDX92DBuffer*> mUseDisplayBuffers;	
	D3DCAPS9 mD3DCaps9;

public:
	GnDirectx9Renderer();
	virtual ~GnDirectx9Renderer();

	static GnDirectx9Renderer* Create(guint uiWidth, guint uiHeight, GnWindowHandle hwnd);
	static GnDirectx9Renderer* GetRenderer();
	inline LPDIRECT3D9 GetD3D()
	{
		return mpD3D;
	}
	inline LPDIRECT3DDEVICE9 GnDirectx9Renderer::GetDevice()
	{
		return mpDevice;
	}


	virtual void DoBeginFrame();	
	virtual void DoEndFrame();
	virtual void DoRenderFrame();
	// ������ ���õǾ� �ִ� ���� Ÿ���� ����� ���Ӱ� �����ϸ�
	// Ŭ���� ��忡 �°� ����̽��� ����۸� Ŭ�����Ѵ�.
	virtual void DoBeginRenderTarget(gtuint clearFlags);
	// ������ �� ������߿� ȭ�鿡 �׷�����(DoRenderFrame���� �׷���)���۸� �����صд�.
	virtual void DoEndRenderTarget();
	virtual void DoClearBuffer(gtuint clearFlags);
	virtual void DoRenderScreenMesh(GnScreenMesh* pMesh);
		
	virtual gtuint GetMaxSimultaneousRenderTargetBuffer();

	virtual void SetDynamicLight();
	virtual void SetCamera(GnCamera* cam);


	

protected:
	virtual bool Init(guint uiWidth, guint uiHeight, GnWindowHandle hwnd);
	virtual void Release();
	void CollectDevieceInfo();
};

GnSmartPointer(GnDirectx9Renderer);



#endif // GNDIRECTX9RENDERER_H