// DescriptionManager.h: interface for the CDescriptionManager class.
//
//////////////////////////////////////////////////////////////////////

#ifndef DESCRIPTIONMANAGER_H
#define DESCRIPTIONMANAGER_H

#include "XMLParser.h"
#include "ArrayList.h"
#include "ToolDescription.h"
#include "Setting.h"

class CDescriptionManager  
{
private:
	struct UserLevel
	{
		int level;						// 1-based userlevel index
		char name[64];
	};
	CArrayList <UserLevel*> userLevels;
	CArrayList <CSetting*> settings;

private:
	bool LoadFile(const char* filename);
	CArrayList <CToolDescription*> tools;
	bool ReadUserLevel(CXMLParser* XML);

public:
	CDescriptionManager();
	virtual ~CDescriptionManager();

	int GetNumTools();
	CToolDescription* GetTool(int index);
	CToolDescription* GetTool(const char* tool);

	int GetNumUserlevels();
	char* GetUserLevel(int level);
	bool IsUserlevel(int level);

	int GetNumSettings();
	CSetting* GetSetting(int index);

// Singleton Instance
private:
	static CDescriptionManager* pInstance;
	static bool isLoaded;
	
// Singleton Instanciator
public:
	static CDescriptionManager* InitInstance(const char* filename);
	static CDescriptionManager* Instance();
	static bool IsLoaded();
	static void ClearInstance();
};

#endif
