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
const TCHAR* RXGlobal::SZ_WND_PROCEDURE_PROPERTY = _T("WndProcedure");

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