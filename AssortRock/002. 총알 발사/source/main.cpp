#include <tchar.h>
#include <crtdbg.h>

#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <list>

#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#endif

#include <windowsx.h>

#if defined(_DEBUG)
#define _CRTDBG_MAP_ALLOC // ����� �Ҵ��� ����ϰڴٴ� ����
#define MY_NEW new(_NORMAL_BLOCK, __FILE__, __LINE__) // ������ �� �� ���� ���� ���� ��
#endif

#define SAFE_DELETE(ptr)\
if (ptr)\
{\
	delete ptr;\
	ptr = nullptr;\
}

#define PRINT_LOG(szLog) ::OutputDebugString(_T(szLog "\n"))

// GetAsyncKeyState()�� �׻� ��Ŀ���� ���������Ƿ�
// �����찡 ��Ŀ���� �Ҿ ������ �ԷµǴ� ������ ����
// ���ڴ� ��ҹ��� ������ ���� �����Ƿ� 'W' �̷��� �־�� ��
#define PRESS_KEY(key)  (::GetAsyncKeyState(key) & 0x8000)
#define STROKE_KEY(key) (::GetAsyncKeyState(key) & 0x0001)

#define ANGLE_TO_RADIAN(angle)  (angle * (M_PI / 180.0f))
#define RADIAN_TO_ANGLE(radian) (radian * (180.0f / M_PI))

struct FLOAT_POINT
{
	FLOAT_POINT()
	{
		rX = 0.0f;
		rY = 0.0f;
	}

	FLOAT rX;
	FLOAT rY;
};

struct FLOAT_RECT
{
	FLOAT_RECT()
	{
		rLeft   = 0.0f;
		rTop    = 0.0f;
		rRight  = 0.0f;
		rBottom = 0.0f;
	}

	FLOAT rLeft;
	FLOAT rTop;
	FLOAT rRight;
	FLOAT rBottom;
};

struct FLOAT_CIRCLE
{
	FLOAT_CIRCLE()
	{
		rRadius = 0.0f;
	}

	FLOAT_POINT pt;
	FLOAT rRadius;
};

struct Bullet
{
	Bullet()
	{
		rAngle = 0.0f;
		rAccumulateDistance = 0.0f;
	}

	FLOAT_CIRCLE cir;                  // ��� ��ġ
	FLOAT rAngle;                      // �̵� ����
	FLOAT rAccumulateDistance;         // ���� �Ÿ�
	static const FLOAT LIMIT_DISTANCE; // ���� �Ÿ�
	static const FLOAT BULLET_SIZE;    // ũ��
};

struct Barrel
{
	Barrel()
	{
		rAngle = 0.0f;
	}

	FLOAT rAngle;
	FLOAT_POINT pt;                 // ���� ��ġ
	static const FLOAT BARREL_SIZE; // ���� ����
};

struct Player
{
	Player()
	{
		rAccumulateFireTime = 0.0f;
	}

	Barrel barrel;                             // ����
	FLOAT_RECT rt;                             // ��� ��ġ
	FLOAT_POINT ptCenter;                      // �߽� ��ġ
	FLOAT rAccumulateFireTime;                 // �߻縦 ���� ���� �ð�
	static const FLOAT BULLET_FIRE_DELAY_TIME; // �Ѿ� �߻� ������ �ð�
	static const FLOAT PLAYER_SIZE;            // ũ��
};

struct Enemy : public Player
{
	INT32 direction;                           // �̵� ����
	static const FLOAT BULLET_FIRE_CYCLE_TIME; // �Ѿ� �߻� �ֱ� �ӵ�
	static const FLOAT ENEMY_SIZE;             // ũ��
};

const INT32 RESOLUTION_WIDTH  = 1024;
const INT32 RESOLUTION_HEIGHT = 768;

LPCTSTR g_szWindowClass  = _T("Ruvendix");
LPCTSTR g_szProgramTitle = _T("Ruvendix");

