#ifndef RX_CUSTOM_WINDOW_APP_H
#define RX_CUSTOM_WINDOW_APP_H

#include "RXWindowApp.h"

namespace RX
{

	class RXCustomWindowApp : public RXWindowApp
	{
	public:
		using RXWindowApp::RXWindowApp;
		
		RXCustomWindowApp() = default;
		virtual ~RXCustomWindowApp() = default;

		virtual HRESULT InitWindowClass() override;
		virtual INT32   Run() override;
	};

} // namespace RX end

#endif