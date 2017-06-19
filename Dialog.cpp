// CDialog.cpp: implementation of the CDialog class.
//
//////////////////////////////////////////////////////////////////////

#include "Dialog.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CDialog::CDialog()
{
	this->m_hInstance			 = NULL;
	this->m_hParent				 = NULL;
	this->m_hDlg				 = NULL;
	this->m_dwResourceDlg		 = 0;
}

CDialog::~CDialog()
{
}

//////////////////////////////////////////////////////////////////////
// Purpose : 
// Input   : 
// Output  : 
//////////////////////////////////////////////////////////////////////
LRESULT CDialog::BaseProc(HWND hDlg, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	CDialog *pDlg = 0;

	// Is it the first message?
	if (uMsg == WM_INITDIALOG)
	{
		// Get the object from the creation param
		pDlg = reinterpret_cast<CDialog *>(lParam);
		pDlg->SetHandle(hDlg);

		// Set it in the Window param
		::SetWindowLong(hDlg, GWL_USERDATA, lParam);
	}
	else
	{
		// Get the object from the window param
		pDlg = reinterpret_cast<CDialog *>(::GetWindowLong(hDlg, GWL_USERDATA)); 
	}

	if (pDlg)
		pDlg->DlgProc(uMsg, wParam, lParam);

	return FALSE;
}

//////////////////////////////////////////////////////////////////////
// Purpose : 
// Input   : 
// Output  : 
//////////////////////////////////////////////////////////////////////
int CDialog::ShowModal(HINSTANCE hInst, HWND hParent)
{
	this->m_hInstance = hInst;
	this->m_hParent = hParent;

	return DialogBoxParam(hInst, MAKEINTRESOURCE(m_dwResourceDlg), hParent, (DLGPROC)BaseProc, (LPARAM)this);
}

//////////////////////////////////////////////////////////////////////
// Purpose : 
// Input   : 
// Output  : 
//////////////////////////////////////////////////////////////////////
int CDialog::ShowModalless(HINSTANCE hInst, HWND hParent)
{
	this->m_hInstance = hInst;
	this->m_hParent = hParent;

	m_hDlg = CreateDialogParam(hInst, MAKEINTRESOURCE(m_dwResourceDlg), hParent, (DLGPROC)BaseProc, (LPARAM)this);
	ShowWindow(m_hDlg, SW_SHOW);
	
	return 0;
}

//////////////////////////////////////////////////////////////////////
// Purpose : Set the handle of the created dialogwindow in this 
//           instance. Used in the wndproc of the clientwindowclass
// Input   : Handle of the dialogwindow created by this instance
// Output  : 
//////////////////////////////////////////////////////////////////////
void CDialog::SetHandle(HWND hWnd)
{
	this->m_hDlg = hWnd;
}

//////////////////////////////////////////////////////////////////////
// Purpose : 
// Input   : 
// Output  : 
//////////////////////////////////////////////////////////////////////
void CDialog::DlgProc(UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_COMMAND:
		{
			switch (wParam)
			{
			case IDCANCEL:
			case IDOK:
				{
					EndDialog(m_hDlg, IDOK);
					break;
				}
			}
			break;
		}

	case WM_CLOSE:
		{
			EndDialog(m_hDlg, IDOK);
			break;
		}
	}
}
