// Setting.cpp: implementation of the CSetting class.
//
//////////////////////////////////////////////////////////////////////

#include "Setting.h"
#include <string.h>

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CSetting::CSetting()
{
	settingName[0] = '\0';
}

CSetting::~CSetting()
{
}

//////////////////////////////////////////////////////////////////////
// Purpose : 
// Input   : 
// Output  : 
//////////////////////////////////////////////////////////////////////
char* CSetting::GetSettingName()
{
	return settingName;
}

//////////////////////////////////////////////////////////////////////
// Purpose : 
// Input   : 
// Output  : 
//////////////////////////////////////////////////////////////////////
bool CSetting::ReadSetting(CXMLParser* XML)
{
	while (stricmp(XML->GetElementName(), "</setting>") != 0)
	{
		if (stricmp(XML->GetElementName(), "<name>") == 0)
		{
			if (XML->HasData())
			{
				strncpy(this->settingName, XML->GetData(), 64);
			}
		}
		if (!XML->GetNextElement())
			return false;
	}
	return true;
}