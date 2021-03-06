//
//  GItemInfo.cpp
//  Core
//
//  Created by Max Yoon on 11. 8. 12..
//  Copyright 2011년 __MyCompanyName__. All rights reserved.
//

#include "GnGamePCH.h"
#include "GItemInfo.h"

GnImplementSingleton(GItemInfo)


const gchar* GItemInfo::GetIconFileName(gtuint uiIndex)
{
	uiIndex -= INDEX_ITEM;
	if( mscNumMaxItem <= uiIndex  )
		return NULL;
	
	static const char fileName[mscNumMaxItem][256] = 	
	{
		{"Upgrade/items/400_74 a.png"}, {"Upgrade/items/400_174.png"},
		{"Upgrade/items/400_124.png"}, {"Upgrade/items/400_74 .png"},
		{"Upgrade/items/400_174 a.png"}, {"Upgrade/items/N1_a.png"}
	};
	
	return fileName[uiIndex];
}

const gchar* GItemInfo::GetGameIconFileName(gtuint uiIndex)
{
	uiIndex -= INDEX_ITEM;
	if( mscNumMaxItem <= uiIndex  )
		return NULL;
	
	static const char fileName[mscNumMaxItem][256] = 	
	{
		{"Controll/N5_g.png"}, {"Controll/N4_g.png"},
		{"Controll/N3_g.png"}, {"Controll/N2_g.png"},
		{"Controll/N6_g.png"}, {"Controll/N1_g.png"}
	};
	
	return fileName[uiIndex];
}

const gchar* GItemInfo::GetPriceIconFileName(gtuint uiIndex)
{
	uiIndex -= INDEX_ITEM;
	if( mscNumMaxItem <= uiIndex )
		return NULL;
	
	static const char fileName[mscNumMaxItem][256] = 	
	{
		{"Upgrade/items/30_140.png"}, {"Upgrade/items/134_74.png"},
		{"Upgrade/items/82_74.png"}, {"Upgrade/items/30_74.png"},
		{"Upgrade/items/82_140.png"}, {"Upgrade/items/N1.png"}
	};
	return fileName[uiIndex];
}

const gchar* GItemInfo::GetExplainFileName(gtuint uiIndex)
{
	uiIndex -= INDEX_ITEM;
	if( mscNumMaxItem <= uiIndex  )
		return NULL;
	
	static const char fileName[mscNumMaxItem][256] = 	
	{
		{"Upgrade/items/a 28_222.png"}, {"Upgrade/items/c 28_222.png"},
		{"Upgrade/items/b 28_222.png"}, {"Upgrade/items/d 28_222.png"},
		{"Upgrade/items/e 28_222.png"}, {"Upgrade/items/e 28_222.png"}
	};
	return fileName[uiIndex];	
}

guint32 GItemInfo::GetBuyPrice(gtuint uiIndex, guint32 uiLevel)
{
	GnSQLite sqlite( GetFullPath( "ItemInfo.sqlite" ) );
	GnSQLiteQuery query = sqlite.ExecuteSingleQuery( "SELECT * FROM GameItem WHERE idx=%d"
		, uiIndex );
	
	if( query.QueryReturn() == false )
		return false;
	
	guint32 price = query.GetIntField( 3 ) *( uiLevel + 1  );
	return price;
}

guint32 GItemInfo::GetSellPrice(gtuint uiIndex, guint32 uiLevel)
{
	GnSQLite sqlite( GetFullPath( "ItemInfo.sqlite" ) );
	GnSQLiteQuery query = sqlite.ExecuteSingleQuery( "SELECT * FROM GameItem WHERE idx=%d"
		, uiIndex );
	
	if( query.QueryReturn() == false )
		return false;
	
	guint32 price = query.GetIntField( 4 ) *( uiLevel + 1  );
	return price;
}