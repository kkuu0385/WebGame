#include "StdAfx.h"
#include "GcAnimationKeyPropEntity.h"
#include "GtAniKeyHelper.h"

GcAnimationKeyPropEntity::GcAnimationKeyPropEntity(void) : mpAniKeyManager(NULL)
{
	Init();
}


GcAnimationKeyPropEntity::~GcAnimationKeyPropEntity(void)
{
}

bool GcAnimationKeyPropEntity::Init()
{
	mUpdateEventSlot.Initialize( this, &GcAnimationKeyPropEntity::UpdateEvent );	

	CMFCPropertyGridProperty* pGroup = new CMFCPropertyGridProperty(_T("�ؽ��� �ִϸ��̼� ����"));
	mpProperty = pGroup;
	
	mpKeyTime = new GcPropertyGridProperty(_T("�̺�Ʈ �߻� �ð�"), 0.0f
		, _T("���� �ð��� �̺�Ʈ�� �߻��մϴ�"));
	mpKeyTime->SetData( MSG_KEYTIME );
	mpKeyTime->AllowEdit( false );
	pGroup->AddSubItem( mpKeyTime );

	mpTegID = new GcPropertyGridProperty(_T("�ε����� ����"), 0L
		, _T("�̺�Ʈ �߻��� ���� �ױ��� �ε����� �����մϴ�"));
	mpTegID->SetData( MSG_TEGID );
	mpTegID->SubscribeToUpdateEvent( &mUpdateEventSlot );
	pGroup->AddSubItem( mpTegID );

	return true;
}

bool GcAnimationKeyPropEntity::ParseToEntity(EntityData* pData)
{
	mpsSequence = (Gt2DSequence*)(GtObject*)pData->mpObject;
	if( mpsSequence == NULL || mpsSequence->GetSequence() == NULL )
		return false;

	ThisEntityData* thisData = (ThisEntityData*)pData;
	mpAniKeyManager = mpsSequence->GetSequence()->GetAnimationKeyManager();

	GnAnimationKeyManager::AniKey key;
	int aniKeysIndex = GetAniKey( GnAnimationKey::TEGIDKEY, mpAniKeyManager, key );	

	if( aniKeysIndex == -1 )
		return false;
	
	mAniKeyIndex = thisData->mAniKeyIndex;
	if( key.mNumKey <= (guint32)mAniKeyIndex  )
		return false;
	

	GnTegIDKey* tegKeys = (GnTegIDKey*)key.mAnimationKeys;
	GetKeyTimeProp()->SetValue( tegKeys[mAniKeyIndex].GetKeyTime() );
	GetTegIDProp()->SetValue( (long)tegKeys[mAniKeyIndex].GetTegID() );
	return true;
}

void GcAnimationKeyPropEntity::UpdateEvent(GcPropertyGridProperty* pChangedGridProperty)
{
	switch( pChangedGridProperty->GetData() )
	{
	case MSG_TEGID:
		{
			if( mpAniKeyManager == NULL )
				return;

			GnAnimationKeyManager::AniKey key;
			int aniKeysIndex = GetAniKey( GnAnimationKey::TEGIDKEY, mpAniKeyManager, key );	

			if( aniKeysIndex == -1 )
				return;

			if( key.mNumKey <= (guint32)mAniKeyIndex  )
				return;

			GnTegIDKey* tegKeys = (GnTegIDKey*)key.mAnimationKeys;
			int id = GetIntValue( GetTegIDProp()->GetValue() );
			tegKeys[mAniKeyIndex].SetTegID( (guint32)id );
		}
		break;
	default:
		return;
	}
	mpsSequence->SetModifed( true );
}

void GcAnimationKeyPropEntity::SetCurrentTime(float val)
{
	if( mpsSequence == NULL )
		return;
	GetKeyTimeProp()->SetValue( val );

	GnAnimationKeyManager::AniKey key;
	int aniKeysIndex = GetAniKey( GnAnimationKey::TEGIDKEY, mpAniKeyManager, key );	

	if( aniKeysIndex == -1 )
		return;

	if( key.mNumKey <= (guint32)mAniKeyIndex  )
		return;

	GnTegIDKey* tegKeys = (GnTegIDKey*)key.mAnimationKeys;
	tegKeys[mAniKeyIndex].SetKeyTime( val );
	mpsSequence->SetModifed( true );
}