// CallCenter.h: interface for the CCallCenter class.
//
//////////////////////////////////////////////////////////////////////

#ifndef CALLCENTER_H
#define CALLCENTER_H

#include "ArrayList.h"
#include "Call.h"
#include "SettingVal.h"

class CCallCenter  
{
private:
	CArrayList <CCall*> calls;
	CArrayList <CSettingVal*> settings;
public:
	CCallCenter();
	virtual ~CCallCenter();

	int NewCall(CTool* tool);
	void RemoveCall(int call);
	void RemoveCall(CCall* c);

	int NewSetting(char* setting);
	void RemoveSetting(int setting);
	void RemoveSetting(CSettingVal* s);

	int GetNumCalls();
	CCall* GetCall(int index);

	int GetNumSettings();
	CSettingVal* GetSetting(int index);
};

#endif
