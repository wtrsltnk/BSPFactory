// ToolDescription.h: interface for the CToolDescription class.
//
//////////////////////////////////////////////////////////////////////

#ifndef TOOLDESCRIPTION_H
#define TOOLDESCRIPTION_H

#include "XMLParser.h"
#include "ArrayList.h"
#include "Option.h"

class CToolDescription  
{
public:
	CToolDescription();
	virtual ~CToolDescription();

// Descriptionfile options
private:

	char toolName[64];					// Must be unique for a tooldescription
	char fileName[64];
	CArrayList <COption*> options;

	bool ReadCall(CXMLParser* XML);

// Descriptionfile methods
public:
	bool ReadDescription(CXMLParser* XML);

	int GetNumOptions();
	COption* GetOption(int index);
	COption* GetOptionByID(int ID);

	const char* GetToolName();
	const char* GetFileName();
};

#endif
