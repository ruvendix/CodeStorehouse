#include "RXWindow.h"

namespace RX
{

	RXWindow::RXWindow(const std::wstring& szWndTitle)
	{
		m_szWndTitle = szWndTitle;
		m_hWnd       = nullptr;
	}

	void RXWindow::OnDestroy(HWND hWnd)
	{
		::PostQuitMessage(EXIT_SUCCESS);
	}

	HRESULT RXWindow::Create(INT32 x, INT32 y, INT32 clientWidth, INT32 clientHeight)
	{
		m_hWnd = ::CreateWindow(m_szWndTitle.c_str(), m_szWndTitle.c_str(),
			WS_OVERLAPPEDWINDOW, x, y, clientWidth, clientHeight,
			nullptr, nullptr, RXGlobal::m_hMainInstance, this);
			
		::ShowWindow(m_hWnd, SW_NORMAL);
		::UpdateWindow(m_hWnd);

		return S_OK;
	}

	void RXWindow::ChangeWindowTitle(const std::wstring & szWndTitle)
	{
		m_szWndTitle = szWndTitle;
		::SetWindowText(m_hWnd, szWndTitle.c_str());
	}

} // namespace RX end