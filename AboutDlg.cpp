// AboutDlg.cpp: implementation of the CAboutDlg class.
//
//////////////////////////////////////////////////////////////////////

#include "AboutDlg.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

Factory::CAboutDlg::CAboutDlg()
{
	this->m_dwResourceDlg = IDD_ABOUT;
}

Factory::CAboutDlg::~CAboutDlg()
{
}

void Factory::CAboutDlg::DlgProc(UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_INITDIALOG:
		{
			RECT dsktp, dlg;
			GetWindowRect(GetDesktopWindow(), &dsktp);
			GetWindowRect(m_hDlg, &dlg);

			int x = (dsktp.right / 2) - ((dlg.right-dlg.left) / 2);
			int y = (dsktp.bottom / 2) - ((dlg.bottom-dlg.top) / 2);
			MoveWindow(m_hDlg, x, y, (dlg.right-dlg.left), (dlg.bottom-dlg.top), true);
			break;
		}
	}

	CDialog::DlgProc(uMsg, wParam, lParam);
}
