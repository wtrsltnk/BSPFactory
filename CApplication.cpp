#include "CApplication.h"
#include <tchar.h>
#include <stdio.h>

/////////////////////////////////////
// Statics
/////////////////////////////////////
LRESULT Factory::CApplication::DlgProc(HWND hDlg, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	Factory::CApplication* app = 0;

	if (uMsg == WM_INITDIALOG)
	{
		app = reinterpret_cast <Factory::CApplication*> (lParam);

		SetWindowLong(hDlg, GWL_USERDATA, lParam);
	}
	else
	{
		app = reinterpret_cast <Factory::CApplication*> (GetWindowLong(hDlg, GWL_USERDATA));
	}

	if (app)
		app->ConfigProc(hDlg, uMsg, wParam, lParam);
	return FALSE;
}

LRESULT Factory::CApplication::StaticMapProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	CApplication* app = 0;

	if (uMsg == WM_INITDIALOG)
	{
		app = reinterpret_cast <Factory::CApplication*> (lParam);

		SetWindowLong(hWnd, GWL_USERDATA, lParam);
	}
	else
	{
		app = reinterpret_cast <Factory::CApplication*> (GetWindowLong(hWnd, GWL_USERDATA));
	}

	if (app)
		app->MapProc(hWnd, uMsg, wParam, lParam);
	return FALSE;
}

/////////////////////////////////////
// Constructors / Destructors      //
/////////////////////////////////////
Factory::CApplication::CApplication()
{
	this->m_dwCreationFlags  = 0L;
	this->m_dwWindowStyle	 = WS_OVERLAPPEDWINDOW;
	this->m_dwExWindowStyle	 = WS_EX_WINDOWEDGE;
	this->m_dwCreationFlags  = SW_SHOW;
	this->m_PosX			 = CW_USEDEFAULT;	
	this->m_PosY			 = CW_USEDEFAULT;	
	this->m_dwCreationWidth  = CW_USEDEFAULT;
	this->m_dwCreationHeight = CW_USEDEFAULT;
	this->m_hbrWindowColor	 = (HBRUSH)(COLOR_WINDOW);
	this->m_hIcon			 = LoadIcon(m_hInstance, MAKEINTRESOURCE(IDI_NANO));
	this->m_strWindowTitle	 = _T("BSP Factory");
	this->m_hMenu			 = LoadMenu(m_hInstance, MAKEINTRESOURCE(IDR_MENU));

	CDescriptionManager::InitInstance("descfile.xml");

	newToolMenu = CreatePopupMenu();

    int i = 0, j = 0;
    for (i = 0; i < CDescriptionManager::Instance()->GetNumSettings(); i++)
	{
		CSetting* st = CDescriptionManager::Instance()->GetSetting(i);
		AppendMenu(newToolMenu, MF_STRING, ID_MENU_TOOLSTART+i, st->GetSettingName());
	}
	
	AppendMenu(newToolMenu, MF_SEPARATOR, 0, 0);

    for (j = 0; j < CDescriptionManager::Instance()->GetNumTools(); j++)
	{
		CToolDescription* tl = CDescriptionManager::Instance()->GetTool(j);
		AppendMenu(newToolMenu, MF_STRING, ID_MENU_TOOLSTART+i+j, tl->GetToolName());
	}

	pSelectedCall = NULL;
	pCurrentDoc = new CCompileSettings();
}


Factory::CApplication::~CApplication()
{
}

/////////////////////////////////////
// Memberfuncties                  //
/////////////////////////////////////

