#include <cstdio>
#include <cstdlib>
#include <tchar.h>

#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#endif

#include <windowsx.h>

#define PRINT_LOG(szLog) ::OutputDebugString(_T(szLog "\n"))

// GetAsyncKeyState()�� �׻� ��Ŀ���� ���������Ƿ�
// �����찡 ��Ŀ���� �Ҿ ������ �ԷµǴ� ������ ����
// ���ڴ� ��ҹ��� ������ ���� �����Ƿ� 'W' �̷��� �־�� ��
#define PRESS_KEY(key)  (::GetAsyncKeyState(key) & 0x8000)
#define STROKE_KEY(key) (::GetAsyncKeyState(key) & 0x0001)

enum class SHAPE_TYPE
{
	LINE,
	ELLIPSE,
	RECTANGLE,
	END,
};

struct MouseDragInfo
{
	bool  bDrag;
	POINT ptStart;
	POINT ptEnd;
};

struct FLOAT_RECT
{
	FLOAT rLeft;
	FLOAT rTop;
	FLOAT rRight;
	FLOAT rBottom;
};

const INT32 RESOLUTION_WIDTH  = 1024;
const INT32 RESOLUTION_HEIGHT = 768;

LPCTSTR g_szWindowClass  = _T("Ruvendix");
LPCTSTR g_szProgramTitle = _T("Ruvendix");

HWND g_hMainWnd = nullptr;
MouseDragInfo g_mouseDragInfo;

INT32 g_shapeType = static_cast<INT32>(SHAPE_TYPE::LINE);

HDC g_hDC = nullptr;

LARGE_INTEGER g_freq;
LARGE_INTEGER g_prevTick;

FLOAT g_rTimeScale = 1.0f;

bool g_bPause = false;

LRESULT CALLBACK WindowProcedure(HWND hMainWnd, UINT msg, WPARAM wParam, LPARAM lParam);
HRESULT InitInstance(HINSTANCE hInstance);
HRESULT CreateProgramWindow(HINSTANCE hInstance);

void Run();
void DrawRect(const HDC& hDC, const RECT& rt);
void DrawRect(const HDC& hDC, const FLOAT_RECT& rt);
FLOAT TimeScale();

