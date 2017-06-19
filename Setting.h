// Setting.h: interface for the CSetting class.
//
//////////////////////////////////////////////////////////////////////

#ifndef SETTING_H
#define SETTING_H

#include "XMLParser.h"

class CSetting  
{
private:
	char settingName[64];
public:
	CSetting();
	virtual ~CSetting();

	char* GetSettingName();
	
	bool ReadSetting(CXMLParser* XML);
};

#endif