void Factory::CApplication::InitGUI()
{
	RECT wnd, clnt;

	pCallList = new CWTreeView();
	pCallList->SetStyle(TVS_CHECKBOXES|TVS_SHOWSELALWAYS|TVS_FULLROWSELECT);
	pCallList->SetExStyle(WS_EX_STATICEDGE);
	pCallList->Create(m_hWnd, ID_CALLLIST);

	pSettingList = new CWTreeView();
	pSettingList->SetStyle(TVS_CHECKBOXES|TVS_SHOWSELALWAYS|TVS_FULLROWSELECT);
	pSettingList->SetExStyle(WS_EX_STATICEDGE);
	pSettingList->Create(m_hWnd, ID_SETTINGLIST);

	pNewCall = new CWButton();
	pNewCall->Create(m_hWnd, ID_NEWTOOL);
	pNewCall->SetTitle("+");

	pRemCall = new CWButton();
	pRemCall->Create(m_hWnd, ID_REMTOOL);
	pRemCall->SetTitle("-");

	pCompile = new CWButton();
	pCompile->Create(m_hWnd, ID_COMPILE);
	pCompile->SetTitle("Compile");
	
	pCommandview = new CWEdit();
	pCommandview->SetStyle(ES_MULTILINE|ES_AUTOVSCROLL|ES_AUTOHSCROLL|ES_READONLY|WS_BORDER|WS_VSCROLL);
	pCommandview->Create(m_hWnd, ID_COMMANDVIEW);

	hBuildmap = CreateDialogParam(m_hInstance, MAKEINTRESOURCE(IDD_BUILDMAP), m_hWnd, (DLGPROC)StaticMapProc, (LPARAM)this);
	ShowWindow(hBuildmap, SW_SHOW);
	GetWindowRect(hBuildmap, &rcBuildmap);
	rcBuildmap.bottom = rcBuildmap.bottom-rcBuildmap.top;
	rcBuildmap.top = 0;
	rcBuildmap.right = rcBuildmap.right-rcBuildmap.left;
	rcBuildmap.left = 0;

	hConfig = CreateDialogParam(m_hInstance, MAKEINTRESOURCE(IDD_CONFIG), m_hWnd, (DLGPROC)DlgProc, (LPARAM)this);
	ShowWindow(hConfig, SW_SHOW);
	GetWindowRect(hConfig, &rcConfig);
	rcConfig.bottom = rcConfig.bottom-rcConfig.top;
	rcConfig.top = 0;
	rcConfig.right = rcConfig.right-rcConfig.left;
	rcConfig.left = 0;
	
	HFONT font = (HFONT)SendMessage(GetDlgItem(hConfig, IDC_PLUS_PARAMS), WM_GETFONT, 0, 0);
	pNewCall->SetFont(font);
	pRemCall->SetFont(font);
	pCompile->SetFont(font);

	GetWindowRect(m_hWnd, &wnd);
	GetClientRect(m_hWnd, &clnt);

	int resthoogte = (wnd.bottom-wnd.top) - clnt.bottom;
	int totalhoogte = resthoogte + rcBuildmap.bottom + rcConfig.bottom + 30 + 80;

	MoveWindow(m_hWnd, wnd.left, wnd.top, wnd.right-wnd.left, totalhoogte, true);
}

void Factory::CApplication::InitTrayMenu()
{
	hSystrayMenu = CreatePopupMenu();
	AppendMenu(hSystrayMenu, MF_STRING, ID_MHIDE, "Hide");
	AppendMenu(hSystrayMenu, MF_SEPARATOR, 0, 0);
	AppendMenu(hSystrayMenu, MF_STRING, ID_MEXIT, "Exit");
	
	// Create systray icon
	Notify.cbSize				 = sizeof(NOTIFYICONDATA);
	Notify.hIcon				 = LoadIcon(m_hInstance, MAKEINTRESOURCE(IDI_NANO2));
	Notify.hWnd					 = m_hWnd;
	Notify.uCallbackMessage		 = WM_SHELLNOTIFY;
	Notify.uID					 = 23;
	Notify.uFlags				 = NIF_ICON | NIF_MESSAGE | NIF_TIP;
	lstrcpy(Notify.szTip, m_strWindowTitle);
	Shell_NotifyIcon(NIM_ADD, &Notify);
}

void Factory::CApplication::InitUserlevelMenu()
{
	HMENU ulmenu = GetSubMenu(m_hMenu, 0);

	for (int i = 0; i < CDescriptionManager::Instance()->GetNumUserlevels(); i++)
	{
		InsertMenu(ulmenu, i+2, MF_BYPOSITION, ID_USERLEVELS_INFORMATION+i+1, (LPTSTR)CDescriptionManager::Instance()->GetUserLevel(i+1));
	}
}

void Factory::CApplication::SizingGUI(RECT* rc)
{
	RECT wnd, clnt;
	GetWindowRect(m_hWnd, &wnd);
	GetClientRect(m_hWnd, &clnt);

	int resthoogte = (wnd.bottom-wnd.top) - clnt.bottom;
	int restbreedte = (wnd.right-wnd.left) - clnt.right;

	int totalhoogte = resthoogte + rcBuildmap.bottom + rcConfig.bottom + 30 + 80;
	int totalbreedte = restbreedte + rcBuildmap.right + 20 + 300;

	if (rc->bottom-rc->top < totalhoogte)
		rc->bottom = rc->top + totalhoogte;

	if (rc->right-rc->left < totalbreedte)
		rc->right = rc->left + totalbreedte;
}

