#include "MouseDragWnd.h"

// WM_LBUTTONDOWN 핸들러입니다.
void RXMouseDragWnd::OnLButtonDown(HWND hWnd, BOOL bDoubleClick, INT32 x, INT32 y, UINT keyFlags)
{
	m_bDrag = true;
	m_dragArea.left = x;
	m_dragArea.top  = y;
}

// WM_LBUTTONUP 핸들러입니다.
void RXMouseDragWnd::OnLButtonUp(HWND hWnd, INT32 x, INT32 y, UINT keyFlags)
{
	m_bDrag = false;
	::SetRect(&m_dragArea, 0, 0, 0, 0);
	::InvalidateRect(hWnd, nullptr, TRUE);
}

// WM_MOUSEMOVE 핸들러입니다.
void RXMouseDragWnd::OnMouseMove(HWND hWnd, INT32 x, INT32 y, UINT keyFlags)
{
	if (m_bDrag == true)
	{
		m_dragArea.right  = x;
		m_dragArea.bottom = y;
		::InvalidateRect(hWnd, nullptr, TRUE);
	}
}

// WM_PAINT 핸들러입니다.
void RXMouseDragWnd::OnPaint(HWND hWnd)
{
	// 반드시 DC를 BeginPaint()로 생성해야 합니다.
	// 그렇지 않으면 WM_PAINT는 삭제되지 않습니다.
	PAINTSTRUCT ps;
	HDC hDC = BeginPaint(hWnd, &ps);

	// ======================================================================
	// 논리 펜을 생성해서 DC에 적용합니다.
	LOGPEN logPen;
	logPen.lopnColor   = RGB(255, 255, 0);
	logPen.lopnStyle   = PS_SOLID;
	logPen.lopnWidth.x = 1;

	HPEN   hPen      = ::CreatePenIndirect(&logPen);
	HPEN   hOldPen   = SelectPen(hDC, hPen);
	HBRUSH hOldBrush = SelectBrush(hDC, GetStockBrush(NULL_BRUSH));

	// ======================================================================
	// 드래그 영역을 사각형으로 그립니다.
	::Rectangle(hDC, m_dragArea.left, m_dragArea.top, m_dragArea.right, m_dragArea.bottom);

	// ======================================================================
	// 이전 펜으로 복구하고 생성한 펜을 제거합니다.
	SelectBrush(hDC, hOldBrush);
	SelectPen(hDC, hOldPen);
	DeletePen(hPen);

	// BeginPaint()로 시작했으면 EndPaint()로 끝내야 합니다.
	EndPaint(hWnd, &ps);
}