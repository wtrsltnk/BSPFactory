// CompileSettings.h: interface for the CCompileSettings class.
//
//////////////////////////////////////////////////////////////////////

#ifndef COMPILESETTINGS_H
#define COMPILESETTINGS_H

#include "DescriptionManager.h"
#include "CallCenter.h"
#include "BuildMap.h"

class CCompileSettings  
{
private:
	CCallCenter* callCenter;
	CBuildMap* map;
	int iSelectedUserLevel;
public:
	CCompileSettings();
	virtual ~CCompileSettings();

	CCallCenter* GetCallCenter();
	CBuildMap* GetMap();

	void SetUserlevel(int level);
	int GetUserlevel();

	int Compile();
};

#endif