void Factory::CApplication::ResizeGUI()
{
	pSettingList->Resize(		10, 
						10, 
						iWidth-rcConfig.right-60, 
						(rcBuildmap.bottom + rcConfig.bottom) / 2);

	pCallList->Resize(		10, 
						20 + ((rcBuildmap.bottom + rcConfig.bottom) / 2), 
						iWidth-rcConfig.right-60, 
						((rcBuildmap.bottom + rcConfig.bottom) / 2) - 10);

	pNewCall->Resize(	iWidth-rcConfig.right-40,
						10,
						38,
						20);

	pRemCall->Resize(	iWidth-rcConfig.right-40,
						40,
						38,
						20);

	pCompile->Resize(	iWidth-60,
						rcBuildmap.bottom + rcConfig.bottom,
						50,
						20);

	pCommandview->Resize(10,
						rcBuildmap.bottom + rcConfig.bottom + 30,
						iWidth - 20,
						iHeight - (rcBuildmap.bottom + rcConfig.bottom + 40));

	MoveWindow(			hBuildmap, 
						iWidth - rcConfig.right, 
						10, 
						rcConfig.right, 
						rcBuildmap.bottom, 
						true);

	MoveWindow(			hConfig, 
						iWidth - rcConfig.right, 
						rcBuildmap.bottom, 
						rcConfig.right, 
						rcConfig.bottom, 
						true);
}

void Factory::CApplication::RefreshBuildMap()
{
	SendMessage(GetDlgItem(hBuildmap, IDC_BUILDMAP), WM_SETTEXT, 0, (LPARAM)pCurrentDoc->GetMap()->GetMapName());
}

void Factory::CApplication::RefreshSettingList()
{
	pSettingList->ClearItems();

	for (int i = 0; i < pCurrentDoc->GetCallCenter()->GetNumSettings(); i++)
	{
		CSettingVal* pSetting = pCurrentDoc->GetCallCenter()->GetSetting(i);
		if (pSetting)
		{
			char str[320];
			sprintf(str, "%s=%s", pSetting->GetName(), pSetting->GetValue());
			HTREEITEM item = pSettingList->AddItem(str, TVGN_ROOT, 0, (LPARAM)i);
			pSettingList->SetCheckState(item, pSetting->IsRun());
		}
	}
}

void Factory::CApplication::RefreshCallList()
{
	pSelectedCall = 0;
	pSelectedParam = 0;

	pCallList->ClearItems();

	for (int j = 0; j < pCurrentDoc->GetCallCenter()->GetNumCalls(); j++)
	{
		CCall* pCall = pCurrentDoc->GetCallCenter()->GetCall(j);
		if (pCall)
		{
			HTREEITEM item = pCallList->AddItem(pCall->Call(), TVGN_ROOT, 0, (LPARAM)j);
			pCallList->SetCheckState(item, pCall->IsRun());
		}
	}
	RefreshConfig(pSelectedCall);
}

void Factory::CApplication::RefreshConfig(CCall* call)
{
	if (!call)
		return;

	// Resetting config infoGUI
	pSelectedCall = call;
	pSelectedParam = 0;

	CTool* pTool = call->GetTool();
	CToolDescription* pDesc = CDescriptionManager::Instance()->GetTool(pTool->GetToolName());

	ClearConfigValues();
	
	// FIlling configGUI
	SetDlgItem(IDC_TOOLNAME, pTool->GetToolName());
	SetDlgItem(IDC_FILENAME, pDesc->GetFileName());
	SetDlgItem(IDC_LOCATION, pTool->GetToolPath());

	for (int i = 0; i < call->GetNumParams(); i++)
		AddListItem(IDC_PARAMS, pDesc->GetOptionByID(call->GetParam(i)->GetID())->GetName(), (LPARAM)i);
}