HWND g_hMainWnd = nullptr;
HDC  g_hDC      = nullptr;

LARGE_INTEGER g_freq;
LARGE_INTEGER g_prevTick;

FLOAT g_rTimeScale    = 1.0f;
FLOAT g_rDeltaSeconds = 0.0f;
bool  g_bPause = false;

std::list<Bullet*> g_listPlayerBullet;
Player g_player;

std::list<Bullet*> g_listEnemyBullet;
Enemy g_enemy;

const FLOAT Barrel::BARREL_SIZE = 60.0f;

const FLOAT Bullet::LIMIT_DISTANCE = 500.0f;
const FLOAT Bullet::BULLET_SIZE    = 10.0f;

const FLOAT Player::BULLET_FIRE_DELAY_TIME = 0.04f;
const FLOAT Player::PLAYER_SIZE            = 40.0f;

const FLOAT Enemy::BULLET_FIRE_CYCLE_TIME = 1.0f;
const FLOAT Enemy::ENEMY_SIZE             = 60.0f;

LRESULT CALLBACK WindowProcedure(HWND hMainWnd, UINT msg, WPARAM wParam, LPARAM lParam);
HRESULT InitInstance(HINSTANCE hInstance);
HRESULT CreateProgramWindow(HINSTANCE hInstance);

HRESULT OnDrive();
HRESULT OnInit();
HRESULT OnUpdate();
HRESULT OnRender();
HRESULT OnRelease();

HRESULT InitPlayer();
HRESULT InitEnemy();

HRESULT UpdateDeltaSeconds();
HRESULT UpdatePlayer();
HRESULT UpdatePlayerBullet();
HRESULT UpdateEnemy();
HRESULT UpdateEnemyBullet();

HRESULT RenderPlayer();
HRESULT RenderPlayerBullet();
HRESULT RenderEnemy();
HRESULT RenderEnemyBullet();
HRESULT RenderText();

HRESULT ReleasePlayer();
HRESULT ReleaseEnemy();

void DrawSegment(const HDC& hDC, FLOAT rX1, FLOAT rY1, FLOAT rX2, FLOAT rY2);
void DrawSegment(const HDC& hDC, const FLOAT_POINT& pt1, const FLOAT_POINT& pt2);

void DrawRect(const HDC& hDC, const RECT& rt);
void DrawRect(const HDC& hDC, const FLOAT_RECT& rt);
void SetRect(FLOAT_RECT* pRt, FLOAT rLeft, FLOAT rTop, FLOAT rRight, FLOAT rBottom);

void DrawEllipse(const HDC& hDC, const FLOAT_CIRCLE& cir);
void SetEllipse(FLOAT_CIRCLE* pCir, FLOAT rX, FLOAT rY, FLOAT rRadius);

FLOAT TimeScale();

// 2D �浹 �˻�
bool CollidePointToPointOn2D(FLOAT rX1, FLOAT rY1, FLOAT rX2, FLOAT rY2);     // ���� ��
bool CollidePointToPointOn2D(const FLOAT_POINT& pt1, const FLOAT_POINT& pt2); // ���� ��
bool CollidePointToRectOn2D(FLOAT rX, FLOAT rY, const FLOAT_RECT& rt);        // ���� �簢��
bool CollidePointToRectOn2D(const POINT& pt, const FLOAT_RECT& rt);           // ���� �簢��
bool CollidePointToRectOn2D(const FLOAT_POINT& pt, const FLOAT_RECT& rt);     // ���� �簢��
bool CollideRectToRectOn2D(const FLOAT_RECT& rt1, const FLOAT_RECT& rt2);     // �簢���� �簢��
bool CollideCircleToCircleOn2D(const FLOAT_CIRCLE& cir1, const FLOAT_CIRCLE cir2); // ���� ��

