// AboutDlg.h: interface for the CAboutDlg class.
//
//////////////////////////////////////////////////////////////////////

#ifndef ABOUTDLG_H
#define ABOUTDLG_H

#include "Dialog.h"

namespace Factory
{
	class CAboutDlg : public CDialog
	{
	public:
		CAboutDlg();
		virtual ~CAboutDlg();

		void DlgProc(UINT uMsg, WPARAM wParam, LPARAM lParam);
	};
}
#endif
