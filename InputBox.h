// InputBox.h: interface for the CInputBox class.
//
//////////////////////////////////////////////////////////////////////

#ifndef INPUTBOX_H
#define INPUTBOX_H

#include "Dialog.h"

class CInputBox : public CDialog  
{
private:
	char* title;
	char result[256];
public:
	CInputBox();
	virtual ~CInputBox();

	void DlgProc(UINT uMsg, WPARAM wParam, LPARAM lParam);
	char* InputBox(HWND hParent, char* title);
};

#endif
