// DescriptionManager.cpp: implementation of the CDescriptionManager class.
//
//////////////////////////////////////////////////////////////////////

#include "DescriptionManager.h"
#include <string.h>
#include <stdlib.h>

//////////////////////////////////////////////////////////////////////
// Statics
//////////////////////////////////////////////////////////////////////

CDescriptionManager* CDescriptionManager::pInstance = 0;
bool CDescriptionManager::isLoaded = false;

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CDescriptionManager::CDescriptionManager()
{
	tools.Resize(0);
	settings.Resize(0);
}

CDescriptionManager::~CDescriptionManager()
{
	tools.Resize(0);
	settings.Resize(0);
}

//////////////////////////////////////////////////////////////////////
// Purpose : 
// Input   : 
// Output  : 
//////////////////////////////////////////////////////////////////////
CDescriptionManager* CDescriptionManager::InitInstance(const char* filename)
{
	if (pInstance)
		delete pInstance;
	
	pInstance = new CDescriptionManager();
	if (!pInstance->LoadFile(filename))
		return 0;

	isLoaded = true;

	return pInstance;
}

//////////////////////////////////////////////////////////////////////
// Purpose : 
// Input   : 
// Output  : 
//////////////////////////////////////////////////////////////////////
CDescriptionManager* CDescriptionManager::Instance()
{
	return pInstance;
}

//////////////////////////////////////////////////////////////////////
// Purpose : 
// Input   : 
// Output  : 
//////////////////////////////////////////////////////////////////////
bool CDescriptionManager::IsLoaded()
{
	return isLoaded;
}

//////////////////////////////////////////////////////////////////////
// Purpose : 
// Input   : 
// Output  : 
//////////////////////////////////////////////////////////////////////
void CDescriptionManager::ClearInstance()
{
	if (!pInstance)
	{
		delete pInstance;
		pInstance = 0;
		isLoaded = false;
	}
}

//////////////////////////////////////////////////////////////////////
// Purpose : 
// Input   : 
// Output  : 
//////////////////////////////////////////////////////////////////////
bool CDescriptionManager::LoadFile(const char* filename)
{
	CXMLParser XML;

	XML.SetXmlFile(const_cast <char*> (filename));

	// Loop naar de description toe
	while (stricmp(XML.GetElementName(), "<root>") != 0)
		XML.GetNextElement();

	XML.GetNextElement();

	while (stricmp(XML.GetElementName(), "</root>") != 0)
	{
		if (stricmp(XML.GetElementName(), "<tooldescription>") == 0)
		{
			CToolDescription* pNew = new CToolDescription();
			if (!pNew->ReadDescription(&XML))
				return false;
			tools.Add(pNew);
		}
		else if (stricmp(XML.GetElementName(), "<userlevel>") == 0)
		{
			if (!ReadUserLevel(&XML))
				return false;
		}
		else if (stricmp(XML.GetElementName(), "<setting>") == 0)
		{
			CSetting* pNew = new CSetting();
			if (!pNew->ReadSetting(&XML))
				return false;
			settings.Add(pNew);
		}
		else
			return false;

		if (!XML.GetNextElement())
			return false;
	}
	return true;
}

//////////////////////////////////////////////////////////////////////
// Purpose : 
// Input   : 
// Output  : 
//////////////////////////////////////////////////////////////////////
bool CDescriptionManager::ReadUserLevel(CXMLParser* XML)
{
	UserLevel* ul = new UserLevel;
	memset(ul, 0, sizeof(UserLevel));
	while (stricmp(XML->GetElementName(), "</userlevel>") != 0)
	{
		if (stricmp(XML->GetElementName(), "<level>") == 0)
		{
			if (XML->HasData())
			{
				int level = atoi(XML->GetData());
				if (level != 0)
				{
					ul->level = level;
				}
			}
		}
		if (stricmp(XML->GetElementName(), "<name>") == 0)
		{
			if (XML->HasData())
			{
				strcpy(ul->name, XML->GetData());
			}
		}
		if (!XML->GetNextElement())
			return false;
	}

	if (ul->level != 0)
		userLevels.Add(ul);
	return true;
}

//////////////////////////////////////////////////////////////////////
// Purpose : 
// Input   : 
// Output  : 
//////////////////////////////////////////////////////////////////////
int CDescriptionManager::GetNumTools()
{
	return tools.Length();
}

//////////////////////////////////////////////////////////////////////
// Purpose : 
// Input   : 
// Output  : 
//////////////////////////////////////////////////////////////////////
CToolDescription* CDescriptionManager::GetTool(int index)
{
	if (index > (int)tools.Length())
		return 0;
	return (CToolDescription*)tools[index];
}

//////////////////////////////////////////////////////////////////////
// Purpose : 
// Input   : 
// Output  : 
//////////////////////////////////////////////////////////////////////
int CDescriptionManager::GetNumUserlevels()
{
	return userLevels.Length();
}

//////////////////////////////////////////////////////////////////////
// Purpose : 
// Input   : 
// Output  : 
//////////////////////////////////////////////////////////////////////
char* CDescriptionManager::GetUserLevel(int level)
{
	for (int i = 0; i < (int)userLevels.Length(); i++)
	{
		UserLevel* ul = userLevels[i];
		if (ul->level == level)
			return ul->name;
	}
	return 0;
}

//////////////////////////////////////////////////////////////////////
// Purpose : 
// Input   : 
// Output  : 
//////////////////////////////////////////////////////////////////////
bool CDescriptionManager::IsUserlevel(int level)
{
	for (int i = 0; i < (int)userLevels.Length(); i++)
		if (userLevels[i]->level == level)
			return true;
	return false;
}

//////////////////////////////////////////////////////////////////////
// Purpose : 
// Input   : 
// Output  : 
//////////////////////////////////////////////////////////////////////
int CDescriptionManager::GetNumSettings()
{
	return settings.Length();
}

//////////////////////////////////////////////////////////////////////
// Purpose : 
// Input   : 
// Output  : 
//////////////////////////////////////////////////////////////////////
CSetting* CDescriptionManager::GetSetting(int index)
{
	if (index > (int)settings.Length())
		return 0;
	return settings[index];
}

//////////////////////////////////////////////////////////////////////
// Purpose : 
// Input   : 
// Output  : 
//////////////////////////////////////////////////////////////////////
CToolDescription* CDescriptionManager::GetTool(const char* tool)
{
	for (int i = 0; i < (int)tools.Length(); i++)
	{
		if (stricmp(tools[i]->GetToolName(), tool) == 0)
			return tools[i];
	}
	return 0;
}
