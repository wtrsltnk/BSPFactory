// BuildMap.h: interface for the CBuildMap class.
//
//////////////////////////////////////////////////////////////////////

#ifndef BUILDMAP_H
#define BUILDMAP_H

class CBuildMap  
{
private:
	char mapName[64];
	char mapPath[256];
public:
	CBuildMap();
	virtual ~CBuildMap();

	void SetMap(char* map);

	char* GetMapName();
	char* GetMapPath();

	int GetType();
};

#endif
