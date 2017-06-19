// CDialog.h: interface for the CDialog class.
//
//////////////////////////////////////////////////////////////////////

#ifndef CDIALOG_H
#define CDIALOG_H

#define WIN32_MEAN_AND_LEAN
#include <windows.h>
#include "resource.h"

class CDialog  
{
protected:
	HWND m_hDlg;
	HWND m_hParent;
	HINSTANCE m_hInstance;
	DWORD m_dwResourceDlg;
public:
	CDialog();
	virtual ~CDialog();

	int ShowModal(HINSTANCE hInst, HWND hParent);
	int ShowModalless(HINSTANCE hInst, HWND hParent);
	void SetHandle(HWND hWnd);

	static LRESULT BaseProc(HWND hDlg, UINT uMsg, WPARAM wParam, LPARAM lParam);
	virtual void DlgProc(UINT uMsg, WPARAM wParam, LPARAM lParam);
};

#endif
