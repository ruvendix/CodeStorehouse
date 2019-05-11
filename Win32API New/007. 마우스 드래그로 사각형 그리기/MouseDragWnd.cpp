#include "MouseDragWnd.h"

void RXMouseDragWnd::OnLButtonDown(HWND hWnd, BOOL bDoubleClick, INT32 x, INT32 y, UINT keyFlags)
{
	m_bDrag = true;
	m_dragArea.left = x;
	m_dragArea.top  = y;
}

void RXMouseDragWnd::OnLButtonUp(HWND hWnd, INT32 x, INT32 y, UINT keyFlags)
{
	m_bDrag = false;
	::SetRect(&m_dragArea, 0, 0, 0, 0);
	::InvalidateRect(hWnd, nullptr, TRUE);
}

void RXMouseDragWnd::OnMouseMove(HWND hWnd, INT32 x, INT32 y, UINT keyFlags)
{
	if (m_bDrag == true)
	{
		m_dragArea.right  = x;
		m_dragArea.bottom = y;
		::InvalidateRect(hWnd, nullptr, TRUE);
	}
}

void RXMouseDragWnd::OnPaint(HWND hWnd)
{
	PAINTSTRUCT ps;
	HDC hDC = BeginPaint(hWnd, &ps);

	LOGPEN logPen;
	logPen.lopnColor   = RGB(255, 255, 0);
	logPen.lopnStyle   = PS_SOLID;
	logPen.lopnWidth.x = 1;

	HPEN   hPen      = ::CreatePenIndirect(&logPen);
	HPEN   hOldPen   = SelectPen(hDC, hPen);
	HBRUSH hOldBrush = SelectBrush(hDC, GetStockBrush(NULL_BRUSH));

	::Rectangle(hDC, m_dragArea.left, m_dragArea.top, m_dragArea.right, m_dragArea.bottom);

	SelectBrush(hDC, hOldBrush);
	SelectPen(hDC, hOldPen);
	DeletePen(hPen);

	EndPaint(hWnd, &ps);
}