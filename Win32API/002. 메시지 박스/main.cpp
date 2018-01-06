/*
 * <파일 설명>
 * 메시지 박스 테스트 프로그램입니다.
 * 메시지 박스는 사용자에게 현재 프로그램의 상황을 알려줄 때 사용합니다.
 * 주로 오류를 사용자한테 보여줄 때 사용합니다.
 */

#include <cstdio>  // snprintf()를 사용하기 위해 포함시킵니다.
#include <cstdlib> // _countof 매크로를 사용하기 위해 포함시킵니다. 배열의 개수를 구해주는 매크로 함수입니다.

// 윈도우 헤더 파일에서 최소로 필요로 하는 것들만 포함시킵니다.
#ifdef WIN32_LEAN_AND_MEAN
#include <windows.h>
#else
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#undef  WIN32_LEAN_AND_MEAN
#endif

struct MessageBoxStyleInfo
{
	INT32  styleValue;
	LPCSTR strStyleGuide;
};

INT32 main()
{
	MessageBoxStyleInfo messageBoxStyleInfoTable[] =
	{
        { MB_OK,                "확인" },
        { MB_OKCANCEL,          "확인 | 취소" },
        { MB_ABORTRETRYIGNORE,  "중단 | 다시 시도 | 무시" },
        { MB_YESNO,             "예 | 아니오" },
        { MB_YESNOCANCEL,       "예 | 아니오 | 취소" },
        { MB_RETRYCANCEL,       "다시 시도 | 취소" },
        { MB_CANCELTRYCONTINUE, "취소 | 다시 시도 | 계속" },
        { MB_HELP,              "확인 | 도움말" },
        { MB_USERICON,          "사용자 정의 아이콘 | 확인" },
        { MB_ICONQUESTION,      "물음표 아이콘 | 확인" },
        { MB_ICONERROR,         "오류 아이콘 | 확인" },   // MB_ICONSTOP, MB_ICONERROR 동일
        { MB_ICONWARNING,       "경고 아이콘 | 확인" },   // MB_ICONEXCLAMATION 동일
        { MB_ICONINFORMATION,   "느낌표 아이콘 | 확인" }, // MB_ICONASTERISK 동일
        { MB_TOPMOST,           "최상위로 위치(다른 윈도우 가려지지 않음) | 확인" },
        { MB_RIGHT,             "오른쪽 정렬 | 확인" },
        { MB_RTLREADING,        "오른쪽에서 왼쪽 정렬(기본 스타일의 반대) | 확인" } // RTL => Right To Left
	};

	for (INT32 i = 0; i < _countof(messageBoxStyleInfoTable); ++i)
	{
		CHAR strStyleValue[256] = "";
		snprintf(strStyleValue, 256, "스타일값 : %x\n", messageBoxStyleInfoTable[i].styleValue);

		CHAR strStyleGuide[256] = "";
		snprintf(strStyleGuide, 256, "스타일 안내 : %s\n", messageBoxStyleInfoTable[i].strStyleGuide);

		CHAR strStyleContent[256] = "";
		strncat_s(strStyleContent, strStyleValue, 256);
		strncat_s(strStyleContent, strStyleGuide, 256);
		OutputDebugString(strStyleContent); // 비주얼 스튜디오 출력창에 문자열을 출력해줍니다.
		MessageBox(nullptr, strStyleContent, "메시지 박스 캡션", messageBoxStyleInfoTable[i].styleValue);
	}

	return 0;
}