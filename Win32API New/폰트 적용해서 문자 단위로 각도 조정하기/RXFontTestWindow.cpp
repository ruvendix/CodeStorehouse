#include "RXFontTestWindow.h"

namespace RX
{	

	void RXFontTestWindow::OnPaint(HWND hWnd)
	{
		PAINTSTRUCT ps;
		HDC hDC = BeginPaint(hWnd, &ps);
		
		// ==========================================================
		// �׸��� �۾��� ó���մϴ�.
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
		logFont.lfEscapement   = 50;  // ��ü ���ڿ� ���� ���� (lfOrientation�� ����)
		logFont.lfOrientation  = 1800; // ���ڸ��� ���� ���� (������ 0��)

		StringCchCopy(logFont.lfFaceName, LF_FACESIZE, L"Kostar");

		HFONT hFont = ::CreateFontIndirect(&logFont);
		HFONT hOldFont = SelectFont(hDC, hFont);

		TCHAR szTest[] = _T("��Ÿũ����Ʈ2 ��Ʈ!");

		::SetTextColor(hDC, RGB(255, 255, 0));
		::SetBkMode(hDC, TRANSPARENT);

		// �׷��Ƚ� ��� ���� ��
		::DrawText(hDC, szTest, _TRUNCATE, &m_rtClient, DT_SINGLELINE | DT_VCENTER | DT_CENTER);

		// �׷��Ƚ� ��带 GM_ADVANCED�� �����մϴ�.
		::SetGraphicsMode(hDC, GM_ADVANCED);

		// �׷��Ƚ� ��� ���� ��
		::DrawText(hDC, szTest, _TRUNCATE, &m_rtClient, DT_SINGLELINE | DT_VCENTER | DT_CENTER);

		SelectFont(hDC, hOldFont);
		DeleteFont(hFont);
		
		// �׷��Ƚ� ��带 GM_COMPATIBLE�� �����մϴ�.
		::SetGraphicsMode(hDC, GM_COMPATIBLE);
		// ==========================================================

		EndPaint(hWnd, &ps);
	}

} // namespace RX end