#include "RXSplashWindow.h"

namespace RX
{

	BOOL RXSplashWindow::OnCreate(HWND hWnd, CREATESTRUCT * pCreateStruct)
	{
		std::srand(::timeGetTime());
		std::wstring szFilePath =
			RXGlobal::MakeFormatString(_T("resource\\splash_%d.bmp"), std::rand() % 6);
		m_hBitmap = static_cast<HBITMAP>(::LoadImage(RXGlobal::g_hMainInstance,
			szFilePath.c_str(), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION));
		
		if (m_hBitmap == nullptr)
		{
			ERRMSGBOX(_T("비트맵 로드 실패!"));
			return FALSE;
		}

		// WS_EX_LAYERED로 설정하면 반드시
		// SetLayeredWindowAttributes() 또는
		// UpdateLayeredWindow()를 바로 호출해야 정상 작동이 보장됩니다!
		// 스플래시 스크린은 무조건 보여져야 하므로 WS_EX_TOPMOST로 설정합니다.
		// 작업 표시줄과 알트탭 목록에서 숨기려면 WS_EX_TOOLWINDOW를 설정하면 됩니다.
		::SetWindowLongPtr(hWnd, GWL_EXSTYLE, ::GetWindowLongPtr(hWnd, GWL_EXSTYLE) |
			WS_EX_LAYERED | WS_EX_TOPMOST | WS_EX_TOOLWINDOW);
		::SetLayeredWindowAttributes(hWnd, RGB(255, 255, 255), 0, LWA_COLORKEY);
		
		::SetTimer(hWnd, 1, 3000, nullptr);
		return TRUE;
	}

	void RXSplashWindow::OnPaint(HWND hWnd)
	{
		PAINTSTRUCT ps;
		HDC hDC = BeginPaint(hWnd, &ps);

		POINT pt = RXGlobal::CalcCenterPosByScreen(getClientWidth(), getClientHeight());
		::SetWindowPos(hWnd, HWND_TOPMOST, pt.x, pt.y, 0, 0, SWP_NOSIZE);

		RXGlobal::DrawBimapExcludeColorKey(hDC, m_hBitmap,
			getClientWidth(), getClientHeight(), RGB(255, 255, 255), true);

		EndPaint(hWnd, &ps);
	}

	void RXSplashWindow::OnDestroy(HWND hWnd)
	{
		::KillTimer(hWnd, 1);
		DeleteBitmap(m_hBitmap);
		RXWindow::OnDestroy(hWnd);
	}

	UINT RXSplashWindow::OnNCHitTest(HWND hWnd, INT32 x, INT32 y)
	{
		INT32 hitResult = ::DefWindowProc(hWnd, WM_NCHITTEST, 0, MAKELPARAM(x, y));
		if (hitResult == HTCLIENT)
		{
			hitResult = HTCAPTION;
		}
		return hitResult;
	}

	void RXSplashWindow::OnTimer(HWND hWnd, UINT id)
	{
		if (id == 1)
		{
			RXGlobal::g_bRunMainWindow = true;
			::SendMessage(hWnd, WM_CLOSE, 0, 0);
		}
	}

} // namespace RX end