INT32 APIENTRY _tWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
	                     LPTSTR szCmdLine, INT32 cmdShow)
{
	::QueryPerformanceFrequency(&g_freq);
	::QueryPerformanceCounter(&g_prevTick);

	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(szCmdLine);
	UNREFERENCED_PARAMETER(cmdShow);

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
	// ���� �ʱ�ȭ
	if (FAILED(OnInit()))
	{
		PRINT_LOG("���� �ʱ�ȭ ����!");
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

			OnDrive();
		}
	}
	// ==============================================

	// ���� ���Ḧ ���� ����
	OnRelease();

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
	case WM_SYSCOMMAND:
	{
		// ���� 4��Ʈ�� ���������� ����ϴ� ���̹Ƿ� ������ ��!
		if (SC_KEYMENU == (wParam & 0xFFF0))
		{
			PRINT_LOG("ALT + Enter");
			::MessageBoxA(::GetActiveWindow(), "Good", "Caption", MB_OK);
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
		(screenHeight - clientHeight) / 2, clientWidth, clientHeight, SWP_NOZORDER);

	::UpdateWindow(g_hMainWnd);
	::ShowWindow(g_hMainWnd, SW_NORMAL);

	return S_OK;
}

HRESULT OnInit()
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	InitPlayer(); // �÷��̾� ���� �ʱ�ȭ
	InitEnemy();  // ���ʹ� ���� �ʱ�ȭ	

	return S_OK;
}

HRESULT OnDrive()
{
	OnUpdate();
	OnRender();

	return S_OK;
}

HRESULT OnUpdate()
{
	// ��Ÿ������ ������Ʈ
	UpdateDeltaSeconds();
	
	// �÷��̾� ������Ʈ
	UpdatePlayer();

	// ���ʹ� ������Ʈ
	UpdateEnemy();

	return S_OK;
}

HRESULT OnRender()
{
	// �÷��̾� ����
	RenderPlayer();

	// ���ʹ� ����
	RenderEnemy();

	// �ؽ�Ʈ ����
	RenderText();

	return S_OK;
}

HRESULT OnRelease()
{
	ReleasePlayer();
	ReleaseEnemy();

	return S_OK;
}

HRESULT InitPlayer()
{
	SetRect(&g_player.rt,
		(RESOLUTION_WIDTH / 2) - (Player::PLAYER_SIZE / 2),
		RESOLUTION_HEIGHT - Player::PLAYER_SIZE,
		(RESOLUTION_WIDTH / 2) + (Player::PLAYER_SIZE / 2),
		RESOLUTION_HEIGHT);

	g_player.ptCenter.rX = (g_player.rt.rLeft + g_player.rt.rRight) / 2;
	g_player.ptCenter.rY = (g_player.rt.rTop + g_player.rt.rBottom) / 2;

	g_player.barrel.rAngle = 270.0f; // 0���� -> �� ����

	return S_OK;
}

HRESULT InitEnemy()
{
	// ���ʹ� ���� �ʱ�ȭ
	SetRect(&g_enemy.rt,
		(RESOLUTION_WIDTH / 2) - (Enemy::ENEMY_SIZE / 2),
		20,
		(RESOLUTION_WIDTH / 2) + (Enemy::ENEMY_SIZE / 2),
		Enemy::ENEMY_SIZE + 20);

	g_enemy.ptCenter.rX = (g_enemy.rt.rLeft + g_enemy.rt.rRight) / 2;
	g_enemy.ptCenter.rY = (g_enemy.rt.rTop + g_enemy.rt.rBottom) / 2;

	g_enemy.direction = 1;

	return S_OK;
}

