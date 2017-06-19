#include "CApplication.h"
#include <stdio.h>

void Factory::CApplication::ConfigProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_COMMAND:
		{
			switch (LOWORD(wParam))
			{
			case IDC_PLUS_PARAMS:
				{
					if (!pSelectedCall)
						break;

					CTool* pTool = pSelectedCall->GetTool();
					CToolDescription* pDesc = CDescriptionManager::Instance()->GetTool(pTool->GetToolName());

					// Create a menu with all options
					newParamMenu = CreatePopupMenu();

					for (int i = 0; i < pDesc->GetNumOptions(); i++)
					{
						COption* option = pDesc->GetOption(i);
						if (option->GetUserLevel() >= pCurrentDoc->GetUserlevel())
							AppendMenu(newParamMenu, 0, ID_MENU_OPTIONSTART+i, option->GetName());
					}

					if (GetMenuItemCount(newParamMenu) > 0)
					{
						AppendMenu(newParamMenu, MF_SEPARATOR, 0, 0);
						AppendMenu(newParamMenu, MF_STRING, ID_MENU_OPTION_INFO, "More Info...");
					}
					else
					{
						AppendMenu(newParamMenu, MF_STRING, -1, "No Options in this Userlevel");
					}

					// Show menu
					RECT rc;
					GetWindowRect(GetDlgItem(hConfig, IDC_PLUS_PARAMS), &rc);
					TrackPopupMenu(newParamMenu, 0, rc.left, rc.bottom, 0, hWnd, 0);
					// End Creating menu
					break;
				}

			case IDC_MIN_PARAMS:
				{
					if (!pSelectedParam)
						break;

					if (!pSelectedCall)
						break;
					
					CTool* pTool = pSelectedCall->GetTool();
					CToolDescription* pDesc = CDescriptionManager::Instance()->GetTool(pTool->GetToolName());

					pSelectedCall->RemoveParam(pSelectedParam);
					pSelectedParam = 0;

					RefreshConfig(pSelectedCall);
					break;
				}

			case IDC_BTN_LOCATION:
				{
					if (!pSelectedCall)
						break;

					char filter[255] = {0};
					char defext[255] = {0};

					CTool* pTool = pSelectedCall->GetTool();
					CToolDescription* pDesc = CDescriptionManager::Instance()->GetTool(pTool->GetToolName());

					// Work around to make the openfile dlg work
					sprintf(filter, "%s %s\0", pDesc->GetToolName(), pDesc->GetFileName());
					filter[strlen(pDesc->GetToolName())] = '\0';
					sprintf(defext, "%s\0", pDesc->GetFileName());

					// Get the openfile result
					char* res = CWCommondlg::OpenFile(m_hWnd, filter, defext);

					// Check result and get the path without filename
					if (res)
					{
                        int i = 0;
                        for (i = strlen(res); i > 0; i--)
						{
							if (res[i] == '/')
								break;
						}
						char location[255] = {0};
						strncpy(location, res, i);
						pTool->SetToolPath(location);
					}

					// Refresh screen
					RefreshConfig(pSelectedCall);
					break;
				}

			case IDC_PARAMS:
				{
					switch (HIWORD(wParam))
					{
					case LBN_SELCHANGE:
						{
							if (!pSelectedCall)
								break;

							ClearParamValues();

							// Get tool and description
							CTool* pTool = pSelectedCall->GetTool();
							CToolDescription* pDesc = CDescriptionManager::Instance()->GetTool(pTool->GetToolName());

							// Get selected parameter and option it uses
							int index = SendMessage(GetDlgItem(hWnd, IDC_PARAMS), LB_GETCURSEL, 0, 0);
							DWORD data = SendMessage(GetDlgItem(hWnd, IDC_PARAMS), LB_GETITEMDATA, index, 0);
							
							// Refresh screen
							RefreshParam(pSelectedCall->GetParam((int)data));
							break;
						}
					}
					break;
				}

			case IDC_VAL_ENUM:
				{
					switch (HIWORD(wParam))
					{
					case CBN_SELCHANGE:
						{
							SaveEnumValue();
							break;
						}
					}
					break;
				}

			case IDC_VAL_TEXT_SAVE:
				{
					switch (HIWORD(wParam))
					{
					case BN_CLICKED:
						{
							SaveTextValue();
							break;
						}
					}
					break;
				}

			case ID_MENU_OPTION_INFO:
				{
					CInfoDlg dlg;
					dlg.Show(hWnd, pSelectedCall->GetTool()->GetToolName());
					break;
				}

			default:
				{
					int val = LOWORD(wParam)-ID_MENU_OPTIONSTART;
					if (val >= 0 && val < CDescriptionManager::Instance()->GetNumTools())
					{
						if (!pSelectedCall)
							break;

						CTool* pTool = pSelectedCall->GetTool();
						CToolDescription* pDesc = CDescriptionManager::Instance()->GetTool(pTool->GetToolName());

						COption* opt = pDesc->GetOption(val);
						pSelectedCall->AddParam(new CParam(opt->GetID()));
						DestroyMenu(newParamMenu);
					
						// Refresh screen
						RefreshConfig(pSelectedCall);

					}
					break;
				}
			}
			break;
		}
	}
}
