#include "StdAfx.h"
#include "CocosTool.h"
#include "GcSequenceInfoPropEntity.h"
//#include "GtWindowCreater.h"


GcSequenceInfoPropEntity::MainPropertyGridProperty::MainPropertyGridProperty(const CString& strName, const COleVariant& varValue)
	: GcPropertyGridProperty(strName, varValue)
{
}

void GcSequenceInfoPropEntity::MainPropertyGridProperty::OnClickButton(CPoint /*point*/)
{
	//GtProperties& prop = GetWindowCreater()->GetAniProperties();
	//if( prop.IsVisible() == false )
	//	prop.ShowPane(true, false, true);
}

GcSequenceInfoPropEntity::GcSequenceInfoPropEntity(void)
{
	Init();
}


GcSequenceInfoPropEntity::~GcSequenceInfoPropEntity(void)
{
}

bool GcSequenceInfoPropEntity::Init()
{
	MainPropertyGridProperty* pGroup = new MainPropertyGridProperty( _T("������ ����"), _T( "value")  );
	pGroup->SetEnableGroupButton( true, _T( "������ ����") );
	mpProperty = pGroup;

	CMFCPropertyGridProperty* pProp = new CMFCPropertyGridProperty( _T("������ ���̵�"), _T(""), _T("ĳ���� �ִϸ��̼�") );
	//for( int i = 0 ; i < 20 ; i++ )
	//{
	//	pProp->AddOption(_T("None"), false);
	//	pProp->AddOption(_T("Thin"), false);
	//	pProp->AddOption(_T("Resizable"), false);
	//	pProp->AddOption(_T("Dialog Frame"), false);
	//}
	pProp->SetData( MSG_SEQUENCEID );
	pProp->AllowEdit(FALSE);
	pGroup->AddSubItem(pProp);

	pProp = new CMFCPropertyGridProperty( _T("���� �̸�"), (_variant_t) _T(""),
		_T("�ִϸ��̼� ���� �̸�") );
	pProp->AllowEdit( FALSE );
	pProp->SetData( MSG_FILENAME );
	pGroup->AddSubItem(pProp);
	return true;
}

CString GcSequenceInfoPropEntity::GetFileName()
{
	COleVariant rVariant = GetSequenceFileNameProp()->GetValue();
	VARIANT v = rVariant.Detach();
	GnAssert(v.vt == VT_BSTR);
	CString str = OLE2T(v.bstrVal);
	return str;
}

void GcSequenceInfoPropEntity::SetNames(LPCTSTR ptcSequenceName, LPCTSTR ptcFileName)
{
	GetSequenceNameProp()->AddOption( ptcSequenceName, false );
	GetSequenceFileNameProp()->AddOption( ptcFileName, false );
}

CString GcSequenceInfoPropEntity::GetCurrenctSequenceName()
{
	COleVariant rVariant = GetSequenceNameProp()->GetValue();
	VARIANT v = rVariant.Detach();
	GnAssert(v.vt == VT_BSTR);
	CString str = OLE2T(v.bstrVal);
	return str;
}

bool GcSequenceInfoPropEntity::ParseToEntity(GtObject* pObject)
{
	//Gt2DActor* actorObject = (Gt2DActor*)pObject;
	//GnAssert( actorObject->GetType() == Gt2DActor::OBJECT_TYPE );
	//
	//guint optionCount = actorObject->GetLoadedSequenceCount();

	//if( optionCount <= 0 )
	//	return true;

	//CMFCPropertyGridProperty* sequenceFiles = GetSequenceFileNameProp();
	//CMFCPropertyGridProperty* sequenceNames = GetSequenceNameProp();	
	//
	//for( guint i = 0; i < optionCount ; i++ )
	//{
	//	GtConvertString names = actorObject->GetSequenceFileName( i );
	//	sequenceFiles->AddOption( names.GetWideString() );
	//	names = actorObject->GetSequenceName( i );
	//	sequenceNames->AddOption( names.GetWideString() );
	//}
	return true;
}

bool GcSequenceInfoPropEntity::ParseToObject(GtObject* pObject)
{
	//Gt2DActor* actor = GnDynamicCast( Gt2DActor, pObject );
	//GnAssert( actor );
	//GnAssert( GetSequenceNameProp() );
	//
	//CMFCPropertyGridProperty* sequenceFiles = GetSequenceFileNameProp();
	//CMFCPropertyGridProperty* sequenceNames = GetSequenceNameProp();	
	//int optionCount = sequenceNames->GetOptionCount();

	//actor->RemoveAllNames();
	//actor->SetSequenceCount( optionCount  );

	//for( int i = 0 ; i < optionCount ; i++ )
	//{
	//	GtConvertString name =  sequenceNames->GetOption( i );
	//	GtConvertString filename = sequenceFiles->GetOption( i );
	//	actor->AddNewSequence(name.GetAciiString(), filename.GetAciiString());
	//}
	return true;
}