// OptionDescription.h: interface for the COptionDescription class.
//
//////////////////////////////////////////////////////////////////////

#ifndef OPTIONDESCRIPTION_H
#define OPTIONDESCRIPTION_H

#include "XMLParser.h"
#include "ArrayList.h"
#include "Call.h"
#include "Option.h"

class COptionDescription  
{
private:
	COptionDescription();
	virtual ~COptionDescription();

// Singleton Instance
private:
	static COptionDescription* pInstance;
	static bool isLoaded;

// Singleton Instanciator
public:
	static COptionDescription* GetInstance();
	static void ClearInstance();

// Descriptionfile options
private:
	struct UserLevel
	{
		int level;						// 1-based userlevel index
		char name[64];
	};

	char toolName[64];
	char fileName[64];
	CArrayList <UserLevel> userLevels;
	CArrayList <COption*> options;

	bool ReadUserLevels(CXMLParser* XML);
	bool ReadDescription(CXMLParser* XML);
	bool ReadCall(CXMLParser* XML);

// Descriptionfile methods
public:
	void LoadDescriptionFile(const char* filename);

	bool IsDescriptionLoaded();

	COption* GetOption(int ID);
};

#endif
