#ifndef RX_LAYERED_WINDOW_H_
#define RX_LAYERED_WINDOW_H_

#include "RXCommon.h"
#include "RXWindow.h"

namespace RX
{

	class RXLayeredWindow : public RXWindow
	{
	public:
		using RXWindow::RXWindow;

		RXLayeredWindow() = default;
		virtual ~RXLayeredWindow() = default;

		// ============================================================
		// �޽��� �ڵ鷯
		virtual BOOL OnCreate(HWND hWnd, CREATESTRUCT* pCreateStruct) override;
		virtual void OnPaint(HWND hWnd) override;
		virtual void OnDestroy(HWND hWnd) override;
		virtual UINT OnNCHitTest(HWND hWnd, INT32 x, INT32 y) override;
		virtual void OnTimer(HWND hWnd, UINT id) override;

	private:
		HBITMAP m_hBitmap = nullptr;
	};

} // namespace RX end

#endif