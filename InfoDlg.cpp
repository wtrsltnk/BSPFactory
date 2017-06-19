// InfoDlg.cpp: implementation of the CInfoDlg class.
//
//////////////////////////////////////////////////////////////////////

#include "InfoDlg.h"
#include "CApplication.h"
#include <stdio.h>

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

Factory::CInfoDlg::CInfoDlg()
{
	this->m_dwResourceDlg = IDD_OPTIONINFO;
}

Factory::CInfoDlg::~CInfoDlg()
{
}

int Factory::CInfoDlg::Show(HWND hParent, const char* toolName)
{
	toolDescription = CDescriptionManager::Instance()->GetTool(toolName);

	return CDialog::ShowModal(GetModuleHandle(0), hParent);
}

int Factory::CInfoDlg::GetSelectedOption()
{
	int sel = SendMessage(GetDlgItem(m_hDlg, IDC_OPTIONS), LB_GETCURSEL, 0, 0);
	return (int)SendMessage(GetDlgItem(m_hDlg, IDC_OPTIONS), LB_GETITEMDATA, sel, 0);
}

void Factory::CInfoDlg::ClearOption()
{
	SendMessage(GetDlgItem(m_hDlg, IDC_OPT_NAME), WM_SETTEXT, 0, 0);
	SendMessage(GetDlgItem(m_hDlg, IDC_OPT_TYPE), WM_SETTEXT, 0, 0);
	SendMessage(GetDlgItem(m_hDlg, IDC_OPT_CALL), WM_SETTEXT, 0, 0);
	SendMessage(GetDlgItem(m_hDlg, IDC_OPT_DEFAULT), WM_SETTEXT, 0, 0);
	SendMessage(GetDlgItem(m_hDlg, IDC_OPT_USERLEVEL), WM_SETTEXT, 0, 0);
	SendMessage(GetDlgItem(m_hDlg, IDC_OPT_DESCRIPTION), WM_SETTEXT, 0, 0);
	SendMessage(GetDlgItem(m_hDlg, IDC_OPT_ENUMS), WM_SETTEXT, 0, 0);
}

void Factory::CInfoDlg::FillOption(COption* option)
{
	char* text;

	SendMessage(GetDlgItem(m_hDlg, IDC_OPT_NAME), WM_SETTEXT, 0, (LPARAM)option->GetName());
	SendMessage(GetDlgItem(m_hDlg, IDC_OPT_CALL), WM_SETTEXT, 0, (LPARAM)option->GetCall());
	SendMessage(GetDlgItem(m_hDlg, IDC_OPT_DEFAULT), WM_SETTEXT, 0, (LPARAM)option->GetDefault());
	SendMessage(GetDlgItem(m_hDlg, IDC_OPT_DESCRIPTION), WM_SETTEXT, 0, (LPARAM)option->GetDescription());
	
	switch (option->GetType())
	{
	case COption::boolean:
			text = "Boolean";
			break;
	case COption::integer:
			text = "Integer";
			break;
	case COption::text:
			text = "text";
			break;
	case COption::enumeration:
			text = "Enumeration";
			break;
	default:
			text = "Undifined";
			break;
	}
	SendMessage(GetDlgItem(m_hDlg, IDC_OPT_TYPE), WM_SETTEXT, 0, (LPARAM)text);

	char enums[1024] = {0};

	for (int i = 0; i < option->GetNumEnums(); i++)
	{
		strcat(enums, option->GetEnum(i));
		strcat(enums, "\r\n");
	}
	SendMessage(GetDlgItem(m_hDlg, IDC_OPT_ENUMS), WM_SETTEXT, 0, (LPARAM)enums);

	SendMessage(GetDlgItem(m_hDlg, IDC_OPT_USERLEVEL), WM_SETTEXT, 0, 0);
}

void Factory::CInfoDlg::DlgProc(UINT uMsg, WPARAM wParam, LPARAM lParam)
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

			char str[64];
			sprintf(str, "Information about options for the %s tool", toolDescription->GetToolName());
			SendMessage(m_hDlg, WM_SETTEXT, 0, (LPARAM)str);
			for (int i = 0; i < toolDescription->GetNumOptions(); i++)
			{
				COption* option = toolDescription->GetOption(i);
				if (option->GetUserLevel() >= CApplication::GetCurrentDoc()->GetUserlevel())
				{
					int index = SendMessage(GetDlgItem(m_hDlg, IDC_OPTIONS), LB_ADDSTRING, 0, (LPARAM)option->GetName());
					SendMessage(GetDlgItem(m_hDlg, IDC_OPTIONS), LB_SETITEMDATA, index, (LPARAM)option->GetID());
				}
			}
			break;
		}

	case WM_COMMAND:
		{
			switch (LOWORD(wParam))
			{
			case IDC_OPTIONS:
				{
					switch (HIWORD(wParam))
					{
					case LBN_SELCHANGE:
						{
							ClearOption();

							COption* option = toolDescription->GetOptionByID(GetSelectedOption());
							
							if (option)
								FillOption(option);
							break;
						}
					}
					break;
				}
			}
			break;
		}
	}

	CDialog::DlgProc(uMsg, wParam, lParam);
}