void Factory::CApplication::RefreshParam(CParam* param)
{
	pSelectedParam = param;

	CTool* pTool = pSelectedCall->GetTool();
	CToolDescription* pDesc = CDescriptionManager::Instance()->GetTool(pTool->GetToolName());

	COption* option = pDesc->GetOptionByID(param->GetID());

	// act as the type of option prefers
	switch (option->GetType())
	{
	case COption::integer:
		{
			ShowWindow(GetDlgItem(hConfig, IDC_LBL_VALUE), SW_SHOW);
			ShowWindow(GetDlgItem(hConfig, IDC_VAL_TEXT), SW_SHOW);
			ShowWindow(GetDlgItem(hConfig, IDC_VAL_TEXT_SAVE), SW_SHOW);
			SetDlgItem(IDC_VAL_TEXT, pSelectedParam->GetValue());
			break;
		}
	case COption::text:
		{
			ShowWindow(GetDlgItem(hConfig, IDC_LBL_VALUE), SW_SHOW);
			ShowWindow(GetDlgItem(hConfig, IDC_VAL_TEXT), SW_SHOW);
			ShowWindow(GetDlgItem(hConfig, IDC_VAL_TEXT_SAVE), SW_SHOW);
			SetDlgItem(IDC_VAL_TEXT, pSelectedParam->GetValue());
			break;
		}
	case COption::enumeration:
		{
			ShowWindow(GetDlgItem(hConfig, IDC_LBL_VALUE), SW_SHOW);
			ShowWindow(GetDlgItem(hConfig, IDC_VAL_ENUM), SW_SHOW);

			for (int i = 0; i < option->GetNumEnums(); i++)
			{
				char* str = option->GetEnum(i);
				AddComboItem(IDC_VAL_ENUM, str, (LPARAM)i);

				// Set the selection to the value used in the parameter
				if (stricmp(pSelectedParam->GetValue(), str) == 0)
					SendMessage(GetDlgItem(hConfig, IDC_VAL_ENUM), CB_SETCURSEL, i, 0);
			}
			break;
		}
	}
}

void Factory::CApplication::SetDlgItem(int item, const char* text)
{
	SendMessage(GetDlgItem(hConfig, item), WM_SETTEXT, 0, (LPARAM)text);
}

void Factory::CApplication::AddListItem(int item, const char* text, LPARAM data)
{
	int index = SendMessage(GetDlgItem(hConfig, item), LB_ADDSTRING, 0, (LPARAM)text);
	SendMessage(GetDlgItem(hConfig, item), LB_SETITEMDATA, index, data);
}

void Factory::CApplication::AddComboItem(int item, const char* text, LPARAM data)
{
	int index = SendMessage(GetDlgItem(hConfig, item), CB_ADDSTRING, 0, (LPARAM)text);
	SendMessage(GetDlgItem(hConfig, item), CB_SETITEMDATA, index, data);
}

void Factory::CApplication::SaveTextValue()
{
	if (!pSelectedParam)
		return;

	if (!pSelectedCall)
		return;

	char value[64];
	SendMessage(GetDlgItem(hConfig, IDC_VAL_TEXT), WM_GETTEXT, 64, (LPARAM)value);
	pSelectedParam->SetValue(value);
}

void Factory::CApplication::SaveEnumValue()
{
	if (!pSelectedParam)
		return;

	int index = SendMessage(GetDlgItem(hConfig, IDC_VAL_ENUM), CB_GETCURSEL, 0, 0);
	
	char value[64];
	SendMessage(GetDlgItem(hConfig, IDC_VAL_ENUM), CB_GETLBTEXT, index, (LPARAM)value);
	pSelectedParam->SetValue(value);
}

void Factory::CApplication::ClearConfigValues()
{
	SetDlgItem(IDC_TOOLNAME, "");
	SetDlgItem(IDC_FILENAME, "");
	SetDlgItem(IDC_LOCATION, "");

	SendMessage(GetDlgItem(hConfig, IDC_PARAMS), LB_RESETCONTENT, 0, 0);
	ClearParamValues();
}

void Factory::CApplication::ClearParamValues()
{
	ShowWindow(GetDlgItem(hConfig, IDC_VAL_ENUM), SW_HIDE);
	ShowWindow(GetDlgItem(hConfig, IDC_VAL_TEXT_SAVE), SW_HIDE);
	ShowWindow(GetDlgItem(hConfig, IDC_VAL_TEXT), SW_HIDE);
	ShowWindow(GetDlgItem(hConfig, IDC_LBL_VALUE), SW_HIDE);

	SendMessage(GetDlgItem(hConfig, IDC_VAL_ENUM), CB_RESETCONTENT, 0, 0);
	SendMessage(GetDlgItem(hConfig, IDC_VAL_TEXT), WM_SETTEXT, 0, (LPARAM)"");
}

CCompileSettings* Factory::CApplication::GetCurrentDoc()
{
	return ((CApplication*)g_pCWin)->pCurrentDoc;
}
