// InfoDlg.h: interface for the CInfoDlg class.
//
//////////////////////////////////////////////////////////////////////

#ifndef INFODLG_H
#define INFODLG_H

#include <windows.h>
#include "Dialog.h"
#include "resource.h"
#include "DescriptionManager.h"
#include "ToolDescription.h"

namespace Factory
{
	class CInfoDlg : public CDialog
	{
	private:
		CToolDescription* toolDescription;

		int GetSelectedOption();
		void ClearOption();
		void FillOption(COption* option);
	public:
		CInfoDlg();
		virtual ~CInfoDlg();

		int Show(HWND hParent, const char* toolName);

		void DlgProc(UINT uMsg, WPARAM wParam, LPARAM lParam);
	};
}
#endif
