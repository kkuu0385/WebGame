#ifndef GNANIMATIONKEYMANAGER_H
#define GNANIMATIONKEYMANAGER_H
#include "GnAnimationKey.h"

class GnAnimationKeyManager : public GnMemoryObject
{
	GnDeclareDataStream;
public:
	class AniKey
	{
	public:
		AniKey();
		GnAnimationKey::eKeyType mKeyType;
		guint32 mNumKey;
		GnAnimationKey* mAnimationKeys;
		
	public:
		inline GnAnimationKey* GetAniKey() {
			return mAnimationKeys;
		}
	};

private:
	GnTPrimitiveArray<AniKey> mAnimationKeys;

public:
	GnAnimationKeyManager(){};
	virtual ~GnAnimationKeyManager();

public:
	gtuint GetAnimationKeySize() {
		return mAnimationKeys.GetSize();
	}
	AniKey* GetAnimationKey(gtuint uiIndex){
		return &mAnimationKeys.GetAt( uiIndex );
	}

	// �� ������ ���� ����
public:
	inline GnTPrimitiveArray<AniKey>* GetAnimationKeys() {
		return &mAnimationKeys;
	}
};

#endif // GNANIMATIONKEYMANAGER_H