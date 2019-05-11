// =====================================================================================
// Copyright(c) 2019, Ruvendix. All Rights Reserved.
// 
// �� ���۹��� ũ������Ƽ�� Ŀ���� ������ǥ�� 4.0 ���� ���̼����� ���� �̿��� �� �ֽ��ϴ�.
// http://creativecommons.org/licenses/by/4.0/
// =====================================================================================
#include "Global.h"

// static ������� �� ������ �ʱ�ȭ ����Դϴ�.
// ���Ǵ� �ʼ����� �ʱ�ȭ���� ���������� �ʾƵ� �˴ϴ�.
HINSTANCE    RXGlobal::m_hMainInstance           = nullptr;
bool         RXGlobal::m_bRunMainWnd          = false;
const TCHAR* RXGlobal::SZ_WND_PROCEDURE_PROPERTY = _T("WndProcedure");
const TCHAR* RXGlobal::SZ_NULL                   = _T("");

// ���̿� ���̸� �����ϸ� Ŭ���̾�Ʈ ���� �������� ������ ������ �������մϴ�.
// ���� ��� ���̿� 1024�� �����ϰ� ���̿� 768�� �����ϸ�
// Ŭ���̾�Ʈ ������ (1024 * 768)�� �˴ϴ�.
void RXGlobal::AdjustClientArea(HWND hWnd, INT32 width, INT32 height)
{
	// ======================================================================
	// ���� ����� ������ ��Ÿ���� �����մϴ�.
	DWORD dwStyle   = ::GetWindowLongPtr(hWnd, GWL_STYLE);
	DWORD dwStyleEx = ::GetWindowLongPtr(hWnd, GWL_EXSTYLE);
	BOOL  bMenu     = (::GetMenu(hWnd) != nullptr);

	// ======================================================================
	// ��ũ�ѹ� ���̸� �����մϴ�.
	RECT clientArea = { 0, 0, width, height };

	if (dwStyle & WS_HSCROLL)
	{
		clientArea.right += ::GetSystemMetrics(SM_CXHSCROLL);
	}

	if (dwStyle & WS_HSCROLL)
	{
		clientArea.bottom += ::GetSystemMetrics(SM_CXVSCROLL);
	}

	// ======================================================================
	// Ŭ���̾�Ʈ ���� �������� ������ ������ �������մϴ�.
	::AdjustWindowRectEx(&clientArea, dwStyle, bMenu, dwStyleEx);

	// �̹� �����찡 ������ �����̹Ƿ� �������� ũ�⸦ �����մϴ�.
	::SetWindowPos(hWnd, nullptr, 0, 0, clientArea.right - clientArea.left,
		clientArea.bottom - clientArea.top, SWP_NOMOVE | SWP_NOZORDER);
}

// �÷�Ű �κ��� ���ܽ�Ű�� ��Ʈ���� �׸��ϴ�.
void RXGlobal::DrawBimapExcludeColorKey(HDC hDC, HBITMAP hBitmap,
	INT32 x, INT32 y, COLORREF colorKey, bool bCenter)
{
	// ======================================================================
	// �޸� DC�� �����ؼ� �׸� ��Ʈ�ʰ� ��������ݴϴ�.
	HDC hMemDC = ::CreateCompatibleDC(hDC);
	HBITMAP hOldBitmap = SelectBitmap(hMemDC, hBitmap);

	// ======================================================================
	// ��Ʈ�� ������ �̿��ؼ� ��Ʈ���� �׸� ��ġ�� �����մϴ�.
	BITMAP bitmapInfo;
	::GetObject(hBitmap, sizeof(bitmapInfo), &bitmapInfo);

	// bCenter�� ���� ��Ʈ���� �׸� ��ġ�� �����մϴ�.
	POINT drawPos;
	if (bCenter == true)
	{
		drawPos.x = (x / 2) - (bitmapInfo.bmWidth / 2);
		drawPos.y = (y / 2) - (bitmapInfo.bmHeight / 2);
	}
	else
	{
		drawPos.x = x;
		drawPos.y = y;
	}

	// ======================================================================
	// GdiTransparentBlt()�� TransparentBlt()�� ���������� ������ ���̺귯�� ������ �ʿ� �����ϴ�.
	::GdiTransparentBlt(hDC, drawPos.x, drawPos.y, bitmapInfo.bmWidth, bitmapInfo.bmHeight,
		hMemDC, 0, 0, bitmapInfo.bmWidth, bitmapInfo.bmHeight, colorKey);

	// ======================================================================
	// �޸� DC�� ���� ��Ʈ���� �����ϰ�, �޸� DC�� �����մϴ�.
	// ���� �ǹ̴� ������ ���� ������ �����ؾ� �Ѵٴ� ��Ģ�� �����ϴ�.
	SelectBitmap(hMemDC, hOldBitmap);
	::DeleteDC(hMemDC);
}

