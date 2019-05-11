// =====================================================================================
// Copyright(c) 2019, Ruvendix. All Rights Reserved.
// 
// 이 저작물은 크리에이티브 커먼즈 저작자표시 4.0 국제 라이선스에 따라 이용할 수 있습니다.
// http://creativecommons.org/licenses/by/4.0/
// =====================================================================================
#include "FontAngleWnd.h"

void RXFontAngleWnd::OnPaint(HWND hWnd)
{
	// 반드시 DC를 BeginPaint()로 생성해야 합니다.
	// 그렇지 않으면 WM_PAINT는 삭제되지 않습니다.
	PAINTSTRUCT ps;
	HDC hDC = BeginPaint(hWnd, &ps);

	// ======================================================================
	// 논리 폰트를 생성해서 DC에 적용합니다.
	// 폰트 정보는 많지만 실제로 사용하는 건 많지 않습니다.
	LOGFONT logFont;
	::ZeroMemory(&logFont, sizeof(logFont));
	logFont.lfWidth          = 100;
	logFont.lfHeight         = logFont.lfWidth;
	logFont.lfWeight         = FW_NORMAL;
	logFont.lfCharSet        = DEFAULT_CHARSET;
	logFont.lfPitchAndFamily = FF_DONTCARE;

	// 이탤릭, 줄긋기, 밑줄입니다.
	//logFont.lfItalic     = TRUE;
	//logFont.lfStrikeOut  = TRUE;
	//logFont.lfUnderline  = TRUE;

	// 폰트 각도는 0.1도 단위입니다.
	// 예를 들어 1000이면 100도이고, 20이면 2도입니다.
	logFont.lfEscapement  = 50;   // 전체 문자열 각도를 조정합니다. (lfOrientation과 별개)
	logFont.lfOrientation = 1800; // 문자마다 각도 조정합니다. (시작은 0도)

	// 문자열을 안전하게 복사합니다.
	::StringCchCopy(logFont.lfFaceName, LF_FACESIZE, L"Kostar");

	HFONT hFont    = ::CreateFontIndirect(&logFont);
	HFONT hOldFont = SelectFont(hDC, hFont);

	// ======================================================================
	// 문자열의 출력 정보를 조정한 후, 문자열을 출력합니다.
	TCHAR szTest[] = _T("스타크래프트2 폰트!");

	COLORREF oldTextColor = ::SetTextColor(hDC, RGB(255, 255, 0));
	INT32    oldBKMode    = ::SetBkMode(hDC, TRANSPARENT);

	// 그래픽스 모드 변경 전
	::DrawText(hDC, szTest, _TRUNCATE, &m_clientArea, DT_SINGLELINE | DT_VCENTER | DT_CENTER);

	// 그래픽스 모드를 GM_ADVANCED로 변경합니다.
	// 폰트에 기울기가 적용됩니다.
	::SetGraphicsMode(hDC, GM_ADVANCED);

	// 그래픽스 모드 변경 후
	::DrawText(hDC, szTest, _TRUNCATE, &m_clientArea, DT_SINGLELINE | DT_VCENTER | DT_CENTER);

	// ======================================================================
	// 이전 정보로 복구하고 생성한 폰트를 제거합니다.
	::SetTextColor(hDC, oldTextColor);
	::SetBkMode(hDC, oldBKMode);

	SelectFont(hDC, hOldFont);
	DeleteFont(hFont);

	// 그래픽스 모드를 GM_COMPATIBLE로 변경합니다.
	::SetGraphicsMode(hDC, GM_COMPATIBLE);
	// ==========================================================

	// BeginPaint()로 시작했으면 EndPaint()로 끝내야 합니다.
	EndPaint(hWnd, &ps);
}