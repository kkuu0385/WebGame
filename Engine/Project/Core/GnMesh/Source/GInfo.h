#ifndef __Core__GInfo__
#define __Core__GInfo__

class GnSQLite;
class GnSQLiteQuery;
class GInfo : public GnMemoryObject
{
public:
	static const gtint NULL_TYPE = -1;
public:
	enum eInofComponentType
	{
		INFO_BASIC,
		INFO_MAX,
	};
private:
	guint32 mLevel;
	
public:
	bool LoadDataFromSql(const gchar* pcID, const guint32 uiLevel, GnSQLite* pSql);
	
	virtual inline gtint GetInfoType() {
		return GInfo::NULL_TYPE;
	}
	
	inline guint32 GetLevel() {
		return mLevel;
	}
protected:
	virtual void LoadDataFromQuery(GnSQLiteQuery* pQuery) = 0;
	virtual const gchar* GetUseDatabaseTableName() = 0;
	
//	inline void ExecuteSingleQueryFromID(GnSQLite* pSql, const gchar* pcTableaName
//		, const gchar* pcID, guint32 uiLevel)
//	{
//		gchar combineQuery[256];
//		GnSprintf( combineQuery, sizeof(combineQuery), "SELECT * FROM %s WHERE id=%s AND %d"
//			, pcTableaName, pcID, uiLevel );
//		GnSQLiteQuery query = pSql->ExecuteSingleQuery( combineQuery );
//		LoadDataFromQuery( &query );
//	}
};

#endif
