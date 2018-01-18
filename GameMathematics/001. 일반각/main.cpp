/*
 * <���� ����>
 * �Ϲݰ��� Ȯ���غ��� �����Դϴ�.
 * ���ʼ��� �����̹Ƿ� �������� �ʰ� ���游 �����մϴ�.
 * ���濡 ���� �簢�� ������ ��� ǥ���Ǵ��� �� ������.
 * ���п����� 360�� �̻� ���������� ���α׷��ֿ����� ������ �߻��� �� �����Ƿ�
 * ������ 0 <= �� < 360 ������ �����մϴ�. ��, ���� ������ ���ѵǾ��ֽ��ϴ�.
 */

#include <conio.h>   // CMD ������� �ٷ�� ���� ���(��ǥ��)
#include <windows.h> // CMD Ȯ�� ����� �̿��ϱ� ���� ���
#include <cstdio>    // CMD ������� �ٷ�� ���� ���(ǥ��)
    
int main()
{
	printf("\n");

	int angle = 0; // ���� ������ 0, ���ʼ��� 0���� ����
	int turn  = 0; // ���� ������ 0

	bool bStop = false;
	while (bStop == false)
	{
		printf("���� ���� : %03d��\n", angle);
		printf("���� ���� : %03d����\n", turn);
		++angle;

		// ������ 360�� �̻��̸� 0���� �ʱ�ȭ�մϴ�.
		// ������ 360�� �̻��̸� �ѹ��� ���Ҵٴ� �ǹ��Դϴ�.
		if (angle >= 360)
		{
			angle -= 360;
			++turn;
		}

		// ������ ��и��� �Ǵ��մϴ�.
		// ���п����� (360 * turn) + 0 < angle < (360 * turn) + 90 �̷��� ǥ���մϴ�.
		if ( (0 < angle) &&
			 (angle < 90) ) // 1��и�
		{
			printf("���� 1��и��Դϴ�.\n");
		}
		else if ( (90 < angle) &&
			      (angle < 180) ) // 2��и�
		{
			printf("���� 2��и��Դϴ�.\n");
		}
		else if ( (180 < angle) &&
			      (angle < 270)) // 3��и�
		{
			printf("���� 3��и��Դϴ�.\n");
		}
		else if ( (270 < angle) &&
			      (angle < 360)) // 4��и�
		{
			printf("���� 4��и��Դϴ�.\n");
		}
		
		// CMD ��� ��ġ�� �ʱ�ȭ�մϴ�.
		COORD initPos = { 0, 1 };
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), initPos);

		// q�� Q�� ������ ������ �ݺ��մϴ�.
		if (_kbhit())
		{
			char ch = _getch();
			if (tolower(ch) == 'q')
			{
				bStop = true;
			}
		}

		Sleep(50); // 0.05�ʸ��� ����
	}

	_getch();
	return 0;
}