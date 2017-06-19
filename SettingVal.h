// SettingVal.h: interface for the CSettingVal class.
//
//////////////////////////////////////////////////////////////////////

#ifndef SETTINGVAL_H
#define SETTINGVAL_H

class CSettingVal  
{
private:
	bool run;
	char settingName[64];
	char settingValue[256];
public:
	CSettingVal(char* settingName);
	virtual ~CSettingVal();

	char* GetName();
	char* GetValue();
	void SetValue(char* value);
	
	bool IsRun();
	void Run(bool run);
};

#endif