HRESULT UpdateDeltaSeconds()
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

	if (STROKE_KEY('R'))
	{
		if (g_bPause == true)
		{
			g_bPause = false;
		}

		g_rTimeScale = 1.0f;
	}

	LARGE_INTEGER g_currentTick;
	::QueryPerformanceCounter(&g_currentTick);

	// ���� ƽī��Ʈ 10��, ���� ƽī��Ʈ 15���̸�
	// 15�� - 10�� = 5���� �ǰ� �̰� ���ļ��� ������
	// 5�� / 100�� = 1 / 20�� �Ǵµ� �ʴ��� �����̹Ƿ� 0.05�ʰ� ��!
	// 0.05�ʰ� 20�� ���̸� 1�ʰ� �ǹǷ� �ʴ� �ӵ� ����� ��������!
	g_rDeltaSeconds = (g_currentTick.QuadPart - g_prevTick.QuadPart) /
		static_cast<FLOAT>(g_freq.QuadPart);

	g_prevTick = g_currentTick;

	return S_OK;
}

HRESULT UpdatePlayer()
{
	FLOAT rMoveSpeed = 300 * g_rDeltaSeconds * TimeScale();

	RECT rtClient;
	::GetClientRect(g_hMainWnd, &rtClient);

	// ȸ���� ���� ���� ������ ������ ����

	if (PRESS_KEY('W'))
	{
		g_player.rt.rLeft   += rMoveSpeed * std::cos(ANGLE_TO_RADIAN(g_player.barrel.rAngle));
		g_player.rt.rRight  += rMoveSpeed * std::cos(ANGLE_TO_RADIAN(g_player.barrel.rAngle));
		g_player.rt.rTop    += rMoveSpeed * std::sin(ANGLE_TO_RADIAN(g_player.barrel.rAngle));
		g_player.rt.rBottom += rMoveSpeed * std::sin(ANGLE_TO_RADIAN(g_player.barrel.rAngle));
	}

	if (g_player.rt.rTop < 0.0f)
	{
		g_player.rt.rTop    = 0.0f;
		g_player.rt.rBottom = Player::PLAYER_SIZE;
	}

	//if (PRESS_KEY('A'))
	//{
	//	g_player.rt.rLeft  -= rMoveSpeed;
	//	g_player.rt.rRight -= rMoveSpeed;

	//	if (g_player.rt.rLeft < 0.0f)
	//	{
	//		g_player.rt.rLeft  = 0.0f;
	//		g_player.rt.rRight = Player::PLAYER_SIZE;
	//	}
	//}

	if (g_player.rt.rLeft < 0.0f)
	{
		g_player.rt.rLeft  = 0.0f;
		g_player.rt.rRight = Player::PLAYER_SIZE;
	}

	if (PRESS_KEY('S'))
	{
		g_player.rt.rLeft   -= rMoveSpeed * std::cos(ANGLE_TO_RADIAN(g_player.barrel.rAngle));
		g_player.rt.rRight  -= rMoveSpeed * std::cos(ANGLE_TO_RADIAN(g_player.barrel.rAngle));
		g_player.rt.rTop    -= rMoveSpeed * std::sin(ANGLE_TO_RADIAN(g_player.barrel.rAngle));
		g_player.rt.rBottom -= rMoveSpeed * std::sin(ANGLE_TO_RADIAN(g_player.barrel.rAngle));
	}

	if (g_player.rt.rBottom > rtClient.bottom)
	{
		g_player.rt.rTop    = rtClient.bottom - Player::PLAYER_SIZE;
		g_player.rt.rBottom = rtClient.bottom;
	}

	//if (PRESS_KEY('D'))
	//{
	//	g_player.rt.rLeft  += rMoveSpeed;
	//	g_player.rt.rRight += rMoveSpeed;
	//}

	if (g_player.rt.rRight > rtClient.right)
	{
		g_player.rt.rLeft  = rtClient.right - Player::PLAYER_SIZE;
		g_player.rt.rRight = rtClient.right;
	}

	// �߽� ��ġ ����
	g_player.ptCenter.rX = (g_player.rt.rLeft + g_player.rt.rRight) / 2;
	g_player.ptCenter.rY = (g_player.rt.rTop + g_player.rt.rBottom) / 2;

	g_player.rAccumulateFireTime += g_rDeltaSeconds * TimeScale();
	if (g_player.rAccumulateFireTime > Player::BULLET_FIRE_DELAY_TIME)
	{
		g_player.rAccumulateFireTime -= Player::BULLET_FIRE_DELAY_TIME;
		if (PRESS_KEY(VK_SPACE))
		{
			Bullet* pBullet = MY_NEW Bullet;
			if (pBullet != nullptr)
			{
				::SetEllipse(&pBullet->cir, g_player.ptCenter.rX,
					g_player.ptCenter.rY, Bullet::BULLET_SIZE);
				pBullet->rAngle = g_player.barrel.rAngle;
				pBullet->rAccumulateDistance = 0.0f;

				g_listPlayerBullet.push_back(pBullet);
			}
		}

		// ��ų �׽�Ʈ
		// 360 / �ݺ�Ƚ�� => �� �߻簢
		// �� �߻簢 * (�ݺ��� - (�ݺ�Ƚ�� / 2))
		// Ȧ���� �ڿ�������
		if (PRESS_KEY('T'))
		{
			//FLOAT32 angleTable[4] = { 270.0f - 22.5f, 270.0f - 22.5f * 3, 270.0f + 22.5f, 270.0f + 22.5f * 3 };
			for (INT32 i = 0; i < 5; ++i)
			{
				Bullet* pBullet = MY_NEW Bullet;
				if (pBullet != nullptr)
				{
					::SetEllipse(&pBullet->cir, g_player.ptCenter.rX,
						g_player.ptCenter.rY, Bullet::BULLET_SIZE);
					pBullet->rAngle = g_player.barrel.rAngle - (18 * (i - 2)); // angleTable[i];
					pBullet->rAccumulateDistance = 0.0f;

					g_listPlayerBullet.push_back(pBullet);
				}
			}
		}

		if (PRESS_KEY('Y'))
		{
			for (INT32 i = 0; i < 36; ++i)
			{
				Bullet* pBullet = MY_NEW Bullet;
				if (pBullet != nullptr)
				{
					::SetEllipse(&pBullet->cir, g_player.ptCenter.rX,
						g_player.ptCenter.rY, Bullet::BULLET_SIZE);
					pBullet->rAngle = g_player.barrel.rAngle - (10 * (i - 18));
					pBullet->rAccumulateDistance = 0.0f;

					g_listPlayerBullet.push_back(pBullet);
				}
			}
		}
	}

	// �Ѿ��� ������ ���� ������Ʈ ȣ��
	if (g_listPlayerBullet.empty() == false)
	{
		UpdatePlayerBullet();
	}

	if (PRESS_KEY(VK_LBUTTON))
	{
		// ���콺 ��ư üũ
		POINT ptMouse;
		::GetCursorPos(&ptMouse);
		::ScreenToClient(g_hMainWnd, &ptMouse);

		// 4���� ������ ��� �����ϴ� �ͺ��� �ϳ��� �ƴϸ� �ƴ� �� ����
		if (CollidePointToRectOn2D(ptMouse, g_player.rt))
		//if (::PtInRect(&rt, ptMouse))
		{
			::MessageBox(g_hMainWnd, _T("���콺 Ŭ�� �׽�Ʈ!"), _T("�޽����ڽ�"), MB_OK);
		}
	}

	// ���� ó��
	if (PRESS_KEY('Q'))
	{
		g_player.barrel.rAngle += rMoveSpeed;
		if (g_player.barrel.rAngle >= 360.0f)
		{
			g_player.barrel.rAngle = 0.0f;
		}
	}

	if (PRESS_KEY('E'))
	{
		g_player.barrel.rAngle -= rMoveSpeed;
		if (g_player.barrel.rAngle <= 0.0f)
		{
			g_player.barrel.rAngle = 360.0f;
		}
	}

	g_player.barrel.pt.rX =
		g_player.ptCenter.rX + Barrel::BARREL_SIZE * std::cos(ANGLE_TO_RADIAN(g_player.barrel.rAngle));
	g_player.barrel.pt.rY =
		g_player.ptCenter.rY + Barrel::BARREL_SIZE * std::sin(ANGLE_TO_RADIAN(g_player.barrel.rAngle));

	return S_OK;
}

