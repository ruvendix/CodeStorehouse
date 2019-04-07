#ifndef RX_WINDOW_APP_H
#define RX_WINDOW_APP_H

#include "RXApp.h"
#include "RXNewWindow.h"

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
		virtual ~RXWindowApp() = default;

		virtual INT32 Run() override;

	private:
		std::pair<INT32, INT32> m_windowInfo[APP_WINDOW_INFO::MAX]; // ÁÂÇ¥, ¿µ¿ª

		RXWindowClass m_windowClass;
		RXWindow      m_window;
	};

} // namespace RX end

#endif