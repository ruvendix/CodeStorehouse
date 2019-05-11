// =====================================================================================
// Copyright(c) 2019, Ruvendix. All Rights Reserved.
// 
// �� ���۹��� ũ������Ƽ�� Ŀ���� ������ǥ�� 4.0 ���� ���̼����� ���� �̿��� �� �ֽ��ϴ�.
// http://creativecommons.org/licenses/by/4.0/
// =====================================================================================
#include "Wnd.h"

RXWnd::RXWnd(const std::wstring& szWndTitle)
{
	m_szWndTitle = szWndTitle;
	m_hWnd = nullptr;
}

// WM_CREATE �ڵ鷯�Դϴ�.
BOOL RXWnd::OnCreate(HWND hWnd, CREATESTRUCT* pCreateStruct)
{
	m_hWnd = hWnd;
	return TRUE; // �޽��� ũ��Ŀ�� ���� �ݵ�� TRUE�� ��ȯ�ؾ� �մϴ�.
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
		nullptr, nullptr, RXGlobal::m_hMainInstance, this);

	::ShowWindow(m_hWnd, SW_SHOWNORMAL);
	::UpdateWindow(m_hWnd);
	// ======================================================================

	return S_OK;
}