HRESULT UpdatePlayerBullet()
{
	FLOAT rMoveSpeed = 600 * g_rDeltaSeconds * TimeScale();

	std::list<Bullet*>::iterator iter = g_listPlayerBullet.begin();
	std::list<Bullet*>::iterator iterEnd = g_listPlayerBullet.end();
	while (iter != iterEnd)
	{
		if ((*iter) == nullptr)
		{
			continue;
		}

		(*iter)->cir.pt.rX += rMoveSpeed * std::cos(ANGLE_TO_RADIAN((*iter)->rAngle));
		(*iter)->cir.pt.rY += rMoveSpeed * std::sin(ANGLE_TO_RADIAN((*iter)->rAngle));
		(*iter)->rAccumulateDistance += rMoveSpeed;

		if ( ((*iter)->rAccumulateDistance > Bullet::LIMIT_DISTANCE) ||
			 ((*iter)->cir.pt.rY + (*iter)->cir.rRadius < 0.0f) )
		{
			SAFE_DELETE(*iter);
			iter = g_listPlayerBullet.erase(iter);
		}
		else
		{
			++iter;
		}
	}

	return S_OK;
}

HRESULT UpdateEnemy()
{
	FLOAT rMoveSpeed = 400 * g_rDeltaSeconds * TimeScale() * g_enemy.direction;

	g_enemy.rt.rLeft  += rMoveSpeed;
	g_enemy.rt.rRight += rMoveSpeed;

	RECT rtClient;
	::GetClientRect(g_hMainWnd, &rtClient);

	if (g_enemy.rt.rLeft < 0.0f)
	{
		g_enemy.rt.rLeft  = 0.0f;
		g_enemy.rt.rRight = Enemy::ENEMY_SIZE;
		g_enemy.direction *= -1;
	}

	if (g_enemy.rt.rRight > rtClient.right)
	{
		g_enemy.rt.rLeft  = RESOLUTION_WIDTH - Enemy::ENEMY_SIZE;
		g_enemy.rt.rRight = RESOLUTION_WIDTH;
		g_enemy.direction *= -1;
	}
	
	// �߽� ��ġ ����
	g_enemy.ptCenter.rX = (g_enemy.rt.rLeft + g_enemy.rt.rRight) / 2;
	g_enemy.ptCenter.rY = (g_enemy.rt.rTop + g_enemy.rt.rBottom) / 2;

	g_enemy.rAccumulateFireTime += g_rDeltaSeconds * TimeScale();
	if (g_enemy.rAccumulateFireTime > Enemy::BULLET_FIRE_CYCLE_TIME)
	{
		g_enemy.rAccumulateFireTime -= Enemy::BULLET_FIRE_CYCLE_TIME;

		Bullet* pBullet = MY_NEW Bullet;
		if (pBullet != nullptr)
		{
			::SetEllipse(&pBullet->cir, g_enemy.ptCenter.rX,
				g_enemy.ptCenter.rY, Bullet::BULLET_SIZE);
			pBullet->rAccumulateDistance = RESOLUTION_HEIGHT;

			g_listEnemyBullet.push_back(pBullet);
		}
	}

	// �Ѿ��� ������ ���� ������Ʈ ȣ��
	if (g_listEnemyBullet.empty() == false)
	{
		UpdateEnemyBullet();
	}

	return S_OK;
}

