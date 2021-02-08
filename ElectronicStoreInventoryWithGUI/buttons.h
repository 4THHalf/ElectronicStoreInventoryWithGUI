#pragma once

#include <windows.h>
#include <winuser.h>

class Button : public Control
{
public:
	HRESULT CreateText(HWND hParent, const TCHAR* szCaption, int nID, const Rect& rcBound);
	HRESULT CreateBitmap(HWND hParent, int nImgID, int nID, const Rect& rcBound);
	BOOL SetImage(WORD nImgId);

	void SetCheck(int nCheck)
	{
		SendMessage(BM_SETCHECK, (WPARAM)nCheck, 0L);
	}

	BOOL IsChecked()
	{
		return SendMessage(BM_GETCHECK, 0, 0) == BST_CHECKED;
	}
};