INT32 APIENTRY _tWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
	                     LPTSTR szCmdLine, INT32 cmdShow)
{
	::QueryPerformanceFrequency(&g_freq);
	::QueryPerformanceCounter(&g_prevTick);

	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(szCmdLine);
	UNREFERENCED_PARAMETER(cmdShow);

	g_mouseDragInfo.bDrag = false;

	// ==============================================
	// ������ Ŭ���� ���
	if (FAILED(InitInstance(hInstance)))
	{
		return 0;
	}
	// ==============================================
	// ������ ����
	if (FAILED(CreateProgramWindow(hInstance)))
	{
		return 0;
	}
	// ==============================================
	// �޽��� ����
	MSG msg;
	::ZeroMemory(&msg, sizeof(msg));

	bool bDrive = true;
	while (bDrive != false)
	{
		if (::PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
		{
			if (msg.message == WM_QUIT)
			{
				bDrive = false;
			}
			
			::TranslateMessage(&msg);
			::DispatchMessage(&msg);
		}
		else
		{
			// ���� ������ �� �ڸ�
			// ������ �޽��� ó���� ���� �κ��� ����Ÿ���̶�� ��
			//static INT32 loopCnt = 0;
			//++loopCnt;
			//if (loopCnt == 100000)
			//{
			//	loopCnt = 0;
			//	Run();
			//}

			Run();
		}
	}
	// ==============================================

	// ������ �ڵ鿡 ���� DC�� ���۷��� ī��Ʈ�� �ٿ��� ��!
	::ReleaseDC(g_hMainWnd, g_hDC);

	return (msg.wParam);
}

LRESULT CALLBACK WindowProcedure(HWND hMainWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_CREATE:
	{
		PRINT_LOG("���α׷� ������ ����!");
		break;
	}
	case WM_CLOSE:
	{
		PRINT_LOG("���α׷� �ݱ� ��ư Ŭ��!");
		::DestroyWindow(hMainWnd);
		break;
	}
	case WM_DESTROY:
	{
		PRINT_LOG("���α׷� ����!");
		::PostQuitMessage(0);
		break;
	}
	case WM_KEYDOWN:
	{
		switch (wParam)
		{
		case VK_ESCAPE:
		{
			PRINT_LOG("ESC �Է�!");
			::DestroyWindow(hMainWnd);
			break;
		}
		}

		break;
	}
	case WM_PAINT:
	{
		PAINTSTRUCT paint;
		HDC hDC = ::BeginPaint(hMainWnd, &paint);

		INT32 startX = 768 / 2;

		// �Ӹ�
		::Ellipse(hDC, startX, 100, startX + 200, 300);
		::TextOut(hDC, startX + 75, 120, _T("�����"), _tcslen(_T("�����")));
		
		// ��
		::MoveToEx(hDC, startX + 100, 300, nullptr);
		::LineTo(hDC, startX + 100, 480);

		// ��
		::MoveToEx(hDC, startX - 50, 350, nullptr);
		::LineTo(hDC, startX + 250, 350);
		
		// ���� �ٸ�
		::MoveToEx(hDC, startX + 100, 480, nullptr);
		::LineTo(hDC, startX - 50, 650);

		// ������ �ٸ�
		::MoveToEx(hDC, startX + 100, 480, nullptr);
		::LineTo(hDC, startX + 250, 650);

		TCHAR szMouseDragStartPos[32];
		_stprintf_s(szMouseDragStartPos, _countof(szMouseDragStartPos), _T("�巡�� ���� ����(%d, %d)"),
			g_mouseDragInfo.ptStart.x, g_mouseDragInfo.ptStart.y);
		::TextOut(hDC, 0, 0, szMouseDragStartPos, _tcslen(szMouseDragStartPos));

		if (g_mouseDragInfo.bDrag == true)
		{
			SHAPE_TYPE shapeType = static_cast<SHAPE_TYPE>(g_shapeType);
			switch (shapeType)
			{
			case SHAPE_TYPE::LINE:
			{
				::MoveToEx(hDC, g_mouseDragInfo.ptStart.x, g_mouseDragInfo.ptStart.y, nullptr);
				::LineTo(hDC, g_mouseDragInfo.ptEnd.x, g_mouseDragInfo.ptEnd.y);
				break;
			}
			case SHAPE_TYPE::ELLIPSE:
			{
				::Ellipse(hDC, g_mouseDragInfo.ptStart.x, g_mouseDragInfo.ptStart.y,
					g_mouseDragInfo.ptEnd.x, g_mouseDragInfo.ptEnd.y);
				break;
			}
			case SHAPE_TYPE::RECTANGLE:
			{
				::Rectangle(hDC, g_mouseDragInfo.ptStart.x, g_mouseDragInfo.ptStart.y,
				g_mouseDragInfo.ptEnd.x, g_mouseDragInfo.ptEnd.y);
				break;
			}
			}
		}

		::EndPaint(hMainWnd, &paint);
		break;
	}
	case WM_LBUTTONDOWN:
	{
		if (g_mouseDragInfo.bDrag == false)
		{
			g_mouseDragInfo.bDrag = true;
			g_mouseDragInfo.ptStart.x = GET_X_LPARAM(lParam);
			g_mouseDragInfo.ptStart.y = GET_Y_LPARAM(lParam);
		}
		break;
	}
	case WM_MOUSEMOVE:
	{
		if (g_mouseDragInfo.bDrag == true)
		{
			g_mouseDragInfo.ptEnd.x = GET_X_LPARAM(lParam);
			g_mouseDragInfo.ptEnd.y = GET_Y_LPARAM(lParam);
			::InvalidateRect(hMainWnd, nullptr, true);
		}
		break;
	}
	case WM_LBUTTONUP:
	{
		if (g_mouseDragInfo.bDrag == true)
		{
			g_mouseDragInfo.bDrag = false;
		}
		break;
	}
	case WM_RBUTTONUP:
	{
		++g_shapeType;
		if (g_shapeType == static_cast<INT32>(SHAPE_TYPE::END))
		{
			g_shapeType = static_cast<INT32>(SHAPE_TYPE::LINE);
		}
		break;
	}
	case WM_SYSCOMMAND:
	{
		// ���� 4��Ʈ�� ���������� ����ϴ� ���̹Ƿ� ������ ��!
		if (SC_KEYMENU == (wParam & 0xFFF0))
		{
			PRINT_LOG("ALT + Enter");
		}
	}
	}

	return ::DefWindowProc(hMainWnd, msg, wParam, lParam);
}