HRESULT UpdateEnemyBullet()
{
	FLOAT rMoveSpeed = 600 * g_rDeltaSeconds * TimeScale();

	std::list<Bullet*>::iterator iter = g_listEnemyBullet.begin();
	std::list<Bullet*>::iterator iterEnd = g_listEnemyBullet.end();
	while (iter != iterEnd)
	{
		if ((*iter) == nullptr)
		{
			continue;
		}

		(*iter)->cir.pt.rY += rMoveSpeed;
		if ((*iter)->cir.pt.rY - (*iter)->cir.rRadius >= RESOLUTION_HEIGHT)
		{
			SAFE_DELETE(*iter);
			iter = g_listEnemyBullet.erase(iter);
		}
		else
		{
			++iter;
		}
	}

	return S_OK;
}

HRESULT RenderPlayer()
{
	DrawRect(g_hDC, g_player.rt);
	RenderPlayerBullet();
	DrawSegment(g_hDC, g_player.ptCenter, g_player.barrel.pt);
	
	return S_OK;
}

HRESULT RenderPlayerBullet()
{
	for (auto iter : g_listPlayerBullet)
	{
		if (iter == nullptr)
		{
			continue;
		}

		DrawEllipse(g_hDC, iter->cir);
	}

	return S_OK;
}

