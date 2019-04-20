#ifndef RX_WINDOW_APP_H
#define RX_WINDOW_APP_H

#include "RXApp.h"

namespace RX
{

	enum APP_WINDOW_INFO
	{
		POSITION,
		AREA,
		MAX,
	};

	class RXWindowApp : public RXApp
	{
	public:
		RXWindowApp();
		RXWindowApp(const std::wstring& szTitle, INT32 x, INT32 y,
			INT32 clientWidth, INT32 clientHeight);
		RXWindowApp(const RXWindowApp& app) = delete;
		virtual ~RXWindowApp();

		virtual INT32 Run() override;

		// ============================================================
		// Setter
		void setRXWindow(RXWindow* pWindow)
		{
			m_pWindow = pWindow;
		}

	private:
		std::pair<INT32, INT32> m_windowInfo[APP_WINDOW_INFO::MAX]; // ��ǥ, ����

		RXWindowClass m_windowClass;
		RXWindow*     m_pWindow;
	};

} // namespace RX end

#endif