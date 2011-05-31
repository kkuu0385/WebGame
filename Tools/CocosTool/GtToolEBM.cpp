#include "StdAfx.h"
#include "GtToolEBM.h"

#include <GnSystemEBM.h>
#include <GnMainEBM.h>
#include <GnMeshEBM.h>

void GtToolEBM::StartupEBM()
{
	// ���̺귯�� ����
	GnSystemEBM::StartupEBM();
	GnMainEBM::StartupEBM();
	GnMeshEBM::StartupEBM();

	GtToolSettings::EBMStartup();
	GtObjectFactory::EBMStartup();
 }

void GtToolEBM::ShutdownEBM()
{
	GtObjectFactory::EBMShutdown();
	GtToolSettings::EBMShutdown();
	
	GnMeshEBM::ShutdownEBM();
	GnMainEBM::ShutdownEBM();	
	GnSystemEBM::ShutdownEBM();	
}