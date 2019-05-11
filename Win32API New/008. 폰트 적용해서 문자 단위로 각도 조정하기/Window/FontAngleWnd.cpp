// =====================================================================================
// Copyright(c) 2019, Ruvendix. All Rights Reserved.
// 
// �� ���۹��� ũ������Ƽ�� Ŀ���� ������ǥ�� 4.0 ���� ���̼����� ���� �̿��� �� �ֽ��ϴ�.
// http://creativecommons.org/licenses/by/4.0/
// =====================================================================================
#include "FontAngleWnd.h"

void RXFontAngleWnd::OnPaint(HWND hWnd)
{
	// �ݵ�� DC�� BeginPaint()�� �����ؾ� �մϴ�.
	// �׷��� ������ WM_PAINT�� �������� �ʽ��ϴ�.
	PAINTSTRUCT ps;
	HDC hDC = BeginPaint(hWnd, &ps);

	// ======================================================================
	// �� ��Ʈ�� �����ؼ� DC�� �����մϴ�.
	// ��Ʈ ������ ������ ������ ����ϴ� �� ���� �ʽ��ϴ�.
	LOGFONT logFont;
	::ZeroMemory(&logFont, sizeof(logFont));
	logFont.lfWidth          = 100;
	logFont.lfHeight         = logFont.lfWidth;
	logFont.lfWeight         = FW_NORMAL;
	logFont.lfCharSet        = DEFAULT_CHARSET;
	logFont.lfPitchAndFamily = FF_DONTCARE;

	// ���Ÿ�, �ٱ߱�, �����Դϴ�.
	//logFont.lfItalic     = TRUE;
	//logFont.lfStrikeOut  = TRUE;
	//logFont.lfUnderline  = TRUE;

	// ��Ʈ ������ 0.1�� �����Դϴ�.
	// ���� ��� 1000�̸� 100���̰�, 20�̸� 2���Դϴ�.
	logFont.lfEscapement  = 50;   // ��ü ���ڿ� ������ �����մϴ�. (lfOrientation�� ����)
	logFont.lfOrientation = 1800; // ���ڸ��� ���� �����մϴ�. (������ 0��)

	// ���ڿ��� �����ϰ� �����մϴ�.
	::StringCchCopy(logFont.lfFaceName, LF_FACESIZE, L"Kostar");

	HFONT hFont    = ::CreateFontIndirect(&logFont);
	HFONT hOldFont = SelectFont(hDC, hFont);

	// ======================================================================
	// ���ڿ��� ��� ������ ������ ��, ���ڿ��� ����մϴ�.
	TCHAR szTest[] = _T("��Ÿũ����Ʈ2 ��Ʈ!");

	COLORREF oldTextColor = ::SetTextColor(hDC, RGB(255, 255, 0));
	INT32    oldBKMode    = ::SetBkMode(hDC, TRANSPARENT);

	// �׷��Ƚ� ��� ���� ��
	::DrawText(hDC, szTest, _TRUNCATE, &m_clientArea, DT_SINGLELINE | DT_VCENTER | DT_CENTER);

	// �׷��Ƚ� ��带 GM_ADVANCED�� �����մϴ�.
	// ��Ʈ�� ���Ⱑ ����˴ϴ�.
	::SetGraphicsMode(hDC, GM_ADVANCED);

	// �׷��Ƚ� ��� ���� ��
	::DrawText(hDC, szTest, _TRUNCATE, &m_clientArea, DT_SINGLELINE | DT_VCENTER | DT_CENTER);

	// ======================================================================
	// ���� ������ �����ϰ� ������ ��Ʈ�� �����մϴ�.
	::SetTextColor(hDC, oldTextColor);
	::SetBkMode(hDC, oldBKMode);

	SelectFont(hDC, hOldFont);
	DeleteFont(hFont);

	// �׷��Ƚ� ��带 GM_COMPATIBLE�� �����մϴ�.
	::SetGraphicsMode(hDC, GM_COMPATIBLE);
	// ==========================================================

	// BeginPaint()�� ���������� EndPaint()�� ������ �մϴ�.
	EndPaint(hWnd, &ps);
}