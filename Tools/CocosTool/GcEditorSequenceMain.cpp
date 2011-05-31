// GcEditorSequenceMain.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "CocosTool.h"
#include "GcEditorSequenceMain.h"
#include "afxdialogex.h"


// GcEditorSequenceMain ��ȭ �����Դϴ�.

IMPLEMENT_DYNAMIC(GcEditorSequenceMain, GcEditorPropertyPage)

GcEditorSequenceMain::GcEditorSequenceMain() : GcEditorPropertyPage(GcEditorSequenceMain::IDD)
{

}

GcEditorSequenceMain::~GcEditorSequenceMain()
{
}

void GcEditorSequenceMain::DoDataExchange(CDataExchange* pDX)
{
	GcEditorPropertyPage::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_ET_EDITOR_SEQUENCENAME, mEtSequenceName);
	DDX_Control(pDX, IDC_ET_EDITOR_SEQUENCEFILENAME, mEtSequenctFileName);
	DDX_Control(pDX, IDC_ET_EDITOR_SEQUENCEINDEX, mEtID);
}


BEGIN_MESSAGE_MAP(GcEditorSequenceMain, GcEditorPropertyPage)
	ON_EN_CHANGE(IDC_ET_EDITOR_SEQUENCENAME, &GcEditorSequenceMain::OnEnChangeSequencename)
	ON_EN_CHANGE(IDC_ET_EDITOR_SEQUENCEFILENAME, &GcEditorSequenceMain::OnChangeSequencefilename)
	ON_EN_CHANGE(IDC_ET_EDITOR_SEQUENCEINDEX, &GcEditorSequenceMain::OnChangeSequenceindex)
END_MESSAGE_MAP()


BOOL GcEditorSequenceMain::OnInitDialog()
{
	GcEditorPropertyPage::OnInitDialog();
	return TRUE;
}

void GcEditorSequenceMain::OnEnChangeSequencename()
{
	CString strTemp;	
	mEtSequenceName.GetWindowText( strTemp );

	GtConvertString strName = strTemp.GetString();
	mpSequence->SetObjectName( strName.GetAciiString() );
	CheckEnableOKButton();
}

void GcEditorSequenceMain::OnChangeSequencefilename()
{
}

void GcEditorSequenceMain::OnChangeSequenceindex()
{
	guint32 sequenceID = 1;
	CString strName;
	mEtID.GetWindowText( strName );
	_stscanf_s( strName, _T("%d"), &sequenceID );
	mpSequence->GetSequence()->SetID( sequenceID );
	CheckEnableOKButton();
}

bool GcEditorSequenceMain::CheckEnableButton()
{
	if( GcEditorPropertyPage::CheckEnableButton() == false )
		return false;

	GtConvertString aniName = mpSequence->GetObjectName();
	if( aniName.length() <= 0 )
		return false;	

	if( mpSequence->GetSequence()->GetID() == GUINT32_MAX )
		return false;

	GnActorTool* actorTool = mpActorObject->GetActorTool();
	GnActorTool::SequenceInfo* info = NULL;
	if( actorTool->GetSequenceInfo( mpSequence->GetSequence()->GetID(), info ) )
	{
		return false;
	}
	return true;
}

void GcEditorSequenceMain::OnOK()
{
	// TODO: ���⿡ Ư��ȭ�� �ڵ带 �߰� ��/�Ǵ� �⺻ Ŭ������ ȣ���մϴ�.

	SetFileName();
	GcEditorPropertyPage::OnOK();
}

void GcEditorSequenceMain::SetFileName()
{
	CString tempName;
	mEtSequenctFileName.GetWindowText( tempName );
	if( tempName.IsEmpty() )
	{
		mEtSequenceName.GetWindowText( tempName );
	}

	int pos = tempName.Find( _T(".") );
	if( pos == -1 )
	{
		tempName += _T(".ga");
	}

	GtConvertString strFolderName = mpObject->GetObjectName();
	GtConvertString strName = strFolderName;
	strName += _T( "\\" );
	strName += tempName.GetString();	
	mpSequence->SetFileName( strName.GetAciiString() );
}
