// =====================================================================================
// Copyright(c) 2019, Ruvendix. All Rights Reserved.
// 
// �� ���۹��� ũ������Ƽ�� Ŀ���� ������ǥ�� 4.0 ���� ���̼����� ���� �̿��� �� �ֽ��ϴ�.
// http://creativecommons.org/licenses/by/4.0/
// =====================================================================================
#include "SplashWnd.h"

namespace
{
	const INT32 RANDOM_SPLASH_COUNT = 6;
	const INT32 SPLASH_TIMER_ID = 1;
}

// WM_CREATE �ڵ鷯�Դϴ�.
BOOL RXSplashWnd::OnCreate(HWND hWnd, CREATESTRUCT* pCreateStruct)
{
	if (pCreateStruct == nullptr)
	{
		return FALSE;
	}

	// ======================================================================
	// ���÷��� ������� ����� ��Ʈ���� �����ϰ� ���ϴ�.
	// RANDOM_SPLASH_COUNT�� ���� ��Ʈ�� ���� ������ ��ġ�ؾ� ���� �۵��˴ϴ�.
	// ��Ʈ���� ���� ��Ʈ�� �޸𸮿� �ε��ؼ� ��Ʈ�� �ڵ鰪�� ����ϴ�.
	std::srand(::timeGetTime());
	std::wstring szFilePath =
		RXGlobal::MakeFormatString(_T("resource\\splash_%d.bmp"), std::rand() % RANDOM_SPLASH_COUNT);
	m_hBitmap = static_cast<HBITMAP>(::LoadImage(RXGlobal::m_hMainInstance,
		szFilePath.c_str(), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION));

	if (m_hBitmap == nullptr)
	{
		ERRMSGBOX(_T("��Ʈ�� �ε� ����!"));
		return FALSE;
	}

	// ======================================================================
	// ���÷��� �����츦 �����մϴ�.
	// ������ ��Ÿ���� WS_EXLAYERED�� �����ؾ� �ϴµ�
	// ������ �������� �ݵ�� SetLayeredWindowAttributes() �Ǵ� UpdateLayeredWindow()��
	// �ٷ� ȣ���ؾ� ���� �۵��� ����˴ϴ�!
	//
	// �߰������� ���÷��� ��ũ���� ������ ������ �ϹǷ� WS_EX_TOPMOST�� �����ϰ�,
	// �۾� ǥ���ٰ� ��Ʈ�� ��Ͽ��� ����� �ϹǷ� WS_EX_TOOLWINDOW�� �����մϴ�.
	::SetWindowLongPtr(hWnd, GWL_EXSTYLE, ::GetWindowLongPtr(hWnd, GWL_EXSTYLE) |
		WS_EX_LAYERED | WS_EX_TOPMOST | WS_EX_TOOLWINDOW);

	// �÷�Ű�� �����ϰ� �׸����� LWA_COLORKEY �÷��׸� �����մϴ�.
	::SetLayeredWindowAttributes(hWnd, RXGlobal::WINDOW_COLOR_WHITE, 0, LWA_COLORKEY);

	// ======================================================================
	// ������ ��ġ�� ȭ�� ����� �����մϴ�.
	POINT centerPos = RXGlobal::CalcCenterPosByScreen(pCreateStruct->cx, pCreateStruct->cy);
	::SetWindowPos(hWnd, HWND_TOPMOST, centerPos.x, centerPos.y, 0, 0, SWP_NOSIZE);

	// ======================================================================
	// ���÷��� �����찡 ������ �ð��� �����մϴ�.
	// Ÿ�̸Ӹ� �̿��ϸ� �����ϰ� ó���� �� �ֽ��ϴ�.
	::SetTimer(hWnd, SPLASH_TIMER_ID, 3000, nullptr);
	// ======================================================================

	return TRUE;
}

// WM_PAINT �ڵ鷯�Դϴ�.
void RXSplashWnd::OnPaint(HWND hWnd)
{
	// �ݵ�� DC�� BeginPaint()�� �����ؾ� �մϴ�.
	// �׷��� ������ WM_PAINT�� �������� �ʽ��ϴ�.
	PAINTSTRUCT ps;
	HDC hDC = BeginPaint(hWnd, &ps);

	// ======================================================================
	// ���÷��� �����쿡 ����� ��Ʈ���� �׸��ϴ�.
	RXGlobal::DrawBimapExcludeColorKey(hDC, m_hBitmap,
		getClientWidth(), getClientHeight(), RXGlobal::WINDOW_COLOR_WHITE, true);
	// ======================================================================

	// BeginPaint()�� ���������� EndPaint()�� ������ �մϴ�.
	EndPaint(hWnd, &ps);
}

// WM_DESTROY �ڵ鷯�Դϴ�.
void RXSplashWnd::OnDestroy(HWND hWnd)
{
	::KillTimer(hWnd, SPLASH_TIMER_ID);
	DeleteBitmap(m_hBitmap);
	RXWnd::OnDestroy(hWnd);
}

// WM_TIMER �ڵ鷯�Դϴ�.
void RXSplashWnd::OnTimer(HWND hWnd, UINT id)
{
	// Ÿ�̸Ӱ� �̺�Ʈ�� ������ ���� �����츦 Ȱ��ȭ��ŵ�ϴ�.
	if (id == SPLASH_TIMER_ID)
	{
		::SendMessage(hWnd, WM_CLOSE, 0, 0); // �����ϰ� �����ϴ� ����Դϴ�.
	}
}