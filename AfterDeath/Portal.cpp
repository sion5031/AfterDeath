#include "Portal.h"
//#include "Map.h"

Portal::Portal()
{
}

Portal::Portal(int newMap)
{
	NextMapNum = newMap;
}

Portal::~Portal()
{
}

void Portal::SetPortalInfo(int nextMap)
{
	NextMapNum = nextMap;
}

int Portal::GetPortalInfo()
{
	return NextMapNum;
}
