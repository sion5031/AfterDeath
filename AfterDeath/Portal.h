#pragma once

class Map;

class Portal
{
private:
	Map* NextMap;

public:
	Portal();
	~Portal();

	void SetPortalInfo(Map* nextMap);
	Map* GetPortalInfo();
};