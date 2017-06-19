// ToolDescription.cpp: implementation of the CToolDescription class.
//
//////////////////////////////////////////////////////////////////////

#include "ToolDescription.h"
#include <string.h>
#include <stdlib.h>

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CToolDescription::CToolDescription()
{
}

CToolDescription::~CToolDescription()
{
}

//////////////////////////////////////////////////////////////////////
// Purpose : 
// Input   : 
// Output  : 
//////////////////////////////////////////////////////////////////////
bool CToolDescription::ReadDescription(CXMLParser* XML)
{
	while (stricmp(XML->GetElementName(), "</tooldescription>") != 0)
	{
		if (stricmp(XML->GetElementName(), "<toolname>") == 0)
		{
			if (XML->HasData())
			{
				strncpy(this->toolName, XML->GetData(), 64);
			}
		}
		else if (stricmp(XML->GetElementName(), "<filename>") == 0)
		{
			if (XML->HasData())
			{
				strncpy(this->fileName, XML->GetData(), 64);
			}
		}
		else if (stricmp(XML->GetElementName(), "<option>") == 0)
		{
			COption* opt = new COption();
			if (!opt->ReadOption(XML))
				return false;

			options.Add(opt);
		}
		if (!XML->GetNextElement())
			return false;
	}
	return true;
}

//////////////////////////////////////////////////////////////////////
// Purpose : 
// Input   : 
// Output  : 
//////////////////////////////////////////////////////////////////////
bool CToolDescription::ReadCall(CXMLParser* XML)
{
	while (stricmp(XML->GetElementName(), "</call>") != 0)
	{
		if (!XML->GetNextElement())
			return false;
	}
	return true;
}

//////////////////////////////////////////////////////////////////////
// Purpose : 
// Input   : 
// Output  : 
//////////////////////////////////////////////////////////////////////
int CToolDescription::GetNumOptions()
{
	return options.Length();
}

//////////////////////////////////////////////////////////////////////
// Purpose : 
// Input   : 
// Output  : 
//////////////////////////////////////////////////////////////////////
COption* CToolDescription::GetOption(int index)
{
	if (index > (int)options.Length())
		return 0;
	return options[index];
}

//////////////////////////////////////////////////////////////////////
// Purpose : 
// Input   : 
// Output  : 
//////////////////////////////////////////////////////////////////////
COption* CToolDescription::GetOptionByID(int ID)
{
	for (int i = 0; i < (int)options.Length(); i++)
	{
		if (options[i]->GetID() == ID)
			return options[i];
	}
	return 0;
}

//////////////////////////////////////////////////////////////////////
// Purpose : 
// Input   : 
// Output  : 
//////////////////////////////////////////////////////////////////////
const char* CToolDescription::GetToolName()
{
	return toolName;
}

//////////////////////////////////////////////////////////////////////
// Purpose : 
// Input   : 
// Output  : 
//////////////////////////////////////////////////////////////////////
const char* CToolDescription::GetFileName()
{
	return fileName;
}
