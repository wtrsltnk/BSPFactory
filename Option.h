// Option.h: interface for the COption class.
//
//////////////////////////////////////////////////////////////////////

#ifndef OPTION_H
#define OPTION_H

#include "XMLParser.h"
#include "ArrayList.h"

class COption  
{
// Enumerations
public:
	enum
	{
		boolean = 1,
		integer,
		text,
		enumeration
	};

private:
	int ID;
	int type;
	char optionName[64];
	char callName[64];
	char* defaultValue;
	char* description;
	int userLevel;
	CArrayList <char*> enumValues;

	bool ReadEnums(CXMLParser* XML);
public:
	COption();
	virtual ~COption();

	bool ReadOption(CXMLParser* XML);

	bool operator==(COption* o);

	int GetID();
	int GetType();
	char* GetName();
	char* GetCall();
	char* GetDefault();
	char* GetDescription();
	int GetUserLevel();

	int GetNumEnums();
	char* GetEnum(int index);

	char* GetInfoText();
};

#endif
