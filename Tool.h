// Tool.h: interface for the CTool class.
//
//////////////////////////////////////////////////////////////////////

#ifndef TOOL_H
#define TOOL_H

#include "ToolDescription.h"

class CTool  
{
private:
	char toolName[64];
	char toolPath[256];

public:
	CTool(const char* tool);
	virtual ~CTool();

	const char* GetToolName();
	const char* GetToolPath();

	void SetToolName(char* toolName);
	void SetToolPath(char* toolPath);
};

#endif
