#ifndef RX_APP_H
#define RX_APP_H

#include "RXWindow.h"
#include "RXWindowClass.h"

namespace RX
{
	
	class RXApp
	{
	public:
		RXApp() = default;
		RXApp(const RXApp& app) = delete;
		virtual ~RXApp() = default;

		virtual INT32 Run() = 0;
	};

} // namespace RX end

#endif