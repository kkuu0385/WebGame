#ifndef GNRENDERER_H
#define GNRENDERER_H

class GnRenderTarget;
class GnScreenMesh;
class GnCamera;
class GNMAIN_ENTRY GnRenderer : public GnSmartObject
{
public:
	enum eClearMode
	{
		CLEAR_NONE,
		CLEAR_ALL,
	};
protected:
	static GnRenderer* mpRenderer;
	// ��� ���� ���������� ���� - �⺻ ����Ÿ�� ����
	GnRenderTarget* mpDefaultRenderTarget;
	// ���� �����ϱ����� BeginRenderTarget �Լ����� ����
	GnRenderTarget* mpCurrentRenderTarget;	
	GnColorA mBackgroundColor;

public:
	GnRenderer();
	virtual ~GnRenderer();
	
	static GnRenderer* GetRenderer();

	void BeginFrame();	
	void EndFrame();
	void RenderFrame();
	void BeginRenderTarget(GnRenderTarget* renderTarget, gtuint clearFlags = CLEAR_ALL);
	void BeginDefaultRenderTarget(gtuint clearFlags = CLEAR_ALL);
	void EndRenderTarget();
	void ClearBuffer(gtuint clearFlags);
	void RenderScreenMesh(GnRenderObject* pMesh);

	virtual void DoBeginFrame() = 0;
	virtual void DoRenderFrame() = 0;
	virtual void DoEndFrame() = 0;
	virtual void DoBeginRenderTarget(gtuint clearFlags) = 0;
	virtual void DoEndRenderTarget() = 0;	
	virtual void DoClearBuffer(gtuint clearFlags) = 0;
	virtual void DoRenderScreenMesh(GnScreenMesh* pMesh) = 0;
	

	//�� ����Ÿ�ٿ� ��� ���۰� �������� Ȯ��
	virtual gtuint GetMaxSimultaneousRenderTargetBuffer() = 0;

	virtual void SetCamera(GnCamera* cam) = 0;

	inline GnRenderTarget* GetDefaultRenderTarget()
	{
		return mpDefaultRenderTarget;
	}
	inline GnRenderTarget* GetCurrentRenderTarget() const
	{
		return mpCurrentRenderTarget;
	}
	inline void GetBackgroundColor(GnColorA& outVal) const
	{
		outVal = mBackgroundColor;
	}
	inline void SetBackgroundColor(GnColorA& val)
	{
		mBackgroundColor = val;
	}
};

GnSmartPointer(GnRenderer);


#endif // GNRENDERER_H
