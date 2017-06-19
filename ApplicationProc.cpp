#include "CApplication.h"
#include "InputBox.h"

LRESULT Factory::CApplication::MsgProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_CREATE:
		{
			InitGUI();
			InitTrayMenu();
			InitUserlevelMenu();

			pSelectedCall = 0;
			pSelectedParam = 0;
			
			int start = ID_USERLEVELS_INFORMATION+1;
			int end = ID_USERLEVELS_INFORMATION+1+CDescriptionManager::Instance()->GetNumUserlevels();
			CheckMenuRadioItem(m_hMenu, start, end, start+pCurrentDoc->GetUserlevel(), TRUE);
			break;
		}

	case WM_SIZING:
		{
			SizingGUI((RECT*)lParam);
			break;
		}

	case WM_SIZE:
		{
			iWidth = LOWORD(lParam);
			iHeight = HIWORD(lParam);

			ResizeGUI();
			break;
		}

	case WM_NOTIFY:
		{
			switch (((LPNMHDR)lParam)->idFrom)
			{
			case ID_CALLLIST:
				{
					switch (((LPNMHDR)lParam)->code)
					{
					case TVN_SELCHANGED:
						{
							NMTREEVIEW* pnmtv = (LPNMTREEVIEW)lParam;
							int index = (int)pCallList->GetItemData(pnmtv->itemNew.hItem);
							CCall* call = pCurrentDoc->GetCallCenter()->GetCall(index);
							RefreshConfig(call);
							break;
						}

					case NM_CLICK:
						{
							HTREEITEM hItem = pCallList->HitTestCursor();

							if (hItem)
							{
								int index = (int)pCallList->GetItemData(hItem);
								CCall* call = pCurrentDoc->GetCallCenter()->GetCall(index);

								call->Run(pCallList->GetCheckState(hItem));
							}
							break;
						}
					}
					break;
				}

			case ID_SETTINGLIST:
				{
					switch (((LPNMHDR)lParam)->code)
					{
					case NM_DBLCLK:
						{
							char* res = CWCommondlg::Directory(hWnd);
							if (res && strcmp(res, "") != 0)
							{
								int index = pSettingList->GetItemData(pSettingList->GetSelectedItem());
								pCurrentDoc->GetCallCenter()->GetSetting(index)->SetValue(res);
								RefreshSettingList();
							}
							break;
						}
					}
					break;
				}
			}
			break;
		}

	case WM_COMMAND:
		{
			switch (LOWORD(wParam))
			{
			case ID_NEWTOOL:
				{
					switch (HIWORD(wParam))
					{
					case BN_CLICKED:
						{
							RECT rc;
							pNewCall->GetRect(&rc);
							TrackPopupMenu(newToolMenu, 0, rc.left, rc.bottom, 0, m_hWnd, 0);
							break;
						}
					}
					break;
				}

			case ID_REMTOOL:
				{
					switch (HIWORD(wParam))
					{
					case BN_CLICKED:
						{
							if (!pSelectedCall)
								break;

							pCurrentDoc->GetCallCenter()->RemoveCall(pSelectedCall);
							pSelectedCall = 0;

							RefreshCallList();
							RefreshSettingList();
							ClearConfigValues();
							ClearParamValues();
							break;
						}
					}
					break;
				}

			case ID_MSHOW:
				{
					ShowWindow(m_hWnd,SW_SHOW);
					ShowWindow(m_hWnd,SW_RESTORE);
					RemoveMenu(hSystrayMenu, ID_MSHOW, MF_BYCOMMAND);
					InsertMenu(hSystrayMenu, 0, MF_BYPOSITION, ID_MHIDE, "Hide");
					break;
				}

			case ID_MHIDE:
				{
					ShowWindow(m_hWnd,SW_HIDE);
					RemoveMenu(hSystrayMenu, ID_MHIDE, MF_BYCOMMAND);
					InsertMenu(hSystrayMenu, 0, MF_BYPOSITION, ID_MSHOW, "Show");
					break;
				}

			case ID_MEXIT:
				{
					DestroyWindow(hWnd);
					break;
				}

			case ID_USERLEVELS_INFORMATION:
				{
					break;
				}

			case ID_HELP_ABOUT:
				{
					CAboutDlg dlg;
					dlg.ShowModal(m_hInstance, hWnd);
					break;
				}

			default:
				{
					int val = LOWORD(wParam);

					if (val-ID_MENU_TOOLSTART >= 0 && val-ID_MENU_TOOLSTART < CDescriptionManager::Instance()->GetNumTools()+CDescriptionManager::Instance()->GetNumSettings())
					{
						if (val-ID_MENU_TOOLSTART < CDescriptionManager::Instance()->GetNumSettings())
						{
							CSetting* st = CDescriptionManager::Instance()->GetSetting(val-ID_MENU_TOOLSTART);
							if (st)
							{
								pCurrentDoc->GetCallCenter()->NewSetting(st->GetSettingName());
								RefreshSettingList();
							}
						}
						else
						{
							CToolDescription* tl = CDescriptionManager::Instance()->GetTool(val-ID_MENU_TOOLSTART-CDescriptionManager::Instance()->GetNumSettings());
							if (tl)
							{
								CTool* pNewTool = new CTool(tl->GetToolName());

								pCurrentDoc->GetCallCenter()->NewCall(pNewTool);
								RefreshCallList();
							}
						}
						break;
					}
					else if (val-(ID_USERLEVELS_INFORMATION+1) >= 0 && val-(ID_USERLEVELS_INFORMATION+1) < CDescriptionManager::Instance()->GetNumUserlevels())
					{
						pCurrentDoc->SetUserlevel(val-ID_USERLEVELS_INFORMATION);

						int start = ID_USERLEVELS_INFORMATION+1;
						int end = ID_USERLEVELS_INFORMATION+CDescriptionManager::Instance()->GetNumUserlevels()+1;
						CheckMenuRadioItem(m_hMenu, start, end, val, TRUE);
					}
					break;
				}
			}
			break;
		}

	case WM_SHELLNOTIFY:
		{
			if(lParam == WM_RBUTTONDOWN)
			{
				POINT pt;
				GetCursorPos(&pt);
				SetForegroundWindow(hWnd);
				TrackPopupMenu(hSystrayMenu, TPM_RIGHTALIGN | TPM_BOTTOMALIGN, pt.x, pt.y, NULL, hWnd, NULL);            
			}
			else if(lParam == WM_LBUTTONDBLCLK)
			{
				ShowWindow(m_hWnd, SW_SHOW);
				ShowWindow(m_hWnd, SW_RESTORE);
				if (RemoveMenu(hSystrayMenu, ID_MSHOW, MF_BYCOMMAND))
					InsertMenu(hSystrayMenu, 0, MF_BYPOSITION, ID_MHIDE, "Hide");	              
			}
			break;
		}

	case WM_DESTROY:
		{
			Shell_NotifyIcon(NIM_DELETE, &Notify);
			PostQuitMessage(0);
			break;
		}
	}
	return CWin::MsgProc(hWnd, uMsg, wParam, lParam);
}
