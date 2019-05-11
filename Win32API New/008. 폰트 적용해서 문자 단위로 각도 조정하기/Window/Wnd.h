// =====================================================================================
// Copyright(c) 2019, Ruvendix. All Rights Reserved.
// 
// �� ���۹��� ũ������Ƽ�� Ŀ���� ������ǥ�� 4.0 ���� ���̼����� ���� �̿��� �� �ֽ��ϴ�.
// http://creativecommons.org/licenses/by/4.0/
// =====================================================================================

// �ߺ� ���� �������Դϴ�.
// #pragma once�� ������ #define Guarder�� ����մϴ�.
#ifndef WND_H_
#define WND_H_

// ���� ����� ����մϴ�.
#include "Common"

/*
	������ ���� �� �������Դϴ�.
*/
class RXWnd
{
public:
	RXWnd();
	RXWnd(const std::wstring& szWndTtile);
	virtual ~RXWnd() = default;

	// ======================================================================
	// �޽��� �ڵ鷯�Դϴ�.
	virtual BOOL OnCreate(HWND hWnd, CREATESTRUCT* pCreateStruct);
	virtual void OnClose(HWND hWnd);
	virtual void OnMouseMove(HWND hWnd, INT32 x, INT32 y, UINT keyFlags);
	virtual void OnLButtonDown(HWND hWnd, BOOL bDoubleClick, INT32 x, INT32 y, UINT keyFlags);
	virtual void OnLButtonUp(HWND hWnd, INT32 x, INT32 y, UINT keyFlags);
	virtual void OnPaint(HWND hWnd);
	virtual void OnKeyDown(HWND hWnd, UINT vKey, BOOL bDown, INT32 repeat, UINT flags);
	virtual void OnDestroy(HWND hWnd);

	// ======================================================================
	// ������ �����Դϴ�.
	HRESULT Create(INT32 x, INT32 y, INT32 clientWidth, INT32 clientHeight, DWORD dwStyle); // �⺻���Դϴ�.
	HRESULT Create(const WndCreateInfo& wndCreateInfo);

	// ======================================================================
	// Getter
	const std::wstring getWndTitle() const noexcept
	{
		return m_szWndTitle;
	}

	INT32 getClientWidth() const noexcept
	{
		return (m_clientArea.right - m_clientArea.left);
	}

	INT32 getClientHeight() const noexcept
	{
		return (m_clientArea.bottom - m_clientArea.top);
	}

	// ======================================================================
	// Setter
	void setTitle(const std::wstring& szTitle)
	{
		m_szWndTitle = szTitle;
	}

	void setTitleBarTitle(const std::wstring& szTitle)
	{
		m_szWndTitle = szTitle;
		::SetWindowText(m_hWnd, szTitle.c_str());
	}

	void setClientArea(RECT clientArea)
	{
		m_clientArea = clientArea;
	}

protected:
	std::wstring m_szWndTitle; // ������ �̸��Դϴ�.
	HWND         m_hWnd;       // ������ �ڵ��Դϴ�.
	RECT         m_clientArea; // Ŭ���̾�Ʈ �����Դϴ�.
};

#endif