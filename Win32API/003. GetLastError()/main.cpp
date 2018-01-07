/*
 * <파일 설명>
 * GetLastError() 예제입니다.
 * 이 함수는 SetLastError()로 설정된 값을 가져오는 함수입니다.
 * 반환값은 정수지만 FormatMessage()를 이용하면 문자열로 확인할 수 있습니다.
 * FormatMessager()를 사용하면 LocalFree()도 같이 사용해야 합니다.
 * 문자열은 시스템 기본 설정으로 출력되지만 자세한 정보를 위해 영어로 설정하는 게 좋습니다.
 */

#include <tchar.h>   // 멀티바이트와 유니코드를 동시에 호환하기 위해 포함시킵니다.
#include <windows.h> // Win32API를 이용하기 위한 기본 헤더 파일입니다.

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
		WS_EX_TOPMOST,                  // 윈도우 확장 스타일입니다.
		lpStrClassName,                 // 윈도우 클래스 이름입니다.
		lpStrMainWindowCpation,         // 윈도우 캡션입니다.
		WS_OVERLAPPEDWINDOW | WS_CHILD, // 윈도우 스타일입니다.
		CW_USEDEFAULT,                  // 윈도우가 생성될 X좌표입니다. CW_USEDEFAULT는 운영체제가 초기 위치를 정해줍니다.
		CW_USEDEFAULT,                  // 윈도우가 생성될 Y좌표입니다. CW_USEDEFAULT는 운영체제가 초기 위치를 정해줍니다.
		800,                            // 생성될 윈도우의 가로 크기입니다.
		600,                            // 생성될 윈도우의 세로 크기입니다.
		nullptr,                        // 부모 윈도우를 설정합니다.
		nullptr,                        // 메뉴를 설정합니다.
		hInstance,                      // 인스턴스를 설정합니다.
		nullptr                         // 추가 정보를 전달할 lParam을 설정합니다.
	);

	ShowLastError(GetLastError());

	return 0;
}

void ShowLastError(INT32 errorCode)
{
	LPTSTR pStrError = nullptr;
	
	// 오류 번호를 문자열로 변경해주는 함수입니다.
	// 플래그는 기본적으로 (버퍼 내부 할당, 시스템 메시지 테이블) 이렇게 사용합니다.
	FormatMessage
	(
		// 함수 플래그입니다.
		FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM,

		// 메시지가 정의된 위치인데 기본은 nullptr입니다.
		// FORMAT_MESSAGE_FROM_HMODULE 또는 FORMAT_MESSAGE_FROM_STRING이
		// 설정되어있지 않으면 무시됩니다.
		nullptr,

		// 문자열로 변환할 오류 번호입니다.
		// FORMAT_MESSAGE_FROM_STRING이 설정되어있으면 무시됩니다.
		errorCode,

		// 변환될 문자열의 언어 설정입니다.
		// LANG_NEUTRAL과 SUBLANG_DEFAULT로 설정하면 제어판에서 설정된 언어로 설정됩니다.
		// 하지만 번역에 문제가 있으므로 영어로 설정하는 걸 추천합니다.
		// 영어 설정은 LANG_ENGLISH, SUBLANG_ENGLISH_US입니다.
		// MAKELANGID() 매크로 함수는 언어 플래그를 합쳐서 ID로 만들어줍니다.
		// FORMAT_MESSAGE_FROM_STRING이 설정되어있으면 무시됩니다.
		MAKELANGID(LANG_ENGLISH, SUBLANG_ENGLISH_US),

		// 변환된 문자열을 저장할 버퍼입니다.
		// FORMAT_MESSAGE_ALLOCATE_BUFFER가 설정되어있으면
		// 내부에서 LocalAlloc()을 이용해 동적할당합니다.
		// 참고로 버퍼는 64KB(64,000바이트) 미만이어야 합니다.
		// 포인터가 기리키는 주소를 설정해야 하므로 더블 포인터를 넣어야 합니다. 
		reinterpret_cast<LPTSTR>(&pStrError),

		// 변환된 문자열을 저장할 버퍼의 크기입니다.
		// FORMAT_MESSAGE_ALLOCATE_BUFFER가 설정되어있으면
		// 내부에서 동적할당한 크기로 설정하므로 0을 넣으면 됩니다.
		// FORMAT_MESSAGE_ALLOCATE_BUFFER가 설정되어있지 않으면
		// 기본적으로 TCHAR만큼의 크기로 설정합니다.
		0,

		// 추가로 설정하는 옵션입니다. 형식은 가변인자(va_list)의 포인터 형식입니다.
		// 기본값은 널 문자열입니다. va_list* 형식이므로 더블 포인터가 됩니다. (va_list => char*)
		nullptr
	);

	MessageBox(nullptr, pStrError, "오류 안내입니다", MB_ICONERROR);
	LocalFree(pStrError); // FormatMessage()에서 할당된 메모리를 해제합니다.
}