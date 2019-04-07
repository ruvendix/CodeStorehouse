#include "RXNewWindow.h"

namespace RX
{

	RXNewWindow::RXNewWindow() : RXWindow()
	{

	}

	RXNewWindow::RXNewWindow(const std::wstring& szWndTtile) : RXWindow(szWndTtile)
	{

	}

	void RXNewWindow::OnLButtonDown(HWND hWnd, BOOL bDoubleClick,
		INT32 x, INT32 y, UINT keyFlags)
	{
		::MessageBox(hWnd, L"(RXNewWindow) 마우스 왼쪽 버튼 클릭!", L"캡션", MB_OK);
	}

} // namespace RX end
