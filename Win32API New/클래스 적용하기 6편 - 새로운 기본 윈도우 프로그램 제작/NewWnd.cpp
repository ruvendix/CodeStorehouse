// =====================================================================================
// Copyright(c) 2019, Ruvendix. All Rights Reserved.
// 
// �� ���۹��� ũ������Ƽ�� Ŀ���� ������ǥ�� 4.0 ���� ���̼����� ���� �̿��� �� �ֽ��ϴ�.
// http://creativecommons.org/licenses/by/4.0/
// =====================================================================================
#include "NewWnd.h"

// WM_LBUTTONDOWN �ڵ鷯�Դϴ�.
void RXNewWnd::OnLButtonDown(HWND hWnd, BOOL bDoubleClick, INT32 x, INT32 y, UINT keyFlags)
{
	MSGBOX(_T("(RXNewWnd) ���콺 ���� ��ư Ŭ��!"));
}