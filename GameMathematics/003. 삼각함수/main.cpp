/*
 * <파일 설명>
 * 삼각함수를 확인해보는 예제입니다.
 * 삼각함수는 호도법을 이용하므로 일반각을 호도법으로 변환할 줄 알아야 합니다.
 * 삼각함수는 sin, cos, tan 이렇게 3개만 알아보겠습니다.
 */

// double에서 float으로 축소되는 것 허용
#pragma warning(disable : 4305)

#include <conio.h>   // CMD 입출력을 다루기 위한 헤더(비표준)
#include <windows.h> // CMD 확장 기능을 이용하기 위한 헤더(비표준)
#include <cstdio>    // CMD 입출력을 다루기 위한 헤더(표준)

#define _USE_MATH_DEFINES // 수학의 정의값을 사용하기 위한 매크로 상수
#include <cmath>          // 수학을 다루기 위한 헤더(표준)

void MoveConsoleCursorPosition(int x, int y)
{
	COORD curPos = { static_cast<short>(x), static_cast<short>(y) };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), curPos);
}

int main()
{
	// sin
	for (int i = 0; i < 360; ++i)
	{
		printf("sin%03d : %+5.4f\n", i, sin(i * (M_PI / 180.0f)));
		Sleep(100);
		MoveConsoleCursorPosition(0, 0);
	}

	// cos
	printf("\n");
	for (int i = 0; i < 360; ++i)
	{
		printf("cos%03d : %+5.4f\n", i, cos(i * (M_PI / 180.0f)));
		Sleep(100);
		MoveConsoleCursorPosition(0, 1);
	}

	// tan
	printf("\n");
	for (int i = 0; i < 360; ++i)
	{
		// 탄젠트는 (πn / 2)마다 값이 존재하지 않습니다.
		if ( (i == 90) ||
			 (i == 180) ||
			 (i == 270) )
		{
			continue;
		}

		printf("tan%03d : %+5.4f\n", i, tan(i * (M_PI / 180.0f)));
		Sleep(100);
		MoveConsoleCursorPosition(0, 2);
	}

	_getch();
	return 0;
}