// =====================================================================================
// Copyright(c) 2019, Ruvendix. All Rights Reserved.
// 
// �� ���۹��� ũ������Ƽ�� Ŀ���� ������ǥ�� 4.0 ���� ���̼����� ���� �̿��� �� �ֽ��ϴ�.
// http://creativecommons.org/licenses/by/4.0/
// =====================================================================================

/*
	������ WIN32_LEAN_AND_MEAN�� ���������,
	���� ��ǻ�� ��翡���� �ǹ̰� �����Ƿ� �����մϴ�.
*/

// RXWndApp�� ����մϴ�.
#include "MyApp.h"

// RXMouseDragWnd�� ����մϴ�.
#include "MouseDragWnd.h"

// ������ ���α׷��� �������Դϴ�.
INT32 APIENTRY _tWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPTSTR szCommandLine, INT32 showStyle)
{
	// ======================================================================
	// ������� �ʴ� �Ű������Դϴ�.
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(szCommandLine);

	// ��������ó�� ����� Ŭ������ ������ ����մϴ�.
	RXGlobal::m_hMainInstance = hInstance;

	// ���α׷��� ���� ��ƾ�� ����� ��ü�� �����մϴ�.
	RXMyApp myApp(_T("Sample"), 100, 100, 1024, 768);
	
	// ���α׷��� ���� �����츦 �����մϴ�.
	myApp.setMainWnd(RXNew RXMouseDragWnd);

	// ���α׷��� ���� ��ƾ�� �۵���ŵ�ϴ�.
	return (myApp.Run());
}