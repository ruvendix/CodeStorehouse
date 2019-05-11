// =====================================================================================
// Copyright(c) 2019, Ruvendix. All Rights Reserved.
// 
// �� ���۹��� ũ������Ƽ�� Ŀ���� ������ǥ�� 4.0 ���� ���̼����� ���� �̿��� �� �ֽ��ϴ�.
// http://creativecommons.org/licenses/by/4.0/
// =====================================================================================
#include "Wnd.h"

RXWnd::RXWnd()
{
	m_szWndTitle = _T("RXWnd");
	m_hWnd = nullptr;
	
	::SetRect(&m_clientArea, 0, 0, 0, 0);
}

RXWnd::RXWnd(const std::wstring& szWndTitle)
{
	m_szWndTitle = szWndTitle;
	m_hWnd = nullptr;

	::SetRect(&m_clientArea, 0, 0, 1024, 768);
}

// WM_CREATE �ڵ鷯�Դϴ�.
BOOL RXWnd::OnCreate(HWND hWnd, CREATESTRUCT* pCreateStruct)
{
	m_hWnd = hWnd;
	return TRUE; // �޽��� ũ��Ŀ�� ���� �ݵ�� TRUE�� ��ȯ�ؾ� �մϴ�.
}

// WM_DESTROY �ڵ鷯�Դϴ�.
void RXWnd::OnLButtonDown(HWND hWnd, BOOL bDoubleClick, INT32 x, INT32 y, UINT keyFlags)
{
	MSGBOX(_T("(RXWnd) ���콺 ���� ��ư Ŭ��!"));
}

// WM_DESTROY �ڵ鷯�Դϴ�.
void RXWnd::OnDestroy(HWND hWnd)
{
	// WM_DESTROY�� ������ WM_QUIT�� �����ϴ�.
	::PostQuitMessage(EXIT_SUCCESS);
}

// ������ ���� �⺻���Դϴ�.
HRESULT RXWnd::Create(INT32 x, INT32 y, INT32 clientWidth, INT32 clientHeight, DWORD dwStyle)
{
	// ======================================================================
	// �����츦 �����ϰ� ����ڿ��� �����ݴϴ�.
	m_hWnd = ::CreateWindow(m_szWndTitle.c_str(), m_szWndTitle.c_str(),
		dwStyle, x, y, clientWidth, clientHeight,
		HWND_DESKTOP, nullptr, RXGlobal::m_hMainInstance, this);

	if (m_hWnd == nullptr)
	{
		ERRMSGBOX(L"������ ���� ����!");
		return E_FAIL;
	}

	// Ŭ���̾�Ʈ ���� �������� ������ ������ �������մϴ�.
	RXGlobal::AdjustClientArea(m_hWnd, clientWidth, clientHeight);
	
	// ������ �ڵ鰪�� ������Ƿ� Ŭ���̾�Ʈ ���� ������ �����մϴ�.
	::GetClientRect(m_hWnd, &m_clientArea);

	::ShowWindow(m_hWnd, SW_SHOWNORMAL);
	::UpdateWindow(m_hWnd);
	// ======================================================================

	return S_OK;
}

// ������ ���� ������ ���ڷ� �ް�,
// ������ ��Ÿ���� WS_OVERLAPPEDWINDOW�� �����մϴ�.
HRESULT RXWnd::Create(const WndCreateInfo& wndCreateInfo)
{
	return Create(wndCreateInfo.posInfo.x, wndCreateInfo.posInfo.y,
		wndCreateInfo.resolutionInfo.width, wndCreateInfo.resolutionInfo.height, WS_OVERLAPPEDWINDOW);
}