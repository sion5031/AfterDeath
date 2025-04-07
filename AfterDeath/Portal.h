#pragma once
#include <memory>

using namespace std;

class Map;

class Portal
{
private:
	int NextMapNum;

public:
	Portal();
	Portal(int newMap);
	~Portal();

	void SetPortalInfo(int nextMap);
	int GetPortalInfo();
};