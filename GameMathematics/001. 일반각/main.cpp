/*
 * <파일 설명>
 * 일반각을 확인해보는 예제입니다.
 * 시초선은 고정이므로 생각하지 않고 동경만 생각합니다.
 * 동경에 따라 양각과 음각이 어떻게 표현되는지 잘 보세요.
 * 수학에서는 360도 이상도 생각하지만 프로그래밍에서는 오차가 발생할 수 있으므로
 * 각도는 0 <= Α < 360 까지만 생각합니다. 즉, 각도 범위가 제한되어있습니다.
 */

#include <conio.h>   // CMD 입출력을 다루기 위한 헤더(비표준)
#include <windows.h> // CMD 확장 기능을 이용하기 위한 헤더
#include <cstdio>    // CMD 입출력을 다루기 위한 헤더(표준)
    
int main()
{
	printf("\n");

	int angle = 0; // 시작 각도는 0, 시초선을 0으로 생각
	int turn  = 0; // 시작 바퀴는 0

	bool bStop = false;
	while (bStop == false)
	{
		printf("현재 각도 : %03d도\n", angle);
		printf("현재 바퀴 : %03d바퀴\n", turn);
		++angle;

		// 각도가 360도 이상이면 0도로 초기화합니다.
		// 각도가 360도 이상이면 한바퀴 돌았다는 의미입니다.
		if (angle >= 360)
		{
			angle -= 360;
			++turn;
		}

		// 각도의 사분면을 판단합니다.
		// 수학에서는 (360 * turn) + 0 < angle < (360 * turn) + 90 이렇게 표현합니다.
		if ( (0 < angle) &&
			 (angle < 90) ) // 1사분면
		{
			printf("현재 1사분면입니다.\n");
		}
		else if ( (90 < angle) &&
			      (angle < 180) ) // 2사분면
		{
			printf("현재 2사분면입니다.\n");
		}
		else if ( (180 < angle) &&
			      (angle < 270)) // 3사분면
		{
			printf("현재 3사분면입니다.\n");
		}
		else if ( (270 < angle) &&
			      (angle < 360)) // 4사분면
		{
			printf("현재 4사분면입니다.\n");
		}
		
		// CMD 출력 위치를 초기화합니다.
		COORD initPos = { 0, 1 };
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), initPos);

		// q나 Q를 누르기 전까지 반복합니다.
		if (_kbhit())
		{
			char ch = _getch();
			if (tolower(ch) == 'q')
			{
				bStop = true;
			}
		}

		Sleep(50); // 0.05초마다 정지
	}

	_getch();
	return 0;
}