// ����� ����� ���α׷��� ��ġ�� ��ġ�� ���մϴ�.
POINT RXGlobal::CalcCenterPosByScreen(INT32 width, INT32 height)
{
	POINT centerPos;
	centerPos.x = (::GetSystemMetrics(SM_CXSCREEN) / 2) - (width / 2);
	centerPos.y = (::GetSystemMetrics(SM_CYSCREEN) / 2) - (height / 2);
	return centerPos;
}

// WndCreateInfo�� ResolutionInfo ������ �߾� ��ġ�� ���մϴ�.
// ���� ��ġ�� POINT�ε� ��ȯ������ WndCreateInfo�� PositionInfo���� �����մϴ�.
// ǥ�� ���̺귯������ �̷� ������ �Լ����� �ֽ��ϴ�.
POINT RXGlobal::CalcCenterPosByScreen(WndCreateInfo* pWndCreateInfo)
{
	if (pWndCreateInfo == nullptr)
	{
		return POINT();
	}

	POINT centerPos = CalcCenterPosByScreen(pWndCreateInfo->resolutionInfo.width,
		pWndCreateInfo->resolutionInfo.height);
	pWndCreateInfo->posInfo.x = centerPos.x;
	pWndCreateInfo->posInfo.y = centerPos.y;
	return centerPos;
}

// Create�� ���� ������ �̿��ؼ� ó������ ���� �� ����ϰ�
// Make�� ���޵� �������� �����ؼ� ���� �� ����մϴ�. (��� ���� ���̴� ����...)
// printf()ó�� ����ϸ� std::wstring �ڷ������� ���ڿ��� ����ϴ�.
std::wstring RXGlobal::MakeFormatString(const WCHAR* szFormat, ...)
{
	// ======================================================================
	// ���� ���� ��ũ�θ� �̿��ؼ� �� ���ڵ��� �����մϴ�.
	va_list va = nullptr;
	va_start(va, szFormat); // ���� ������ ������ �˸��ϴ�.

	// ���� ���ڿ��� ���̸� ���մϴ�.
	// �����Ҵ��� ���� ���� ���ڸ� �����ؾ� �մϴ�.
	INT32 strLength = _vscwprintf(szFormat, va) + 1;

	// ���� ���ڷ� ���ڿ��� �����Ϸ��� �޸� ���۰� �ʿ��մϴ�.
	// std::string�� �޸� ���۰� �������̶� ����� �� �����ϴ�.
	// ����� �ܼ��ϰ� ����Ʈ ������ �����Ҵ��� ���� std::malloc()�� ����մϴ�.
	WCHAR* szBuffer = nullptr;
	szBuffer = reinterpret_cast<WCHAR*>(std::malloc(strLength * sizeof(WCHAR)));
	::ZeroMemory(szBuffer, (strLength * sizeof(WCHAR)));

	// �����Ҵ�� �޸� ���ۿ� ���� ���ڿ��� ���� ���ڵ��� �����ؼ� �ϳ��� ���ڿ��� ����ϴ�.
	vswprintf_s(szBuffer, strLength, szFormat, va);
	va_end(va); // ���� ������ ���Ḧ �˸��ϴ�.

	// ======================================================================
	// �����Ҵ�� �޸� ���۸� �����ϰ� �ϼ��� ���ڿ��� std::wstring�� �����մϴ�.
	std::wstring szResult = szBuffer;
	free(szBuffer);

	return szResult;
}