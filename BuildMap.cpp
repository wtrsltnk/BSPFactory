// BuildMap.cpp: implementation of the CBuildMap class.
//
//////////////////////////////////////////////////////////////////////

#include "BuildMap.h"
#include <string.h>

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CBuildMap::CBuildMap()
{
	mapName[0] = '\0';
	mapPath[0] = '\0';
}

CBuildMap::~CBuildMap()
{
}

//////////////////////////////////////////////////////////////////////
// Purpose : 
// Input   : 
// Output  : 
//////////////////////////////////////////////////////////////////////
void CBuildMap::SetMap(char* map)
{
	if (strcspn(map, ".map") <= 0)
		return;

    int i = 0, j = 0;
    for (i = strlen(map); i > 0; i--)
	{
		if (map[i] == '/' || map[i] == '\\')
			break;
	}

	strncpy(mapPath, map, i);
	mapPath[i] = '\0';

	i++;

    for (j = i; j < (int)strlen(map); j++)
    {
        mapName[j-i] = map[j];
	}
	mapName[j-i] = '\0';
}

//////////////////////////////////////////////////////////////////////
// Purpose : 
// Input   : 
// Output  : 
//////////////////////////////////////////////////////////////////////
char* CBuildMap::GetMapName()
{
	return mapName;
}

//////////////////////////////////////////////////////////////////////
// Purpose : 
// Input   : 
// Output  : 
//////////////////////////////////////////////////////////////////////
char* CBuildMap::GetMapPath()
{
	return mapPath;
}

//////////////////////////////////////////////////////////////////////
// Purpose : 
// Input   : 
// Output  : 
//////////////////////////////////////////////////////////////////////
int CBuildMap::GetType()
{
	if (strcmp(mapName, "") == 0)
		return 0;

	int len = strlen(mapName);
	if (mapName[len-4] != '.')
		return 0;

	if (mapName[len-3] == 'm' && mapName[len-2] == 'a' && mapName[len-1] == 'p')
		return 1;
	else if (mapName[len-3] == 'r' && mapName[len-2] == 'm' && mapName[len-1] == 'f')
		return 2;

	return 0;
}