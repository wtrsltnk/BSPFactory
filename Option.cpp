// Option.cpp: implementation of the COption class.
//
//////////////////////////////////////////////////////////////////////

#include "Option.h"
#include <string.h>
#include <stdlib.h>

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

COption::COption()
{
	ID = 0;
	type = 0;
	optionName[0] = '\0';
	callName[0] = '\0';	
	defaultValue = 0;
	description = 0;
	userLevel = 0;
}

COption::~COption()
{
	if (defaultValue)
		delete [] defaultValue;
	defaultValue = 0;

	if (description)
		delete [] description;
	description = 0;

	enumValues.Resize(0);
}

//////////////////////////////////////////////////////////////////////
// Purpose : 
// Input   : 
// Output  : 
//////////////////////////////////////////////////////////////////////
bool COption::ReadOption(CXMLParser* XML)
{
	while (stricmp(XML->GetElementName(), "</option>") != 0)
	{
		if (stricmp(XML->GetElementName(), "<id>") == 0)			// 1-based identifier
		{
			if (XML->HasData())
			{
				int in = atoi(XML->GetData());
				if (in > 0)
					this->ID = in;
			}
		}
		else if (stricmp(XML->GetElementName(), "<type>") == 0)
		{
			if (XML->HasData())
			{
				int in = atoi(XML->GetData());
				if (in > 0 && in < 5)
					this->type = in;
			}
		}
		else if (stricmp(XML->GetElementName(), "<userLevel>") == 0)
		{
			if (XML->HasData())
			{
				int in = atoi(XML->GetData());
				if (in > 0)
					this->userLevel = in;
			}
		}
		else if (stricmp(XML->GetElementName(), "<optionname>") == 0)
		{
			if (XML->HasData())
			{
				strncpy(this->optionName, XML->GetData(), 64);
			}
		}
		else if (stricmp(XML->GetElementName(), "<callname>") == 0)
		{
			if (XML->HasData())
			{
				strncpy(this->callName, XML->GetData(), 64);
			}
		}
		else if (stricmp(XML->GetElementName(), "<defaultvalue>") == 0)
		{
			if (XML->HasData())
			{
				int len = strlen(XML->GetData());
				this->defaultValue = new char[len];
				strncpy(this->defaultValue, XML->GetData(), strlen(XML->GetData()));
				this->defaultValue[len] = '\0';
			}
		}
		else if (stricmp(XML->GetElementName(), "<optiondescription>") == 0)
		{
			if (XML->HasData())
			{
				int len = strlen(XML->GetData());
				this->description = new char[len];
				strncpy(this->description, XML->GetData(), strlen(XML->GetData()));
				this->description[len] = '\0';
			}
		}
		else if (stricmp(XML->GetElementName(), "<enums>") == 0)
		{
			if (!ReadEnums(XML))
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
bool COption::ReadEnums(CXMLParser* XML)
{
	while (stricmp(XML->GetElementName(), "</enums>") != 0)
	{
		if (stricmp(XML->GetElementName(), "<item>") == 0)
		{
			if (XML->HasData())
			{
				char* newenum = new char[64];
				strncpy(newenum, XML->GetData(), 64);
				enumValues.Add(newenum);
			}
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
bool COption::operator==(COption* o)
{
	return (this->ID == o->ID);
}

//////////////////////////////////////////////////////////////////////
// Purpose : 
// Input   : 
// Output  : 
//////////////////////////////////////////////////////////////////////
int COption::GetID()
{
	return this->ID;
}

//////////////////////////////////////////////////////////////////////
// Purpose : 
// Input   : 
// Output  : 
//////////////////////////////////////////////////////////////////////
int COption::GetType()
{
	return this->type;
}

//////////////////////////////////////////////////////////////////////
// Purpose : 
// Input   : 
// Output  : 
//////////////////////////////////////////////////////////////////////
char* COption::GetName()
{
	return this->optionName;
}

//////////////////////////////////////////////////////////////////////
// Purpose : 
// Input   : 
// Output  : 
//////////////////////////////////////////////////////////////////////
char* COption::GetCall()
{
	return this->callName;
}

//////////////////////////////////////////////////////////////////////
// Purpose : 
// Input   : 
// Output  : 
//////////////////////////////////////////////////////////////////////
char* COption::GetDefault()
{
	return this->defaultValue;
}

//////////////////////////////////////////////////////////////////////
// Purpose : 
// Input   : 
// Output  : 
//////////////////////////////////////////////////////////////////////
char* COption::GetDescription()
{
	return this->description;
}

//////////////////////////////////////////////////////////////////////
// Purpose : 
// Input   : 
// Output  : 
//////////////////////////////////////////////////////////////////////
int COption::GetUserLevel()
{
	return this->userLevel;
}

//////////////////////////////////////////////////////////////////////
// Purpose : 
// Input   : 
// Output  : 
//////////////////////////////////////////////////////////////////////
int COption::GetNumEnums()
{
	return this->enumValues.Length();
}

//////////////////////////////////////////////////////////////////////
// Purpose : 
// Input   : 
// Output  : 
//////////////////////////////////////////////////////////////////////
char* COption::GetEnum(int index)
{
	if (index > (int)this->enumValues.Length())
		return 0;

	return enumValues[index];
}

//////////////////////////////////////////////////////////////////////
// Purpose : 
// Input   : 
// Output  : 
//////////////////////////////////////////////////////////////////////
char* COption::GetInfoText()
{
	return 0;
}
