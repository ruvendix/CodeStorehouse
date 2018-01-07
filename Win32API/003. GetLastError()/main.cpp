/*
 * <���� ����>
 * GetLastError() �����Դϴ�.
 * �� �Լ��� SetLastError()�� ������ ���� �������� �Լ��Դϴ�.
 * ��ȯ���� �������� FormatMessage()�� �̿��ϸ� ���ڿ��� Ȯ���� �� �ֽ��ϴ�.
 * FormatMessager()�� ����ϸ� LocalFree()�� ���� ����ؾ� �մϴ�.
 * ���ڿ��� �ý��� �⺻ �������� ��µ����� �ڼ��� ������ ���� ����� �����ϴ� �� �����ϴ�.
 */

#include <tchar.h>   // ��Ƽ����Ʈ�� �����ڵ带 ���ÿ� ȣȯ�ϱ� ���� ���Խ�ŵ�ϴ�.
#include <windows.h> // Win32API�� �̿��ϱ� ���� �⺻ ��� �����Դϴ�.

LPCSTR lpStrClassName         = "Ruvendix";
LPCSTR lpStrMainWindowCpation = "Program Caption";

void ShowLastError(INT32 errorCode);

INT32 APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, INT32 cmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);

	WNDCLASS wc;
	ZeroMemory(&wc, sizeof(wc));

	wc.hInstance     = hInstance;       
	wc.lpszClassName = lpStrClassName;  

	if (RegisterClass(&wc) == 0)
	{
		ShowLastError(GetLastError());
	}

	CreateWindowEx(
		WS_EX_TOPMOST,                  // ������ Ȯ�� ��Ÿ���Դϴ�.
		lpStrClassName,                 // ������ Ŭ���� �̸��Դϴ�.
		lpStrMainWindowCpation,         // ������ ĸ���Դϴ�.
		WS_OVERLAPPEDWINDOW | WS_CHILD, // ������ ��Ÿ���Դϴ�.
		CW_USEDEFAULT,                  // �����찡 ������ X��ǥ�Դϴ�. CW_USEDEFAULT�� �ü���� �ʱ� ��ġ�� �����ݴϴ�.
		CW_USEDEFAULT,                  // �����찡 ������ Y��ǥ�Դϴ�. CW_USEDEFAULT�� �ü���� �ʱ� ��ġ�� �����ݴϴ�.
		800,                            // ������ �������� ���� ũ���Դϴ�.
		600,                            // ������ �������� ���� ũ���Դϴ�.
		nullptr,                        // �θ� �����츦 �����մϴ�.
		nullptr,                        // �޴��� �����մϴ�.
		hInstance,                      // �ν��Ͻ��� �����մϴ�.
		nullptr                         // �߰� ������ ������ lParam�� �����մϴ�.
	);

	ShowLastError(GetLastError());

	return 0;
}

void ShowLastError(INT32 errorCode)
{
	LPTSTR pStrError = nullptr;
	
	// ���� ��ȣ�� ���ڿ��� �������ִ� �Լ��Դϴ�.
	// �÷��״� �⺻������ (���� ���� �Ҵ�, �ý��� �޽��� ���̺�) �̷��� ����մϴ�.
	FormatMessage
	(
		// �Լ� �÷����Դϴ�.
		FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM,

		// �޽����� ���ǵ� ��ġ�ε� �⺻�� nullptr�Դϴ�.
		// FORMAT_MESSAGE_FROM_HMODULE �Ǵ� FORMAT_MESSAGE_FROM_STRING��
		// �����Ǿ����� ������ ���õ˴ϴ�.
		nullptr,

		// ���ڿ��� ��ȯ�� ���� ��ȣ�Դϴ�.
		// FORMAT_MESSAGE_FROM_STRING�� �����Ǿ������� ���õ˴ϴ�.
		errorCode,

		// ��ȯ�� ���ڿ��� ��� �����Դϴ�.
		// LANG_NEUTRAL�� SUBLANG_DEFAULT�� �����ϸ� �����ǿ��� ������ ���� �����˴ϴ�.
		// ������ ������ ������ �����Ƿ� ����� �����ϴ� �� ��õ�մϴ�.
		// ���� ������ LANG_ENGLISH, SUBLANG_ENGLISH_US�Դϴ�.
		// MAKELANGID() ��ũ�� �Լ��� ��� �÷��׸� ���ļ� ID�� ������ݴϴ�.
		// FORMAT_MESSAGE_FROM_STRING�� �����Ǿ������� ���õ˴ϴ�.
		MAKELANGID(LANG_ENGLISH, SUBLANG_ENGLISH_US),

		// ��ȯ�� ���ڿ��� ������ �����Դϴ�.
		// FORMAT_MESSAGE_ALLOCATE_BUFFER�� �����Ǿ�������
		// ���ο��� LocalAlloc()�� �̿��� �����Ҵ��մϴ�.
		// ����� ���۴� 64KB(64,000����Ʈ) �̸��̾�� �մϴ�.
		// �����Ͱ� �⸮Ű�� �ּҸ� �����ؾ� �ϹǷ� ���� �����͸� �־�� �մϴ�. 
		reinterpret_cast<LPTSTR>(&pStrError),

		// ��ȯ�� ���ڿ��� ������ ������ ũ���Դϴ�.
		// FORMAT_MESSAGE_ALLOCATE_BUFFER�� �����Ǿ�������
		// ���ο��� �����Ҵ��� ũ��� �����ϹǷ� 0�� ������ �˴ϴ�.
		// FORMAT_MESSAGE_ALLOCATE_BUFFER�� �����Ǿ����� ������
		// �⺻������ TCHAR��ŭ�� ũ��� �����մϴ�.
		0,

		// �߰��� �����ϴ� �ɼ��Դϴ�. ������ ��������(va_list)�� ������ �����Դϴ�.
		// �⺻���� �� ���ڿ��Դϴ�. va_list* �����̹Ƿ� ���� �����Ͱ� �˴ϴ�. (va_list => char*)
		nullptr
	);

	MessageBox(nullptr, pStrError, "���� �ȳ��Դϴ�", MB_ICONERROR);
	LocalFree(pStrError); // FormatMessage()���� �Ҵ�� �޸𸮸� �����մϴ�.
}