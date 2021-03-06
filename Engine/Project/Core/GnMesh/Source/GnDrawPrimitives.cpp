#include "GnMeshPCH.h"
#include "GnDrawPrimitives.h"

GnDrawPrimitives::GnDrawPrimitives() : mThickness(2.0f)
{

}

GnDrawPrimitives::~GnDrawPrimitives()
{

}

void GnDrawPrimitives::DrawRect(GnIRect iRect)
{
	DrawRect( (float)iRect.left, (float)iRect.top, (float)iRect.right, (float)iRect.bottom );
}

void GnDrawPrimitives::DrawRect(GnFRect fRect)
{
	DrawRect( fRect.left, fRect.top, fRect.right, fRect.bottom );
}

void GnDrawPrimitives::DrawRect(float fLeft, float fTop, float fRight, float fBottom)
{
	glColor4f( mColor.r, mColor.g, mColor.b, mColor.a );
	glLineWidth(mThickness);

	CCPoint vertices2[] = {
		CCPointMake( fLeft, fTop )
		, CCPointMake( fLeft, fBottom )
		, CCPointMake( fRight, fBottom )
		, CCPointMake( fRight, fTop )
	};
	ccDrawPoly( vertices2, 4, true);
}

void GnDrawPrimitives::DrawPoint(GnVector2 vPoint)
{
	glPointSize(mThickness);
	glColor4f(mColor.r, mColor.g, mColor.b, mColor.a);
	//vPoint.x *= GetGameState()->GetGameScale();
	//vPoint.y *= GetGameState()->GetGameScale();
	ccDrawPoint( CCPointMake(vPoint.x, vPoint.y) );
}


void GnDraw2DObjectRect::Draw()
{
	if( mpObject == NULL )
		return;
		
	Gn2DAVData* avData = mpObject->GetAVData();
	if( avData == NULL )
		return;

	CCSize meshSize = mpObject->GetMesh()->getContentSize();

	GnColorA tempColor = mColor;
	mColor = GnColorA( 0, 0, 0, 1 );
	GnVector2 pos = mpObject->GetOriginalPosition();
	//GnFRect gnMeshRect( 0, 0, meshSize.width, meshSize.height );
	GnFRect gnMeshRect( pos.x, pos.y, pos.x + meshSize.width, pos.y + meshSize.height );
	DrawRect( gnMeshRect );	
	
	for( gtuint i = 0 ; i < avData->GetCollisionCount() ; i++ )
	{
		GnColorA color[Gg2DCollision::COLLISION_MAX] =
		{
			GnColorA( 255, 255, 0, 1 ),
			GnColorA( 255, 0, 0, 1 )
		};		
		Gn2DAVData::CollisionRect drawRect = avData->GetCollisionRect( i );
		mColor = color[drawRect.mType];
		if( IsConvertCocosRect() )
		{
			bool convert = false;
			Gn2DAVData::CollisionRect baseRect;
			if( mBaseAVData.GetCollisionCount() > i )
			{
				convert = true;
				baseRect = mBaseAVData.GetCollisionRect(i);
			}
			else if( mBaseAVData.GetCollisionCount() > 0 )
			{
				convert = true;
				baseRect = mBaseAVData.GetCollisionRect( 0 );
			}

			if( convert )
			{
				drawRect.mRect = ConvertGnRectToCocosRect( avData->GetCollisionRect( i ).mRect
					, CCSizeMake((float)drawRect.mRect.right, (float)drawRect.mRect.bottom) );
			}
		}
		//drawRect.mRect.MoveX( mpObject->GetPosition().x );
		//drawRect.mRect.MoveY( mpObject->GetPosition().y );
		//float scale = drawRect.mRect.GetWidth() * GetGameState()->GetGameScale();
		//drawRect.mRect.SetWidth( scale );
		//scale = drawRect.mRect.GetHeight() * GetGameState()->GetGameScale();
		//drawRect.mRect.SetHeight( scale  );
		DrawRect( drawRect.mRect );
	}

	if( IsDrawAnchorPoint() )
	{
		float temp = mThickness;
		mThickness = 5;

		mColor = GnColorA( 0, 255, 255, 1 );
		GnVector2 point = avData->GetImageCenter();
		point += mpObject->GetPosition();
		DrawPoint( point );

		mColor = GnColorA( 0, 0, 255, 1 );
		point = avData->GetAnchorPoint();
		point.x *= meshSize.width;
		point.y *= meshSize.height;
		DrawPoint( point );

		mThickness = temp;
	}

	mColor = tempColor;
}

GnDraw2DObjectRect::GnDraw2DObjectRect()
{
	SetDrawAnchorPoint( true );
	SetConvertCocosRect( false );
}

void GnDrawRect::Draw()
{
	glColor4f( mColor.r, mColor.g, mColor.b, mColor.a );
	glLineWidth(mThickness);
	CCPoint vertices2[] = {
		CCPointMake( mRect.left, mRect.top )
		, CCPointMake( mRect.left, mRect.top + mRect.bottom )
		, CCPointMake( mRect.left+ mRect.right, mRect.top + mRect.bottom )
		, CCPointMake( mRect.left+ mRect.right, mRect.top )
	};
	ccDrawPoly( vertices2, 4, true);
}