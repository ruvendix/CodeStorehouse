#include "RXWindow.h"

namespace RX
{

	RXWindow::RXWindow()
	{
		m_szWndTitle = L"RXWindow";
		m_hWnd       = nullptr;

		m_vecChildWnd.reserve(2);
	}

	RXWindow::RXWindow(const std::wstring& szWndTitle)
	{
		m_szWndTitle = szWndTitle;
		m_hWnd       = nullptr;

		m_vecChildWnd.reserve(2);
	}

	void RXWindow::OnLButtonDown(HWND hWnd, BOOL bDoubleClick,
		INT32 x, INT32 y, UINT keyFlags)
	{
		//::MessageBox(hWnd, L"(RXWindow) 마우스 왼쪽 버튼 클릭!", L"캡션", MB_OK);
		//::MessageBeep(UINT_MAX);

		//m_bDrag = true;
		//m_rtDrag.left = x;
		//m_rtDrag.top  = y;

		//m_startPos.x = x;
		//m_startPos.y = y;
		//m_endPos = m_startPos;
	}

	void RXWindow::OnLButtonUp(HWND hWnd, INT32 x, INT32 y, UINT keyFlags)
	{
		//m_bDrag = false;
		//::SetRect(&m_rtDrag, 0, 0, 0, 0);
		//::InvalidateRect(hWnd, nullptr, TRUE);
	}

	void RXWindow::OnRButtonDown(HWND hWnd, BOOL bDoubleClick, INT32 x, INT32 y, UINT keyFlags)
	{
	}

	void RXWindow::OnMouseMove(HWND hWnd, INT32 x, INT32 y, UINT keyFlags)
	{
		//if (m_bDrag == true)
		//{
		//	m_rtDrag.right  = x;
		//	m_rtDrag.bottom = y;

		//	HDC hDC = ::GetDC(hWnd);

		//	// ROP는 이미 그려진 픽셀 기준으로 비트 연산을 하게 됨!
		//	// 즉, 바탕이 0이면 그릴 때 무조건 1이 됨!

		//	// 그리기 도중인 것, 아직 확정되지 않은 것을 반전으로 그린다면?
		//	// 이전에 그린 선은 반전시키고, 새로 그리는 건 유지
		//	// 이전에 드래그된 선을 지운다 => 반전시킨다.
		//	::SetROP2(hDC, R2_NOT); // 1은 0으로, 0은 1로
		//	::MoveToEx(hDC, m_startPos.x, m_startPos.y, nullptr);
		//	::LineTo(hDC, m_endPos.x, m_endPos.y);
		//	
		//	// 드래그되는 중의 선은 어차피 바탕이 0이므로 반전시켜서 1이 된다.
		//	m_endPos.x = x;
		//	m_endPos.y = y;
		//	::MoveToEx(hDC, m_startPos.x, m_startPos.y, nullptr);
		//	::LineTo(hDC, m_endPos.x, m_endPos.y);

		//	::ReleaseDC(hWnd, hDC);

		//	//::InvalidateRect(hWnd, nullptr, TRUE);
		//}
	}

	void RXWindow::OnPaint(HWND hWnd)
	{
		PAINTSTRUCT ps;
		HDC hDC = BeginPaint(hWnd, &ps);
		//::SetTextAlign(hDC, TA_UPDATECP); // Current Position
		//::TextOut(hDC, 200, 60, TEXT("One "), 4);
		//::TextOut(hDC, 200, 80, TEXT("Two "), 4);
		//::TextOut(hDC, 200, 100, TEXT("Three"), 5);

		//LOGPEN logPen;
		//logPen.lopnColor = RGB(255, 255, 0);
		//logPen.lopnStyle = PS_SOLID;
		//logPen.lopnWidth.x = 1;

		//HPEN hPen = ::CreatePenIndirect(&logPen);
		//HPEN hOldPen = SelectPen(hDC, hPen);
		//HBRUSH hOldBrush = SelectBrush(hDC, GetStockBrush(NULL_BRUSH));

		//::Rectangle(hDC, m_rtDrag.left, m_rtDrag.top, m_rtDrag.right, m_rtDrag.bottom);

		//SelectBrush(hDC, hOldBrush);
		//SelectPen(hDC, hOldPen);
		//DeletePen(hPen);

		EndPaint(hWnd, &ps);
	}

	void RXWindow::OnKeyDown(HWND hWnd, UINT vKey, BOOL bDown, INT32 repeat, UINT flags)
	{
		switch (vKey)
		{
		case VK_ESCAPE:
		{
			::DestroyWindow(hWnd);
		}
		}
	}

	void RXWindow::OnSysKeyDown(HWND hWnd, UINT vk, BOOL bDown, INT32 repeat, UINT flags)
	{
		if (vk == VK_MENU) // ALT 키
		{

		}
	}

	void RXWindow::OnCommand(HWND hWnd, INT32 id, HWND hControlWnd, UINT codeNotify)
	{

	}

	BOOL RXWindow::OnCreate(HWND hWnd, CREATESTRUCT* pCreateStruct)
	{
		m_hWnd = hWnd;
		return TRUE; // 메시지 크래커로 인해 TRUE를 반환해야 윈도우 생성 작업을 이어감!
	}

	void RXWindow::OnClose(HWND hWnd)
	{
		::DestroyWindow(hWnd);
	}

	void RXWindow::OnDestroy(HWND hWnd)
	{
		::RemoveProp(hWnd, _T("WindowProcedure"));
		::PostQuitMessage(EXIT_SUCCESS);
	}

	HRESULT RXWindow::CreateRXWindow(INT32 x, INT32 y, INT32 clientWidth, INT32 clientHeight)
	{
		::CreateWindow(m_szWndTitle.c_str(), m_szWndTitle.c_str(),
			WS_GAME_DEFAULT, x, y, clientWidth, clientHeight,
			HWND_DESKTOP, nullptr, RXGlobal::g_hMainInstance, this);

		if (m_hWnd == nullptr)
		{
			ERRMSGBOX(L"윈도우 생성 실패!");
			return E_FAIL;
		}

		RECT rtWindow = { 0, 0, clientWidth, clientHeight };
		::AdjustWindowRect(&rtWindow, WS_GAME_DEFAULT, FALSE);

		::SetWindowPos(m_hWnd, HWND_TOP, 0, 0, rtWindow.right - rtWindow.left,
			rtWindow.bottom - rtWindow.top, SWP_NOMOVE | SWP_NOZORDER);

		::GetClientRect(m_hWnd, &m_rtClient);
		::UpdateWindow(m_hWnd);

		return S_OK;
	}

	std::pair<INT32, INT32> RXWindow::getClientWidthAndHeight() const noexcept
	{
		std::pair<INT32, INT32> clientAreaInfo;
		clientAreaInfo.first  = m_rtClient.right - m_rtClient.left;
		clientAreaInfo.second = m_rtClient.bottom - m_rtClient.top;
		return clientAreaInfo;
	}

} // namespace RX end