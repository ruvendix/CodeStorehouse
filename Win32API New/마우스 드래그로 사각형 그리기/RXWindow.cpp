#include "RXWindow.h"

namespace RX
{

	RXWindow::RXWindow()
	{
		m_szWndTitle = L"RXWindow";
		m_hWnd       = nullptr;
	}

	RXWindow::RXWindow(const std::wstring& szWndTitle)
	{
		m_szWndTitle = szWndTitle;
		m_hWnd       = nullptr;
	}

	void RXWindow::OnLButtonDown(HWND hWnd, BOOL bDoubleClick,
		INT32 x, INT32 y, UINT keyFlags)
	{
		m_bDrag = true;
		m_rtDrag.left = x;
		m_rtDrag.top  = y;
	}

	void RXWindow::OnLButtonUp(HWND hWnd, INT32 x, INT32 y, UINT keyFlags)
	{
		m_bDrag = false;
		::SetRect(&m_rtDrag, 0, 0, 0, 0);
		::InvalidateRect(hWnd, nullptr, TRUE);
	}

	void RXWindow::OnMouseMove(HWND hWnd, INT32 x, INT32 y, UINT keyFlags)
	{
		if (m_bDrag == true)
		{
			m_rtDrag.right  = x;
			m_rtDrag.bottom = y;
			::InvalidateRect(hWnd, nullptr, TRUE);
		}
	}

	void RXWindow::OnPaint(HWND hWnd)
	{
		PAINTSTRUCT ps;
		HDC hDC = BeginPaint(hWnd, &ps);

		LOGPEN logPen;
		logPen.lopnColor = RGB(255, 255, 0);
		logPen.lopnStyle = PS_SOLID;
		logPen.lopnWidth.x = 1;

		HPEN hPen = ::CreatePenIndirect(&logPen);
		HPEN hOldPen = SelectPen(hDC, hPen);
		HBRUSH hOldBrush = SelectBrush(hDC, GetStockBrush(NULL_BRUSH));

		::Rectangle(hDC, m_rtDrag.left, m_rtDrag.top, m_rtDrag.right, m_rtDrag.bottom);

		SelectBrush(hDC, hOldBrush);
		SelectPen(hDC, hOldPen);
		DeletePen(hPen);

		EndPaint(hWnd, &ps);
	}

	void RXWindow::OnKeyDown(HWND hWnd, UINT vKey, BOOL bDown, INT32 repeat, UINT flags)
	{
		switch (vKey)
		{
		case VK_ESCAPE:
		{
			::DestroyWindow(hWnd);
		}
		}
	}

	BOOL RXWindow::OnCreate(HWND hWnd, CREATESTRUCT * pCreateStruct)
	{
		return TRUE;
	}

	void RXWindow::OnClose(HWND hWnd)
	{
		::DestroyWindow(hWnd);
	}

	void RXWindow::OnDestroy(HWND hWnd)
	{
		::PostQuitMessage(EXIT_SUCCESS);
	}

	HRESULT RXWindow::Create(INT32 x, INT32 y, INT32 clientWidth, INT32 clientHeight)
	{
		RECT rtWindow = { 0, 0, clientWidth, clientHeight };
		::AdjustWindowRect(&rtWindow, WS_OVERLAPPEDWINDOW, FALSE);

		INT32 realClientWidth   = rtWindow.right - rtWindow.left;
		INT32 realClientHeiidth = rtWindow.bottom - rtWindow.top;

		m_hWnd = ::CreateWindow(m_szWndTitle.c_str(), m_szWndTitle.c_str(),
			WS_OVERLAPPEDWINDOW, x, y, realClientWidth, realClientHeiidth,
			nullptr, nullptr, RXGlobal::g_hMainInstance, this);

		if (m_hWnd == nullptr)
		{
			ERRMSGBOX(L"윈도우 생성 실패!");
			return E_FAIL;
		}

		::GetClientRect(m_hWnd, &m_rtClient);

		::ShowWindow(m_hWnd, SW_NORMAL);
		::UpdateWindow(m_hWnd);

		return S_OK;
	}

	std::pair<INT32, INT32> RXWindow::getClientWidthAndHeight() const noexcept
	{
		std::pair<INT32, INT32> clientAreaInfo;
		clientAreaInfo.first  = m_rtClient.right - m_rtClient.left;
		clientAreaInfo.second = m_rtClient.bottom - m_rtClient.top;
		return clientAreaInfo;
	}

	void RXWindow::ChangeWindowTitle(const std::wstring& szWndTitle)
	{
		m_szWndTitle = szWndTitle;
		::SetWindowText(m_hWnd, szWndTitle.c_str());
	}

} // namespace RX end