HRESULT InitInstance(HINSTANCE hInstance)
{
	WNDCLASSEX wcex;
	::ZeroMemory(&wcex, sizeof(wcex));

	wcex.cbSize        = sizeof(wcex);
	wcex.style         = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc   = WindowProcedure;
	wcex.cbClsExtra    = 0;
	wcex.cbWndExtra    = 0;
	wcex.hInstance     = hInstance;
	wcex.hIcon         = LoadIcon(hInstance, IDI_APPLICATION);
	wcex.hCursor       = ::LoadCursor(hInstance, IDC_ARROW);
	wcex.hbrBackground = static_cast<HBRUSH>(::GetStockObject(LTGRAY_BRUSH));
	wcex.lpszMenuName  = nullptr;
	wcex.lpszClassName = g_szWindowClass;
	wcex.hIconSm       = wcex.hIcon;

	if (::RegisterClassEx(&wcex) == 0)
	{
		PRINT_LOG("������ Ŭ���� ��� ����!");
		return E_FAIL;
	}

	return S_OK;
}

HRESULT CreateProgramWindow(HINSTANCE hInstance)
{
	g_hMainWnd = ::CreateWindow(g_szWindowClass, g_szProgramTitle, WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,
		::GetDesktopWindow(), nullptr, hInstance, nullptr);

	if (g_hMainWnd == nullptr)
	{
		PRINT_LOG("���α׷� ������ ���� ����!");
		return E_FAIL;
	}

	g_hDC = ::GetDC(g_hMainWnd);

	RECT rtWindow = { 0, 0, RESOLUTION_WIDTH, RESOLUTION_HEIGHT };
	::AdjustWindowRect(&rtWindow, WS_OVERLAPPEDWINDOW, false);

	INT32 screenWidth  = ::GetSystemMetrics(SM_CXSCREEN);
	INT32 screenHeight = ::GetSystemMetrics(SM_CYSCREEN);

	INT32 clientWidth  = rtWindow.right - rtWindow.left;
	INT32 clientHeight = rtWindow.bottom - rtWindow.top;

	// SWP_NOMOVE   => x, y ����
	// SWP_NOZORDER => hWndInsertAfter ����
	::SetWindowPos(g_hMainWnd, HWND_TOPMOST, (screenWidth - clientWidth) / 2,
		(screenHeight - clientHeight) / 2, clientWidth, clientHeight, 0);

	::UpdateWindow(g_hMainWnd);
	::ShowWindow(g_hMainWnd, SW_NORMAL);

	return S_OK;
}

