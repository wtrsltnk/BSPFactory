#ifndef CAPPLICATION_H
#define CAPPLICATION_H

#include "CWin.h"
#include "resource.h"
#include "InfoDlg.h"
#include "AboutDlg.h"
#include "controls.h"
#include "DescriptionManager.h"
#include "CompileSettings.h"

#define ID_CALLLIST 32
#define ID_SETTINGLIST 33
#define ID_NEWTOOL 34
#define ID_REMTOOL 35
#define ID_COMPILE 36
#define ID_COMMANDVIEW 37

#define ID_MHIDE 653
#define ID_MSHOW 654
#define ID_MEXIT 655

#define ID_USERLEVELS 700

#define ID_MENU_TOOLSTART 3000
#define ID_MENU_OPTIONSTART 5000
#define ID_MENU_OPTION_INFO 4999

#define WM_SHELLNOTIFY WM_USER+3245

namespace Factory
{
	class CApplication : public CWin
	{
	private:
		HWND hConfig, hBuildmap;
		int iWidth, iHeight;
		RECT rcConfig, rcBuildmap;
		CWTreeView* pCallList;
		CWTreeView* pSettingList;
		CWButton* pNewCall;
		CWButton* pRemCall;
		CWButton* pCompile;
		CWEdit* pCommandview;

		CCall* pSelectedCall;
		CParam* pSelectedParam;

		HMENU newToolMenu;
		HMENU newParamMenu;
		HMENU hSystrayMenu;
		NOTIFYICONDATA Notify;

		CCompileSettings* pCurrentDoc;
	private:
		void InitGUI();
		void InitTrayMenu();
		void InitUserlevelMenu();
		void SizingGUI(RECT* rc);
		void ResizeGUI();

		void RefreshBuildMap();
		void RefreshSettingList();
		void RefreshCallList();
		void RefreshConfig(CCall* call);
		void RefreshParam(CParam* param);

		void ClearBuildMap();
		void ClearConfigValues();
		void ClearParamValues();

		void SetDlgItem(int item, const char* text);
		void AddListItem(int item, const char* text, LPARAM data);
		void AddComboItem(int item, const char* text, LPARAM data);

		void SaveTextValue();
		void SaveEnumValue();
	public:
		CApplication();
		~CApplication();

		static CCompileSettings* GetCurrentDoc();

		LRESULT MsgProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

		void ConfigProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
		static LRESULT DlgProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

		void MapProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
		static LRESULT StaticMapProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
	};
}
#endif
