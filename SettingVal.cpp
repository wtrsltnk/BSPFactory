// SettingVal.cpp: implementation of the CSettingVal class.
//
//////////////////////////////////////////////////////////////////////

#include "SettingVal.h"
#include <string.h>

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CSettingVal::CSettingVal(char* settingName)
{
	strncpy(this->settingName, settingName, 64);
	this->settingValue[0] = '\0';
}

CSettingVal::~CSettingVal()
{
}

//////////////////////////////////////////////////////////////////////
// Purpose : 
// Input   : 
// Output  : 
//////////////////////////////////////////////////////////////////////
char* CSettingVal::GetName()
{
	return settingName;
}

//////////////////////////////////////////////////////////////////////
// Purpose : 
// Input   : 
// Output  : 
//////////////////////////////////////////////////////////////////////
char* CSettingVal::GetValue()
{
	return settingValue;
}

//////////////////////////////////////////////////////////////////////
// Purpose : 
// Input   : 
// Output  : 
//////////////////////////////////////////////////////////////////////
void CSettingVal::SetValue(char* value)
{
	strncpy(this->settingValue, value, 256);
}

//////////////////////////////////////////////////////////////////////
// Purpose : 
// Input   : 
// Output  : 
//////////////////////////////////////////////////////////////////////
bool CSettingVal::IsRun()
{
	return this->run;
}

//////////////////////////////////////////////////////////////////////
// Purpose : 
// Input   : 
// Output  : 
//////////////////////////////////////////////////////////////////////
void CSettingVal::Run(bool run)
{
	this->run = run;
}