HRESULT RenderEnemy()
{
	DrawRect(g_hDC, g_enemy.rt);
	RenderEnemyBullet();
	return S_OK;
}

HRESULT RenderEnemyBullet()
{
	for (auto iter : g_listEnemyBullet)
	{
		if (iter == nullptr)
		{
			continue;
		}

		DrawEllipse(g_hDC, iter->cir);
	}

	return S_OK;
}

HRESULT RenderText()
{
	TCHAR szPause[64];
	::ZeroMemory(szPause, _countof(szPause));
	if (g_bPause)
	{
		_stprintf_s(szPause, _countof(szPause), _T("���α׷� �Ͻ�����(TimeScale : 0.00)"));
		::TextOut(g_hDC, 0, 0, szPause, _tcslen(szPause));
	}
	else
	{
		_stprintf_s(szPause, _countof(szPause), _T("�Ͻ����� ���¾ƴ�(TimeScale : %.2f)"), g_rTimeScale);
		::TextOut(g_hDC, 0, 0, szPause, _tcslen(szPause));
	}

	return S_OK;
}

HRESULT ReleasePlayer()
{
	// ���� ��� for���� �����̳��� ������Ʈ ������ �����ϹǷ�
	// ���ͷ����Ϳ��Դ� ������ ����!
	// ���� ���ͷ����Ϳ��� ������ �ַ��� ���� �����ؾ� ��!

	// �Ѿ� ����
	std::list<Bullet*>::iterator iter = g_listPlayerBullet.begin();
	std::list<Bullet*>::iterator iterEnd = g_listPlayerBullet.end();
	while (iter != iterEnd)
	{
		if ((*iter) == nullptr)
		{
			continue;
		}

		SAFE_DELETE(*iter);
		iter = g_listPlayerBullet.erase(iter);
	}
	g_listPlayerBullet.clear();

	return S_OK;
}

HRESULT ReleaseEnemy()
{
	// �Ѿ� ����
	std::list<Bullet*>::iterator iter = g_listEnemyBullet.begin();
	std::list<Bullet*>::iterator iterEnd = g_listEnemyBullet.end();
	while (iter != iterEnd)
	{
		if ((*iter) == nullptr)
		{
			continue;
		}

		SAFE_DELETE(*iter);
		iter = g_listEnemyBullet.erase(iter);
	}
	g_listEnemyBullet.clear();

	return S_OK;
}

void DrawSegment(const HDC& hDC, FLOAT rX1, FLOAT rY1, FLOAT rX2, FLOAT rY2)
{
	::MoveToEx(hDC, rX1, rY1, nullptr);
	::LineTo(hDC, rX2, rY2);
}

