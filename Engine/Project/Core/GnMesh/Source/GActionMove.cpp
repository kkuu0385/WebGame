//
//  GActionMove.cpp
//  HiroCat
//
//  Created by Max Yoon on 11. 6. 20..
//  Copyright 2011년 __MyCompanyName__. All rights reserved.
//

#include "GnGamePCH.h"
#include "GActionMove.h"

GActionMove::GActionMove(GActorController* pController) : GAction( pController ), mpActorLayer( NULL )
	, mMoveRange( 5.0f, 40.0f )
{
	SetMoveLeft( false );
	SetMoveRight( false );
	SetMoveUp( false );
	SetMoveDown( false );
}

void GActionMove::Update(float fDeltaTime)
{
	GnVector2 movePos = GetController()->GetPosition();
	movePos +=  GetMoveVector();
	GetController()->SetMovePosition( movePos );
}

void GActionMove::SetMove(gtuint uiType, bool bCleanMove)
{
	if( bCleanMove )
	{
		SetMoveLeft( false );
		SetMoveRight( false );
		SetMoveUp( false );
		SetMoveDown( false );
		mMoveVector.x = 0.0f;
		mMoveVector.y = 0.0f;
	}
	
	switch ( uiType )
	{
		case MOVELEFT:
		{
			mMoveVector.x = -GetMoveRange().x;
			SetMoveLeft( true );
		}
		break;
		case MOVERIGHT:
		{
			mMoveVector.x = GetMoveRange().x;
			SetMoveRight( true );
		}
		break;
		case MOVEUP:
		{
			mMoveVector.y = GetMoveRange().y;
			SetMoveUp( true );
		}
		break;
		case MOVEDOWN:
		{
			mMoveVector.y = -GetMoveRange().y;
			SetMoveDown( true );
		}
		break;
	}
}