void Run()
{
	if (PRESS_KEY(VK_F1))
	{
		g_rTimeScale += 0.001f;
		if (g_rTimeScale > 4.0f)
		{
			g_rTimeScale = 4.0f;
		}
	}

	if (PRESS_KEY(VK_F2))
	{
		g_rTimeScale -= 0.001f;
		if (g_rTimeScale < 0.0f)
		{
			g_rTimeScale = 0.0f;
		}
	}

	if (STROKE_KEY('P'))
	{
		g_bPause = !g_bPause;
	}

	static FLOAT_RECT rtPlayer = { 100.0f, 100.0f, 200.0f, 200.0f };

	LARGE_INTEGER g_currentTick;
	::QueryPerformanceCounter(&g_currentTick);

	// ���� ƽī��Ʈ 10��, ���� ƽī��Ʈ 15���̸�
	// 15�� - 10�� = 5���� �ǰ� �̰� ���ļ��� ������
	// 5�� / 100�� = 1 / 20�� �Ǵµ� �ʴ��� �����̹Ƿ� 0.05�ʰ� ��!
	// 0.05�ʰ� 20�� ���̸� 1�ʰ� �ǹǷ� �ʴ� �ӵ� ����� ��������!
	FLOAT rDeltaSeconds = (g_currentTick.QuadPart - g_prevTick.QuadPart) /
		static_cast<FLOAT>(g_freq.QuadPart);

	g_prevTick = g_currentTick;

	FLOAT rMoveSpeed = 300 * rDeltaSeconds * TimeScale();

	RECT rtClient;
	::GetClientRect(g_hMainWnd, &rtClient);

	if (PRESS_KEY('W'))
	{
		rtPlayer.rTop    -= rMoveSpeed;
		rtPlayer.rBottom -= rMoveSpeed;

		if (rtPlayer.rTop < 0.0f)
		{
			rtPlayer.rTop    = 0.0f;
			rtPlayer.rBottom = 100.0f;
		}
	}

	if (PRESS_KEY('A'))
	{
		rtPlayer.rLeft  -= rMoveSpeed;
		rtPlayer.rRight -= rMoveSpeed;

		if (rtPlayer.rLeft < 0.0f)
		{
			rtPlayer.rLeft  = 0.0f;
			rtPlayer.rRight = 100.0f;
		}
	}

	if (PRESS_KEY('S'))
	{
		rtPlayer.rTop    += rMoveSpeed;
		rtPlayer.rBottom += rMoveSpeed;

		if (rtPlayer.rBottom > rtClient.bottom)
		{
			rtPlayer.rTop    = rtClient.bottom - 100.0f;
			rtPlayer.rBottom = rtClient.bottom;
		}
	}

	if (PRESS_KEY('D'))
	{
		rtPlayer.rLeft  += rMoveSpeed;
		rtPlayer.rRight += rMoveSpeed;

		if (rtPlayer.rRight > rtClient.right)
		{
			rtPlayer.rLeft  = rtClient.right - 100.0f;
			rtPlayer.rRight = rtClient.right;
		}
	}

	DrawRect(g_hDC, rtPlayer);

	TCHAR szPause[64];
	::ZeroMemory(szPause, _countof(szPause));
	if (g_bPause)
	{
		_stprintf_s(szPause, _countof(szPause), _T("���α׷� �Ͻ�����(TimeScale : 0.00)"));
		::TextOut(g_hDC, 0, 20, szPause, _tcslen(szPause));
	}
	else
	{
		_stprintf_s(szPause, _countof(szPause), _T("�Ͻ����� ���¾ƴ�(TimeScale : %.2f)"), g_rTimeScale);
		::TextOut(g_hDC, 0, 20, szPause, _tcslen(szPause));
	}
}

void DrawRect(const HDC& hDC, const RECT& rt)
{
	::Rectangle(hDC, rt.left, rt.top, rt.right, rt.bottom);
}

void DrawRect(const HDC& hDC, const FLOAT_RECT& rt)
{
	::Rectangle(hDC, rt.rLeft, rt.rTop, rt.rRight, rt.rBottom);
}

FLOAT TimeScale()
{
	if (g_bPause == true)
	{
		return 0;
	}
	else
	{
		return g_rTimeScale;
	}
}