void DrawSegment(const HDC& hDC, const FLOAT_POINT& pt1, const FLOAT_POINT& pt2)
{
	DrawSegment(hDC, pt1.rX, pt1.rY, pt2.rX, pt2.rY);
}

void DrawRect(const HDC& hDC, const RECT& rt)
{
	::Rectangle(hDC, rt.left, rt.top, rt.right, rt.bottom);
}

void DrawRect(const HDC& hDC, const FLOAT_RECT& rt)
{
	::Rectangle(hDC, rt.rLeft, rt.rTop, rt.rRight, rt.rBottom);
}

void SetRect(FLOAT_RECT* pRt, FLOAT rLeft, FLOAT rTop, FLOAT rRight, FLOAT rBottom)
{
	if (pRt == nullptr)
	{
		return;
	}

	pRt->rLeft   = rLeft;
	pRt->rTop    = rTop;
	pRt->rRight  = rRight;
	pRt->rBottom = rBottom;
}

void DrawEllipse(const HDC& hDC, const FLOAT_CIRCLE& cir)
{
	RECT rt =
	{ 
		cir.pt.rX - cir.rRadius,
		cir.pt.rY - cir.rRadius,
		cir.pt.rX + cir.rRadius,
		cir.pt.rY + cir.rRadius
	};
	::Ellipse(hDC, rt.left, rt.top, rt.right, rt.bottom);
}

void SetEllipse(FLOAT_CIRCLE* pCir, FLOAT rX, FLOAT rY, FLOAT rRadius)
{
	if (pCir == nullptr)
	{
		return;
	}

	pCir->pt.rX = rX;
	pCir->pt.rY = rY;
	pCir->rRadius = rRadius;
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

bool CollidePointToPointOn2D(FLOAT rX1, FLOAT rY1, FLOAT rX2, FLOAT rY2)
{
	if ( (std::abs(rX2 - rX1) <= FLT_EPSILON) &&
		 (std::abs(rY2 - rY1) <= FLT_EPSILON) )
	{
		return true;
	}

	return false;
}

bool CollidePointToPointOn2D(const FLOAT_POINT& pt1, const FLOAT_POINT& pt2)
{
	return CollidePointToPointOn2D(pt1.rX, pt1.rY, pt2.rX, pt2.rY);
}

bool CollidePointToRectOn2D(FLOAT rX, FLOAT rY, const FLOAT_RECT& rt)
{
	if ( (rX > rt.rLeft) &&
		 (rX < rt.rRight) &&
		 (rY > rt.rTop) &&
		 (rY < rt.rBottom) )
	{
		return true;
	}

	return false;
}

bool CollidePointToRectOn2D(const POINT& pt, const FLOAT_RECT& rt)
{
	return CollidePointToRectOn2D(pt.x, pt.y, rt);
}

bool CollidePointToRectOn2D(const FLOAT_POINT& pt, const FLOAT_RECT& rt)
{
	return CollidePointToRectOn2D(pt.rX, pt.rY, rt);
}

bool CollideRectToRectOn2D(const FLOAT_RECT& rt1, const FLOAT_RECT& rt2)
{
	if ( (rt1.rLeft < rt2.rRight) &&
		 (rt1.rRight > rt2.rLeft) &&
		 (rt1.rTop < rt2.rBottom) &&
		 (rt1.rBottom > rt2.rTop) )
	{
		return true;
	}

	return false;
}

bool CollideCircleToCircleOn2D(const FLOAT_CIRCLE& cir1, const FLOAT_CIRCLE cir2)
{
	FLOAT rDistancePow = std::pow(cir2.pt.rX - cir1.pt.rX, 2) + std::pow(cir2.pt.rY - cir1.pt.rY, 2);
	FLOAT rRadiusPow   = std::pow(cir1.rRadius + cir2.rRadius, 2);
	if (rDistancePow < rRadiusPow)
	{
		return true;
	}

	return false;
}
