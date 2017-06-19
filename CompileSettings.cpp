// CompileSettings.cpp: implementation of the CCompileSettings class.
//
//////////////////////////////////////////////////////////////////////

#include "CompileSettings.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CCompileSettings::CCompileSettings()
{
	callCenter = new CCallCenter();
	map = new CBuildMap();
	iSelectedUserLevel = 0;
}

CCompileSettings::~CCompileSettings()
{
}

CCallCenter* CCompileSettings::GetCallCenter()
{
	return callCenter;
}

CBuildMap* CCompileSettings::GetMap()
{
	return map;
}

void CCompileSettings::SetUserlevel(int level)
{
	if (CDescriptionManager::Instance()->IsUserlevel(level))
		iSelectedUserLevel = level;
}

int CCompileSettings::GetUserlevel()
{
	return iSelectedUserLevel;
}

int CCompileSettings::Compile()
{
	return 1;
}