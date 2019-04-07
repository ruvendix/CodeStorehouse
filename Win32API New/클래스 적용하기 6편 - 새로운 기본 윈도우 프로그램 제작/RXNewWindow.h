#ifndef RX_NEW_WINDOW_H_
#define RX_NEW_WINDOW_H_

#include "RXWindow.h"

namespace RX
{

	class RXNewWindow : public RXWindow
	{
	public:
		RXNewWindow();
		RXNewWindow(const std::wstring& szWndTtile);
		virtual ~RXNewWindow() = default;

		// ============================================================
		// 메시지 핸들러
		virtual void OnLButtonDown(HWND hWnd, BOOL bDoubleClick, 
			INT32 x, INT32 y, UINT keyFlags);
	};

} // namespace RX end

#endif