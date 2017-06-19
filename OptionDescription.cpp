// OptionDescription.cpp: implementation of the COptionDescription class.
//
//////////////////////////////////////////////////////////////////////

#include "OptionDescription.h"
#include "string.h"

//////////////////////////////////////////////////////////////////////
// Statics
//////////////////////////////////////////////////////////////////////

COptionDescription* COptionDescription::pInstance = 0;
bool COptionDescription::isLoaded = false;

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

COptionDescription::COptionDescription()
{
	toolName[0] = '\0';
	fileName[0] = '\0';
}

COptionDescription::~COptionDescription()
{
	userLevels.Resize(0);
	options.Resize(0);
}

//////////////////////////////////////////////////////////////////////
// Purpose : 
// Input   : 
// Output  : 
//////////////////////////////////////////////////////////////////////
COptionDescription* COptionDescription::GetInstance()
{
	if (!pInstance)
		pInstance = new COptionDescription();
	return pInstance;
}

//////////////////////////////////////////////////////////////////////
// Purpose : 
// Input   : 
// Output  : 
//////////////////////////////////////////////////////////////////////
void COptionDescription::ClearInstance()
{
	if (!pInstance)
	{
		delete pInstance;
		pInstance = 0;
	}
}

//////////////////////////////////////////////////////////////////////
// Purpose : 
// Input   : 
// Output  : 
//////////////////////////////////////////////////////////////////////
void COptionDescription::LoadDescriptionFile(const char* filename)
{
	CXMLParser XML;

	XML.SetXmlFile(const_cast <char*> (filename));

	// Loop naar de description toe
	while (stricmp(XML.GetElementName(), "<tooldescription>") != 0)
		XML.GetNextElement();

	XML.GetNextElement();

	// Laad de hele description
	ReadDescription(&XML);

	isLoaded = true;
}

//////////////////////////////////////////////////////////////////////
// Purpose : 
// Input   : 
// Output  : 
//////////////////////////////////////////////////////////////////////
bool COptionDescription::ReadUserLevels(CXMLParser* XML)
{
	while (stricmp(XML->GetElementName(), "</userlevel>") != 0)
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
bool COptionDescription::ReadDescription(CXMLParser* XML)
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
		else if (stricmp(XML->GetElementName(), "<userlevel>") == 0)
		{
			if (!ReadUserLevels(XML))
				return false;
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
bool COptionDescription::ReadCall(CXMLParser* XML)
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
bool COptionDescription::IsDescriptionLoaded()
{
	return isLoaded;
}

//////////////////////////////////////////////////////////////////////
// Purpose : 
// Input   : 
// Output  : 
//////////////////////////////////////////////////////////////////////
COption* COptionDescription::GetOption(int ID)
{
	for (int i = 0; i < (int)options.Length(); i++)
	{
		if (options[i]->GetID() == ID)
			return options[i];
	}
	return 0;
}