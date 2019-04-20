#ifndef RX_FONTTEST_WINDOW_H_
#define RX_FONTTEST_WINDOW_H_

#include "common.h"
#include "RXWindow.h"

namespace RX
{

	class RXFontTestWindow : public RXWindow
	{
	public:
		RXFontTestWindow() = default;
		virtual ~RXFontTestWindow() = default;

		// ============================================================
		// 메시지 핸들러
		virtual void OnPaint(HWND hWnd) override;
	};

} // namespace RX end

#endif