// =====================================================================================
// Copyright(c) 2019, Ruvendix. All Rights Reserved.
// 
// 이 저작물은 크리에이티브 커먼즈 저작자표시 4.0 국제 라이선스에 따라 이용할 수 있습니다.
// http://creativecommons.org/licenses/by/4.0/
// =====================================================================================
#include "NewWnd.h"

// WM_LBUTTONDOWN 핸들러입니다.
void RXNewWnd::OnLButtonDown(HWND hWnd, BOOL bDoubleClick, INT32 x, INT32 y, UINT keyFlags)
{
	MSGBOX(_T("(RXNewWnd) 마우스 왼쪽 버튼 클릭!"));
}