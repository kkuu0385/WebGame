#include <cocos2d.h>
using namespace cocos2d;
typedef CCSprite GnReal2DMesh;
typedef CCNode GnInterfaceNode;

#include "GnMeshLibType.h"
#include "GnDataStream.h"
#include "GnActorStreamMacro.h"
#include "GnScreenMesh.h"
#include "GnSMManager.h"
#include "GnAnimation.h"
#include "Gn2DTextureAni.h"
#include "Gn2DTextureAniCtlr.h"
#include "Gn2DAVData.h"
#include "Gn2DMeshObject.h"
#include "Gn2DNode.h"
#include "GnSequence.h"
#include "Gn2DSequence.h"
#include "Gn2DActor.h"

#include "GnPathUtil.h"
#include "GnSQLite.h"
#include "GnFileUtil.h"

#include "GnGameState.h"
#include "GnAnimationKey.h"
#include "GnTegIDKey.h"
#include "Gg2DCollision.h"
#include "Gn2DAVDataConverter.h"
#include "GnLayer.h"
#include "GnCocosScene.h"
#include "GnSceneManager.h"
//#include ""#pragma ()