/*
 * <���� ����>
 * �ﰢ�Լ��� Ȯ���غ��� �����Դϴ�.
 * �ﰢ�Լ��� ȣ������ �̿��ϹǷ� �Ϲݰ��� ȣ�������� ��ȯ�� �� �˾ƾ� �մϴ�.
 * �ﰢ�Լ��� sin, cos, tan �̷��� 3���� �˾ƺ��ڽ��ϴ�.
 */

// double���� float���� ��ҵǴ� �� ���
#pragma warning(disable : 4305)

#include <conio.h>   // CMD ������� �ٷ�� ���� ���(��ǥ��)
#include <windows.h> // CMD Ȯ�� ����� �̿��ϱ� ���� ���(��ǥ��)
#include <cstdio>    // CMD ������� �ٷ�� ���� ���(ǥ��)

#define _USE_MATH_DEFINES // ������ ���ǰ��� ����ϱ� ���� ��ũ�� ���
#include <cmath>          // ������ �ٷ�� ���� ���(ǥ��)

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
		// ź��Ʈ�� (��n / 2)���� ���� �������� �ʽ��ϴ�.
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