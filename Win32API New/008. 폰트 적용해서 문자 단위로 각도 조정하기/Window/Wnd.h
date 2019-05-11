// =====================================================================================
// Copyright(c) 2019, Ruvendix. All Rights Reserved.
// 
// 이 저작물은 크리에이티브 커먼즈 저작자표시 4.0 국제 라이선스에 따라 이용할 수 있습니다.
// http://creativecommons.org/licenses/by/4.0/
// =====================================================================================

// 중복 포함 방지용입니다.
// #pragma once도 있지만 #define Guarder를 사용합니다.
#ifndef WND_H_
#define WND_H_

// 공용 기능을 사용합니다.
#include "Common"

/*
	윈도우 생성 및 관리용입니다.
*/
class RXWnd
{
public:
	RXWnd();
	RXWnd(const std::wstring& szWndTtile);
	virtual ~RXWnd() = default;

	// ======================================================================
	// 메시지 핸들러입니다.
	virtual BOOL OnCreate(HWND hWnd, CREATESTRUCT* pCreateStruct);
	virtual void OnClose(HWND hWnd);
	virtual void OnMouseMove(HWND hWnd, INT32 x, INT32 y, UINT keyFlags);
	virtual void OnLButtonDown(HWND hWnd, BOOL bDoubleClick, INT32 x, INT32 y, UINT keyFlags);
	virtual void OnLButtonUp(HWND hWnd, INT32 x, INT32 y, UINT keyFlags);
	virtual void OnPaint(HWND hWnd);
	virtual void OnKeyDown(HWND hWnd, UINT vKey, BOOL bDown, INT32 repeat, UINT flags);
	virtual void OnDestroy(HWND hWnd);

	// ======================================================================
	// 윈도우 생성입니다.
	HRESULT Create(INT32 x, INT32 y, INT32 clientWidth, INT32 clientHeight, DWORD dwStyle); // 기본형입니다.
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
	std::wstring m_szWndTitle; // 윈도우 이름입니다.
	HWND         m_hWnd;       // 윈도우 핸들입니다.
	RECT         m_clientArea; // 클라이언트 영역입니다.
};

#endif