// InputBox.cpp: implementation of the CInputBox class.
//
//////////////////////////////////////////////////////////////////////

#include "InputBox.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CInputBox::CInputBox()
{
	this->m_dwResourceDlg = IDD_INPUT;
	this->result[0] = '\0';
}

CInputBox::~CInputBox()
{
}

void CInputBox::DlgProc(UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_INITDIALOG:
		{
			SendMessage(m_hDlg, WM_SETTEXT, 0, (LPARAM)this->title);
			break;
		}

	case WM_COMMAND:
		{
			switch (LOWORD(wParam))
			{
			case IDOK:
				{
					SendMessage(GetDlgItem(m_hDlg, IDC_INPUT), WM_GETTEXT, 320, (LPARAM)this->result);
					break;
				}
			}
			break;
		}
	}

	CDialog::DlgProc(uMsg, wParam, lParam);
}

char* CInputBox::InputBox(HWND hParent, char* title)
{
	this->title = title;
	
	if (!CDialog::ShowModal(GetModuleHandle(0), hParent))
		return 0;

	return strdup(result);
}