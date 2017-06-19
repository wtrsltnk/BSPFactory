// Call.h: interface for the CCall class.
//
//////////////////////////////////////////////////////////////////////

#ifndef CALL_H
#define CALL_H

#include "ArrayList.h"
#include "Tool.h"
#include "Param.h"

class CCall  
{
private:
	bool run;
	CTool* tool;
	CArrayList <CParam*> params;

public:
	CCall(CTool* tl);
	virtual ~CCall();

	char* Call();

	void SetTool(CTool* tl);
	int AddParam(CParam* p);
	void RemoveParam(int index);
	void RemoveParam(CParam* p);

	CTool* GetTool();

	int GetNumParams();
	CParam* GetParam(int index);

	bool IsRun();
	void Run(bool run);
};

#endif
