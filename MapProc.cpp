#include "CApplication.h"

void Factory::CApplication::MapProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_COMMAND:
		{
			switch (LOWORD(wParam))
			{
			case IDC_BUILDMAP_OPEN:
				{
					char* res = CWCommondlg::OpenFile(m_hWnd, "Hammer/Worldcraft Maps(*.rmf)\0*.rmf\0Game Maps(*.map)\0*.map", "rmf");
					if (res)
					{
						pCurrentDoc->GetMap()->SetMap(res);
						RefreshBuildMap();
					}
					break;
				}
			}
			break;
		}
	}
}
	