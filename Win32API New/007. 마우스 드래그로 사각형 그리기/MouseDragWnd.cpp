#include "MouseDragWnd.h"

// WM_LBUTTONDOWN �ڵ鷯�Դϴ�.
void RXMouseDragWnd::OnLButtonDown(HWND hWnd, BOOL bDoubleClick, INT32 x, INT32 y, UINT keyFlags)
{
	m_bDrag = true;
	m_dragArea.left = x;
	m_dragArea.top  = y;
}

// WM_LBUTTONUP �ڵ鷯�Դϴ�.
void RXMouseDragWnd::OnLButtonUp(HWND hWnd, INT32 x, INT32 y, UINT keyFlags)
{
	m_bDrag = false;
	::SetRect(&m_dragArea, 0, 0, 0, 0);
	::InvalidateRect(hWnd, nullptr, TRUE);
}

// WM_MOUSEMOVE �ڵ鷯�Դϴ�.
void RXMouseDragWnd::OnMouseMove(HWND hWnd, INT32 x, INT32 y, UINT keyFlags)
{
	if (m_bDrag == true)
	{
		m_dragArea.right  = x;
		m_dragArea.bottom = y;
		::InvalidateRect(hWnd, nullptr, TRUE);
	}
}

// WM_PAINT �ڵ鷯�Դϴ�.
void RXMouseDragWnd::OnPaint(HWND hWnd)
{
	// �ݵ�� DC�� BeginPaint()�� �����ؾ� �մϴ�.
	// �׷��� ������ WM_PAINT�� �������� �ʽ��ϴ�.
	PAINTSTRUCT ps;
	HDC hDC = BeginPaint(hWnd, &ps);

	// ======================================================================
	// �� ���� �����ؼ� DC�� �����մϴ�.
	LOGPEN logPen;
	logPen.lopnColor   = RGB(255, 255, 0);
	logPen.lopnStyle   = PS_SOLID;
	logPen.lopnWidth.x = 1;

	HPEN   hPen      = ::CreatePenIndirect(&logPen);
	HPEN   hOldPen   = SelectPen(hDC, hPen);
	HBRUSH hOldBrush = SelectBrush(hDC, GetStockBrush(NULL_BRUSH));

	// ======================================================================
	// �巡�� ������ �簢������ �׸��ϴ�.
	::Rectangle(hDC, m_dragArea.left, m_dragArea.top, m_dragArea.right, m_dragArea.bottom);

	// ======================================================================
	// ���� ������ �����ϰ� ������ ���� �����մϴ�.
	SelectBrush(hDC, hOldBrush);
	SelectPen(hDC, hOldPen);
	DeletePen(hPen);

	// BeginPaint()�� ���������� EndPaint()�� ������ �մϴ�.
	EndPaint(hWnd, &ps);
}