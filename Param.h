// Param.h: interface for the CParam class.
//
//////////////////////////////////////////////////////////////////////

#ifndef PARAM_H
#define PARAM_H

class CParam  
{
private:
	int ID;
	char value[64];

public:
	CParam(int ID);
	virtual ~CParam();

	int GetID();
	const char* GetValue();
	void SetValue(char* value);
};

#endif
