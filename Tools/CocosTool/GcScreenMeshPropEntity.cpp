#include "StdAfx.h"
#include "GcScreenMeshPropEntity.h"
#include "GcPropertyGridNumberPair.h"
#include <memory>

GcScreenMeshPropEntity::GcScreenMeshPropEntity(void)
{
	Init();
}


GcScreenMeshPropEntity::~GcScreenMeshPropEntity(void)
{
}

bool GcScreenMeshPropEntity::Init()
{
	GcPropertyGridProperty* pGroup = NULL;
	pGroup = new GcPropertyGridProperty(_T("�޽� ����"));
	mpProperty = pGroup;

	GcPropertyGridProperty* pProp = NULL;
	pProp = new GcPropertyGridProperty(_T("���� �̸�"), (_variant_t) _T(""),
		_T("ĳ���� �̸��� �����մϴ�."));	
	pProp->AllowEdit( FALSE );
	pGroup->AddSubItem( pProp );

	std::auto_ptr<CMFCPropertyGridProperty> apSize(new GcPropertyGridNumberPair(_T("Mesh Scale Info")
		, 0, GINT_MAX, 0, GINT_MAX, 0, TRUE));
	apSize->AllowEdit( false );
	pProp = new GtBoundedNumberSubProp(_T("Height"), (COleVariant) 250l, 0, GINT_MAX, _T("Specifies the dialog's height"));
	pProp->EnableSpinControl( TRUE, 0, GINT_MAX );
	pProp->SetData( MSG_HEIGHT );
	apSize->AddSubItem( pProp );

	pProp = new GtBoundedNumberSubProp( _T("Width"), (COleVariant) 150l, 0, GINT_MAX, _T("Specifies the dialog's width"));
	pProp->EnableSpinControl( TRUE, 0, GINT_MAX );
	pProp->SetData( MSG_WIDTH );
	apSize->AddSubItem( pProp );

	pGroup->AddSubItem( apSize.release() );
	return true;
}

bool GcScreenMeshPropEntity::ParseToEntity(GtObject* pObject)
{
	//GtObject* gtObject = (GtObject*)pObject;
	//GnVector2 scale = gtObject->GetScale();
	//GtConvertString fileName = gtObject->GetFileName();
	//GetFileNameProp()->SetValue( fileName );
	//GetHeightProp()->SetValue( (COleVariant)(long)scale.y );
	//GetWidthProp()->SetValue( (COleVariant)(long)scale.x );
	return true;
}

bool GcScreenMeshPropEntity::ParseToObject(GtObject* pObject)
{
	//GtConvertString fileName = (CString)GetFileNameProp()->GetValue();
	//pObject->SetFileName( fileName.GetAciiString() );

	//int height = GetIntValue( GetHeightProp()->GetValue() );
	//int width = GetIntValue( GetWidthProp()->GetValue() );
	//pObject->ChanageScale( width, height );
	return true;
}