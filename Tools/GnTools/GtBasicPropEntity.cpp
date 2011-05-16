#include "StdAfx.h"
#include "GtBasicPropEntity.h"


GtBasicPropEntity::GtBasicPropEntity(void)
{
	Init();
}


GtBasicPropEntity::~GtBasicPropEntity(void)
{
}

bool GtBasicPropEntity::Init()
{
	CMFCPropertyGridProperty* pGroup = new CMFCPropertyGridProperty(_T("�⺻ ����"));
	mpProperty = pGroup;
	
	CMFCPropertyGridProperty* pProp = NULL;
	pProp = new CMFCPropertyGridProperty(_T("������Ʈ �̸�"), (_variant_t) _T(""),
		_T("ĳ���� �̸��� �����մϴ�."));	
	pProp->SetData( MSG_OBJECTNAME );

	pGroup->AddSubItem(pProp);
	
	pProp = new CMFCPropertyGridProperty(_T("������Ʈ ����"), (_variant_t) _T("2D ĳ����"),
		_T("ĳ���� �̸��� �����մϴ�."));
	pProp->AllowEdit( FALSE );
	pProp->SetData( MSG_OBJECTTYPE );

	pGroup->AddSubItem(pProp);

	pProp = new CMFCPropertyGridProperty(_T("���� �̸�"), (_variant_t) _T(""),
		_T("���� �̸��� �����մϴ�."));	
	pProp->SetData( MSG_FILENAME );

	pGroup->AddSubItem(pProp);

	//static const TCHAR szFilter[] = _T("Image (*.GAT, *.GAA, *.GM) | *.GAT;*.GAA;*.GM | All Files(*.*)|*.*||");
	//pProp = new CMFCPropertyGridFileProperty(_T("���� ���"), TRUE, _T(""), _T(""),
	//	OFN_HIDEREADONLY | OFN_READONLY, szFilter, _T("���� ���õ� ���� ���� �̸� �Դϴ�."));
	//pGroup->AddSubItem(pProp);

	pProp = new CMFCPropertyGridProperty( _T("�ε��� ��ȣ"), (_variant_t) 0,
		_T("ĳ���� �ε����� �����մϴ�."), 0 );
	pProp->SetData( MSG_OBJECTINDEX );
	pProp->EnableSpinControl( TRUE, 0, 500000 );

	pGroup->AddSubItem(pProp);

	return true;
}

CString GtBasicPropEntity::GetObjectName()
{
	return mpProperty->GetSubItem( BASIC_OBJECTNAME )->GetValue();
}

CString GtBasicPropEntity::GetObjectFileName()
{
	return mpProperty->GetSubItem( BASIC_FILENAME )->GetValue();
}

gtint GtBasicPropEntity::GetObjectIndex()
{
	const COleVariant& var = mpProperty->GetSubItem( BASIC_INDEX )->GetValue();
	return GetIntValue( var );
}

bool GtBasicPropEntity::ParseToEntity(GtStreamObject* pObject)
{
	GtObject* gtObject = (GtObject*)pObject;
	GnAssert( gtObject && gtObject->GetObjectName() );
	GtCString name = gtObject->GetObjectName();
	CMFCPropertyGridProperty* gridPrperty = mpProperty->GetSubItem( BASIC_OBJECTNAME );
	gridPrperty->SetValue( name.GetString() );
	
	SetObjectFileName( gtObject );
	SetObjectType( gtObject );

	gridPrperty = GetIndexProp();
	gridPrperty->SetValue(  (_variant_t) gtObject->GetIndex() );
	return true;
}

bool GtBasicPropEntity::ParseToObject(GtObject* pObject)
{
	GtCString name = GetObjectName();
	pObject->SetObjectName( name.GetAciiString() );

	name = GetObjectFileName();	
	switch( pObject->GetType() )
	{
	case GtObject::GTOBJECTTYPE:
		{
			pObject->SetFileName( name.GetAciiString() );
		}
		break;
	case GtActorObject::GTPLANEACTORTYPE:
		{
			GtActorObject* actorObject = (GtActorObject*)pObject;
			actorObject ->SetGATFileName( name.GetAciiString() );
		}		
		break;
	}

	pObject->SetIndex( (gint32)GetObjectIndex() );
	return true;
}

void GtBasicPropEntity::SetObjectType(GtObject* pObject)
{
	CMFCPropertyGridProperty* prop = GetTypeProp();
	switch( pObject->GetType() )
	{
	case GtObject::GTOBJECTTYPE:
		{
			prop->SetValue( _T( "2D ��" ) );			
		}
		break;
	case GtActorObject::GTPLANEACTORTYPE:
		{
			prop->SetValue( _T( "2D ĳ����" ) );
		}		
		break;
	}
}

void GtBasicPropEntity::SetObjectFileName(GtObject* pObject)
{
	GtCString name;
	CMFCPropertyGridProperty* prop = GetFileNameProp();
	switch( pObject->GetType() )
	{
	case GtObject::GTOBJECTTYPE:
		{
			name = pObject->GetFileName() == NULL ? "" : pObject->GetFileName();	
			if( name.Find( _T(".gm") ) == -1 )
				name += _T(".gm");
		}
		break;
	case GtActorObject::GTPLANEACTORTYPE:
		{
			GtActorObject* actorObject = (GtActorObject*)pObject;
			name = actorObject ->GetGATFileName() == NULL ? "" : actorObject ->GetGATFileName();
			if( name.Find( _T(".gat") ) == -1 )
				name += _T(".gat");
		}		
		break;
	}
	prop->SetValue( name.GetString() );
}