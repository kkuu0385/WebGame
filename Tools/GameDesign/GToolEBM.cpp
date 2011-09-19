#include "StdAfx.h"
#include "GToolEBM.h"
#include "GMobAppearGrid.h"
#include "GMobAttackLineGrid.h"
#include "GMassMobAppearGrid.h"
#include "GStageLevelDesignView.h"


#include <GnSystemEBM.h>
#include <GnMainEBM.h>
#include <GnMeshEBM.h>

void GToolEBM::StartupEBM()
{
	SaveClass(GMobAttackLineGrid);
	SaveClass(GMobAppearGrid);
	SaveClass(GMassMobAppearGrid);
	
	RegFormView(GStageLevelDesignView);

	// ���̺귯�� ����
	GnSystemEBM::StartupEBM();
	GnMainEBM::StartupEBM();
	GnMeshEBM::StartupEBM();
}

void GToolEBM::ShutdownEBM()
{
	GnMeshEBM::ShutdownEBM();
	GnMainEBM::ShutdownEBM();	
	GnSystemEBM::ShutdownEBM();	
}