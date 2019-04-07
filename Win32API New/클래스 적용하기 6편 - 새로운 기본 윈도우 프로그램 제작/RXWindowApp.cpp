#include "RXWindowApp.h"

namespace RX
{

	RXWindowApp::RXWindowApp()
	{
		m_windowInfo[APP_WINDOW_INFO::POSITION] = std::make_pair(0, 0);
		m_windowInfo[APP_WINDOW_INFO::AREA]     = std::make_pair(0, 0);
	}

	RXWindowApp::RXWindowApp(const std::wstring& szTitle, INT32 x, INT32 y,
		INT32 clientWidth, INT32 clientHeight)
	{
		m_window.ChangeWindowTitle(szTitle);
		m_windowInfo[APP_WINDOW_INFO::POSITION] = std::make_pair(x, y);
		m_windowInfo[APP_WINDOW_INFO::AREA]     = std::make_pair(clientWidth, clientHeight);
	}

	INT32 RXWindowApp::Run()
	{
		if (FAILED(m_windowClass.Init(m_window.getWindowTitle())))
		{
			return 0;
		}

		if (FAILED(m_window.Create(m_windowInfo[APP_WINDOW_INFO::POSITION].first,
			m_windowInfo[APP_WINDOW_INFO::POSITION].second,
			m_windowInfo[APP_WINDOW_INFO::AREA].first,
			m_windowInfo[APP_WINDOW_INFO::AREA].second)))
		{
			return 0;
		}

		MSG message;
		::ZeroMemory(&message, sizeof(message));

		bool bRun = true;
		while (bRun == true)
		{
			if (message.message == WM_QUIT)
			{
				bRun = false;
			}

			if (::PeekMessage(&message, nullptr, 0, 0, PM_REMOVE) != FALSE)
			{
				::TranslateMessage(&message);
				::DispatchMessage(&message);
			}
		}

		return (message.wParam);
	}

} // namespace RX end