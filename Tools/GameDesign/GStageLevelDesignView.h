#pragma once
#include "afxwin.h"
#include "GGridCtrl.h"
#include "GDesignFormView.h"
#include "GStageLevel.h"

class GStageLevelDesignView : public GDesignFormView
{
	DECLARE_DYNCREATE(GStageLevelDesignView)
protected:
	CStatic mGpMobAttackLine;
	CStatic mGpMopAppear;
	CStatic mGpMassMobAppear;
	CEdit mEtStageNumber;
	CEdit mEtBossMobIndex;
	CEdit mEtCastleHP;
	GStageLevelGridCtrl* mpGcMopAppear;
	GStageLevelGridCtrl* mpGcMobAttackLine;
	GStageLevelGridCtrl* mpGcMassMopAppear;
	bool mLoadedStageLevel;
	GStageLevel mLoadStageLevelValue;
	UINT mStageNumber;
	UINT mBossMobIndex;
	unsigned int mCastleHP;

public:
	static CRuntimeClass* CreateFormView() {
		return RUNTIME_CLASS(GStageLevelDesignView);
	}
	static const gchar* GetStaicName() {
		return "StageLevel";
	}
public:	
	virtual void Save(GnStream* pStream);
	virtual void Load(GnStream* pStream);
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	virtual const gchar* GetName() {
		return "StageLevel";
	}

protected:
	void SaveStageLevel(GStageLevel* pStageLevel);
	void LoadStageLevel(GStageLevel* pStageLevel);

protected:
	virtual void OnInitialUpdate();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.
public:
	enum { IDD = IDD_GSTAGELEVELDESIGNVIEW };
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

protected:
	GStageLevelDesignView();           // ���� ����⿡ ���Ǵ� protected �������Դϴ�.
	virtual ~GStageLevelDesignView();

protected:
	afx_msg void OnClickedAddMob();
	afx_msg void OnClickedDeleteMob();	
	afx_msg void OnBnClickedAddMassMob();
	afx_msg void OnBnClickedBtDeleteMassMob();

	DECLARE_MESSAGE_MAP()


};


