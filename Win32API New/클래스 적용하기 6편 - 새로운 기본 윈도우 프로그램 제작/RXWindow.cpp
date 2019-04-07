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
		::MessageBox(hWnd, L"(RXWindow) 마우스 왼쪽 버튼 클릭!", L"캡션", MB_OK);
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
			nullptr, nullptr, RXGlobal::m_hMainInstance, this);

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