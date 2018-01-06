/*
 * <���� ����>
 * Win32API �⺻ ���α׷��Դϴ�.
 * ���信 ȥ���� �� �� �ִ� �κ��� �־ �ʿ��� �κи� �ۼ��߽��ϴ�.
 * �⺻ ���α׷��� Win32API�� �پ��� ��ɵ��� �߰��ϸ� �Ǹ��� ������ ���α׷��� ���� �� �ֽ��ϴ�.
 * �ڵ� ���� �ڵ尡 �����ϱ� ������ ���� �̷��� ó������ �ۼ��� �ʿ�� �����ϴ�.
 * �׳� ���� ���ظ� ���� �ѹ� ������ �ۼ��ϸ� ����ϴٰ� �����մϴ�.
 * ����� Win32API�� ��Ƽ����Ʈ, �����ڵ� ������ �����մϴ�. 
 */

#include <windows.h> // Win32API�� �̿��ϱ� ���� �⺻ ��� �����Դϴ�.

LPCSTR lpStrClassName      = "Win32API Basic Window Class";
LPCSTR lpStrMainWindowName = "Win32API Basic Main Window";

LRESULT CALLBACK WindowProcedure(HWND hWnd, UINT32 Message, WPARAM wParam, LPARAM lParam);

// ������ ���α׷��ֿ����� C, C++���� ����� main()�� �ƴ϶� winMain()�� �ۼ��մϴ�.
// Win32API������ ���� �ڷ����� ȿ�������� ����ϱ� ���� ����Ʈ�� �����մϴ�.
// �Ǽ� �ڷ����� �ϰ����� ��Ű�� ���� FLOAT, DOUBLE �̷��� �빮�ڷ� ǥ���մϴ�.
//
// APIENTRY�� Win32API�� �⺻ ȣ�� �Ծ��� __stdcall�� �ǹ��մϴ�.
// __stdcall�� ���ڸ� <-(������) ������ �Ű������� �����ϰ�, ���� �������� ȣ��� �Լ����� �����մϴ�.
// C, C++���� ����ߴ� �Լ�(printf(), fopen() ��)���� �Լ� ȣ�� �Ծ��� __cdecl�Դϴ�.
//
// H�� ���۵Ǹ� �ڵ�(Handle)�� �ǹ��ϴµ� �ڵ��� �ü���� �Ҵ����ִ� �ڿ��� �������Դϴ�.
// ���� �ڿ��� ������ ���� ������ �ڵ��� �̿��ϸ� ���������� �ڿ��� ������ �� �ֽ��ϴ�.
// �ν��Ͻ�(Instance)�� �ü���� ��ϵ� ���α׷��� ���մϴ�. ���� ���α׷��̸� �ν��Ͻ��� �����ϴ�.
// ������ ���μ���(Process, �޸𸮿� Ȱ��ȭ�� ���α׷�)�� PID(Process Identification)�� �Ǵ��ϱ� ������
// ���� ���α׷��� �ٸ��ٰ� �����մϴ�.
INT32 APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, INT32 cmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance); // �� ���� �Ű������� ǥ���մϴ�.

	//////////////////////////////////////////////////////////////////////////
	// ������ Ŭ����(Window Class)�� �����մϴ�.
	// ���⼭ ���ϴ� Ŭ������ ��ü����(C++, C#, JAVA ��)�� Ŭ������ �ƴմϴ�.
	// ��Ƽ���α׷���(Multiprogramming)�� ���� �ڿ�(Resource)�� �����ϱ� ���� ����ü�Դϴ�.
	// Class���� "����"��� �浵 �ִµ� �� ������ ���Ǿ����ϴ�.
	// ���ӿ��� ���� Ŭ����, ������ Ŭ���� �̷��� ǥ���ϱ⵵ �ϴµ� �̰Ͱ� ���� ���Դϴ�.
	WNDCLASS wc;
	ZeroMemory(&wc, sizeof(wc)); // ���������� memset(&wc, 0, sizeof(wc))�Դϴ�.

	//wc.cbSize        = sizeof(wc);    // ������ Ŭ������ ũ��
	wc.hInstance     = hInstance;       // �ü���� ����� �ν��Ͻ�
	wc.lpszClassName = lpStrClassName;  // ������ Ŭ���� �̸�
	wc.lpfnWndProc   = WindowProcedure; // �޽����� ó���� ������ ���ν���, ������ ���� ����

	// �ʱ�ȭ�� ���� ������ Ŭ������ �ü���� ����մϴ�.
	// �ٸ� �����츦 ����� ������ ����� ������ Ŭ������ ��Ȱ���ϸ� �˴ϴ�.
	// ���� ���� �ʿ� ���� wcex�� ������ �缳���ؼ� ������ָ� �˴ϴ�.
	RegisterClass(&wc);

	//////////////////////////////////////////////////////////////////////////
	// �����츦 �����մϴ�.
	// ���ڴ� ������� ������ �����ϴ�.
	// ������ Ŭ���� �̸� | ������ �̸� | ������ ��Ÿ�� | ������ x ��ǥ | ������ y ��ǥ
	// ���� ���� | ���� ���� | �θ� ������ | �޴� | �ν��Ͻ� | ������ ����
	//
	// ������ ���ڴ� ������ ���ν����� lParam���� ���޵Ǵ� �����Դϴ�.
	// CreateWindow()�� WM_CREATE �޽����� �߻���Ű�µ� �̶� ������ ���ν�������
	// CREATESTRUCT�� lParam�� ���� ���� �� �ֽ��ϴ�.
	// ���⼭�� ���信 ȥ���� �� �� �ִٰ� �Ǵ��ؼ� �ش� ������ ���ܽ�ŵ�ϴ�.
	//
	// WS_OVERLAPPEDWINDOW�� Win32API ���α׷��� �⺻ ������ ��Ÿ���Դϴ�.
	// CW_USEDEFAULT�� Win32API ���α׷��� �⺻���Դϴ�.
	HWND hWnd = CreateWindow(lpStrClassName, lpStrMainWindowName, WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, CW_USEDEFAULT, 800, 600, nullptr, nullptr, hInstance, nullptr);

	// ������ �����츦 �����մϴ�.
	UpdateWindow(hWnd); 

	// ������ �����츦 �����ݴϴ�. winMain()�� cmdShow�� ���˴ϴ�.
	// cmdShow�� �⺻���� SW_NORMAL�Դϴ�.
	ShowWindow(hWnd, cmdShow);
	
	//////////////////////////////////////////////////////////////////////////
	// �޽����� ó���� �޽��� ������ �ۼ��մϴ�.
	// ���α׷����� �߻��� �޽������� �ü���� �����ϴ� �޽��� ť�� ����Ǿ
	// �켱������ ���� �� �޽����� ó���˴ϴ�. �Ϻ� �޽����� �޽��� ���̺��̶�� ���� ����˴ϴ�.
	// �켱������ �޽��� ť > �޽��� ���̺��Դϴ�. �޽��� ���̺� ����Ǵ� ��ǥ���� �޽����� WM_PAINT�Դϴ�.
	MSG message;
	ZeroMemory(&message, sizeof(message));

	while (true)
	{
		if (message.message == WM_QUIT) // ���� �޽����� ������ �޽��� ������ Ż���մϴ�.
		{
			break;
		}

		if (GetMessage(&message, nullptr, 0, 0))
		{
			DispatchMessage(&message);
		}
	}

	return static_cast<INT32>(message.message);
}

LRESULT CALLBACK WindowProcedure(HWND hWnd, UINT32 Message, WPARAM wParam, LPARAM lParam)
{
   // switch ~ case ���ο��� ���������� ����Ϸ���
   //
   // case 1:
   // {
   //     INT32 num;
   //     break;
   // }
   //
   // �̷��� ����� �մϴ�. �� ������ ������ ������ �߻��� �� �ֽ��ϴ�.
	switch (Message)
	{
		case WM_CLOSE:
		{
			INT32 a = 100;
			PostQuitMessage(0); // 0�� WinMain()�� ������ ���Դϴ�.
			return 0;
		}
	}

	// �⺻������ ó���Ǿ�� �� �޽����� �Ʒ��� �ִ� �Լ����� �ñ�ϴ�.
	// DefWindowProc�� Default Window Procedure�� �����Դϴ�.
	return DefWindowProc(hWnd, Message, wParam, lParam);
}