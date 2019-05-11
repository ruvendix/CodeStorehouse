#include "RXFontTestWindow.h"

namespace RX
{	

	void RXFontTestWindow::OnPaint(HWND hWnd)
	{
		PAINTSTRUCT ps;
		HDC hDC = BeginPaint(hWnd, &ps);
		
		// ==========================================================
		// 그리기 작업을 처리합니다.
		LOGFONT logFont;
		::ZeroMemory(&logFont, sizeof(logFont));
		logFont.lfWidth          = 100;
		logFont.lfHeight         = logFont.lfWidth;
		logFont.lfWeight         = FW_NORMAL;
		logFont.lfCharSet        = DEFAULT_CHARSET;
		logFont.lfPitchAndFamily = FF_DONTCARE;
		
		//logFont.lfItalic     = TRUE;
		//logFont.lfStrikeOut  = TRUE;
		//logFont.lfUnderline  = TRUE;
		logFont.lfEscapement   = 50;  // 전체 문자열 각도 조정 (lfOrientation과 별개)
		logFont.lfOrientation  = 1800; // 문자마다 각도 조정 (시작은 0도)

		StringCchCopy(logFont.lfFaceName, LF_FACESIZE, L"Kostar");

		HFONT hFont = ::CreateFontIndirect(&logFont);
		HFONT hOldFont = SelectFont(hDC, hFont);

		TCHAR szTest[] = _T("스타크래프트2 폰트!");

		::SetTextColor(hDC, RGB(255, 255, 0));
		::SetBkMode(hDC, TRANSPARENT);

		// 그래픽스 모드 변경 전
		::DrawText(hDC, szTest, _TRUNCATE, &m_rtClient, DT_SINGLELINE | DT_VCENTER | DT_CENTER);

		// 그래픽스 모드를 GM_ADVANCED로 변경합니다.
		::SetGraphicsMode(hDC, GM_ADVANCED);

		// 그래픽스 모드 변경 후
		::DrawText(hDC, szTest, _TRUNCATE, &m_rtClient, DT_SINGLELINE | DT_VCENTER | DT_CENTER);

		SelectFont(hDC, hOldFont);
		DeleteFont(hFont);
		
		// 그래픽스 모드를 GM_COMPATIBLE로 변경합니다.
		::SetGraphicsMode(hDC, GM_COMPATIBLE);
		// ==========================================================

		EndPaint(hWnd, &ps);
	}

} // namespace RX end