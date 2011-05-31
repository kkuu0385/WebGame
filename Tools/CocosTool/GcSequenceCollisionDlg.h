#pragma once
#include "GcPropertyGridCtrl.h"
#include "GcAnimationKeyPropEntity.h"
#include "GcMediateObject.h"
#include "GcCollisionList.h"
#include "afxcmn.h"
#include "afxwin.h"
#include "Gc2DCollisionBoxPropEntity.h"

// GcSequenceCollisionDlg ��ȭ �����Դϴ�.

class GcSequenceCollisionDlg : public CDialogEx, public GcMediateObject
{
	DECLARE_DYNAMIC(GcSequenceCollisionDlg)

protected:
	GcCollisionList mCollisionList;
	CStatic mCollisionPropLocaton;
	GcPropertyGridCtrl mCollisionProp;
	Gc2DCollisionBoxPropEntity mCollisionPropEntity;

	Gt2DActor* mpActor;
	Gt2DSequence* mpSequence;
	
public:
	GcSequenceCollisionDlg(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~GcSequenceCollisionDlg();
	enum { IDD = IDD_GCSEQUENCECOLLISIONDLG };
	void ResetData(Gt2DActor* pActor, Gt2DSequence* pSequence);

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()

	virtual BOOL OnInitDialog();
	virtual BOOL OnNotify(WPARAM wParam, LPARAM lParam, LRESULT* pResult);
	virtual void ReceiveMediateMessage(gtuint messageIndex, GcMediateObjectMessage* pMessage);
};
