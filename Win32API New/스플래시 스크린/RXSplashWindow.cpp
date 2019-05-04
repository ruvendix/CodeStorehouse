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
			ERRMSGBOX(_T("��Ʈ�� �ε� ����!"));
			return FALSE;
		}

		// WS_EX_LAYERED�� �����ϸ� �ݵ��
		// SetLayeredWindowAttributes() �Ǵ�
		// UpdateLayeredWindow()�� �ٷ� ȣ���ؾ� ���� �۵��� ����˴ϴ�!
		// ���÷��� ��ũ���� ������ �������� �ϹǷ� WS_EX_TOPMOST�� �����մϴ�.
		// �۾� ǥ���ٰ� ��Ʈ�� ��Ͽ��� ������� WS_EX_TOOLWINDOW�� �����ϸ� �˴ϴ�.
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