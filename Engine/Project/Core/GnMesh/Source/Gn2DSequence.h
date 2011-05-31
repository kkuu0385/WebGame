#ifndef Gn2DSequence_H
#define Gn2DSequence_H
#include "GnAnimationKeyManager.h"


class Gn2DSequence : public GnObject
{
	GnDeclareRTTI;
	GnDeclareStream;	
	GnDeclareFlags(gushort);
	enum
	{
		LOOP_MASK = 0x0001,
	};

protected:
	GnTObjectArray<Gn2DTextureAniPtr> mTextureAni;
	GnAnimationKeyManager mAnimationKeyManager;
	Gn2DMeshObjectPtr mpsTarget;
	Gn2DAVDataPtr mpsAVData;	
	guint32 mID;
	float mStartTime;
	float mEndTime;
	float mAccumulateDeltaTime;
	
public:
	Gn2DSequence();
	virtual ~Gn2DSequence();

	// �ִϸ��̼��� ���� Ÿ�� ��Ʈ�ѷ��� Ÿ���� ������ ������Ʈ�� �Ѱ��ְ�. ������Ʈ���� ��Ʈ�ѷ��� �����Ѵ�.	
	void SetTargetObject(GnObjectForm* pObject);
	void ResetTargetAV();

	virtual void Update(float fDeltaTime);
	virtual void Start(float fTime);
	virtual void Stop();	

	inline guint32 GetID() {
		return mID;
	}
	inline void SetID(guint32 val) {
		mID = val;
	}
	inline float GetStartTime() {
		return mStartTime;
	}
	inline void SetStartTime(float val) {
		mStartTime = val;
	}
	inline float GetEndTime() {
		return mEndTime;
	}
	inline void SetEndTime(float val) {
		mEndTime = val;
	}
	inline Gn2DAVData* GetAVData() {
		return mpsAVData;
	}
	inline void SetAVData(Gn2DAVData* val) {
		mpsAVData = val;
	}
	inline bool IsLoop() { return GetBit(LOOP_MASK); }
	inline void SetLoop(bool val) { SetBit(val, LOOP_MASK); }
	
	inline GnAnimationKeyManager* GetAnimationKeyManager() {
		return &mAnimationKeyManager;
	}

	// �������� ���� ����
public:
	inline GnTObjectArray<Gn2DTextureAniPtr>& GetTextureAnis() {
		return mTextureAni;
	}
};

#endif // Gn2DSequence_H