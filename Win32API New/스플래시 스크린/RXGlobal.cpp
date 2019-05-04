#include "RXGlobal.h"

namespace RX
{

	namespace RXGlobal
	{

		HINSTANCE      g_hMainInstance = nullptr;
		RXStringVector g_windowClassStringVector;
		bool           g_bRunMainWindow = false;

		std::wstring MakeFormatString(const WCHAR* szFormat, ...)
		{
			va_list va = nullptr;
			va_start(va, szFormat);

			INT32 strLength = _vscwprintf(szFormat, va) + 1;

			WCHAR* szBuffer = nullptr;
			szBuffer = reinterpret_cast<WCHAR*>(std::malloc(strLength * sizeof(WCHAR)));
			::ZeroMemory(szBuffer, (strLength * sizeof(WCHAR)));

			vswprintf_s(szBuffer, strLength, szFormat, va);
			va_end(va);

			std::wstring szResult = szBuffer;
			free(szBuffer);

			return szResult;
		}

		void DrawLineSegment(HDC hDC, INT32 startX, INT32 startY, INT32 endX, INT32 endY)
		{
			::MoveToEx(hDC, startX, startY, nullptr);
			::LineTo(hDC, endX, endY);
		}

		RECT ConvertChildToParentClientRect(HWND hChildWnd)
		{
			RECT rtResult = { 0, 0, 0, 0 };
			HWND hParentWnd = ::GetParent(hChildWnd);
			if (hParentWnd == nullptr)
			{
				ERRMSGBOX(L"�θ� �����찡 �����ϴ�!");
				return rtResult;
			}
			
			// left, top�� right, bottom �ѹ��� �ϴ� �Ͱ� ����
			::GetWindowRect(hChildWnd, &rtResult);
			::ScreenToClient(hChildWnd, reinterpret_cast<POINT*>(&rtResult.left));
			::ScreenToClient(hChildWnd, reinterpret_cast<POINT*>(&rtResult.right));
			
			// �� �Լ��� Ŭ���̾�Ʈ ���������� �۵���...
			::MapWindowPoints(hChildWnd, hParentWnd, reinterpret_cast<POINT*>(&rtResult), 2);

			return rtResult;
		}

		void DrawRect(HDC hDC, const RECT& rt)
		{
			::Rectangle(hDC, rt.left, rt.top, rt.right, rt.bottom);
		}

		void AdjustClientRect(HWND hWnd, INT32 width, INT32 height)
		{
			DWORD dwStyle   = ::GetWindowLongPtr(hWnd, GWL_STYLE);
			DWORD dwStyleEx = ::GetWindowLongPtr(hWnd, GWL_EXSTYLE);
			BOOL  bMenu     = (::GetMenu(hWnd) != nullptr);

			RECT rtClient = { 0, 0, width, height };
			::AdjustWindowRectEx(&rtClient, dwStyle, bMenu, dwStyleEx);
			
			// ===============================================
			// ��ũ�ѹ� ����
			if (dwStyle & WS_HSCROLL)
			{
				rtClient.right += ::GetSystemMetrics(SM_CXHSCROLL);
			}

			if (dwStyle & WS_HSCROLL)
			{
				rtClient.bottom += ::GetSystemMetrics(SM_CXVSCROLL);
			}
			// ===============================================
			
			::SetWindowPos(hWnd, nullptr, 0, 0, rtClient.right - rtClient.left,
				rtClient.bottom - rtClient.top, SWP_NOMOVE | SWP_NOZORDER);
		}

		void DrawBimapExcludeColorKey(HDC hDC, HBITMAP hBitmap,
			INT32 x, INT32 y, COLORREF colorKey, bool bCenter)
		{
			HDC hMemDC = ::CreateCompatibleDC(hDC);
			HBITMAP hOldBitmap = SelectBitmap(hMemDC, hBitmap);

			BITMAP bitmapInfo;
			::GetObject(hBitmap, sizeof(bitmapInfo), &bitmapInfo);

			POINT ptDraw;
			if (bCenter == true)
			{
				ptDraw.x = (x / 2) - (bitmapInfo.bmWidth / 2);
				ptDraw.y = (y / 2) - (bitmapInfo.bmHeight / 2);
			}
			else
			{
				ptDraw.x = x;
				ptDraw.y = y;
			}

			::GdiTransparentBlt(hDC, ptDraw.x, ptDraw.y, bitmapInfo.bmWidth, bitmapInfo.bmHeight,
				hMemDC, 0, 0, bitmapInfo.bmWidth, bitmapInfo.bmHeight, colorKey);

			SelectBitmap(hMemDC, hOldBitmap);
			::DeleteDC(hMemDC);
		}

		POINT CalcCenterPosByScreen(INT32 width, INT32 height)
		{
			POINT pt;
			pt.x = (::GetSystemMetrics(SM_CXSCREEN) / 2) - (width / 2);
			pt.y = (::GetSystemMetrics(SM_CYSCREEN) / 2) - (height / 2);
			return pt;
		}

	} // namespace RXGlobal end

} // namespace RX end