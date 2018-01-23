/*
 * <���� ����>
 * ������ ���Ǹ� Ȯ���غ��� �����Դϴ�.
 * ���ʹ� ���������� �ǹ̿� ������� �ǹ̰� �ִµ�
 * ���α׷��ֿ����� ������� �ǹ̸� �����մϴ�.
 * �׷��� ���������� �ǹ̸� �˾Ƶθ� ���� ���� ���ƿ�.
 */

// double���� float���� ��ҵǴ� �� ���
#pragma warning(disable : 4305)

#include <conio.h>   // CMD ������� �ٷ�� ���� ���(��ǥ��)
#include <windows.h> // CMD Ȯ�� ����� �̿��ϱ� ���� ���(��ǥ��)
#include <cstdio>    // CMD ������� �ٷ�� ���� ���(ǥ��)
#include <cmath>     // ������ �ٷ�� ���� ���(ǥ��)

// ���� Ŭ����
struct Vector2D
{
	float x; // ������ ù ��° ����
	float y; // ������ �� ��° ����
};

float CalcVector2DLength(const Vector2D& vPos)
{
	// ��Ÿ��� ������ ���� �غ��� ������ ������ ������ ������ �˴ϴ�.
	return sqrtf((vPos.x * vPos.x) + (vPos.y * vPos.y));
}

int main()
{
	Vector2D vZero = { 0.0f, 0.0f }; // ���� ����, ������
	printf("������ ��ǥ (%.2f, %.2f)\n", vZero.x, vZero.y);
	printf("������ ���� : %.2f\n\n", CalcVector2DLength(vZero));

	// sqrtf()�� ��Ʈ�� �����ִ� �Լ��Դϴ�.
	Vector2D vUnit = { 1.0f / sqrtf(2.0f), 1.0f / sqrtf(2.0f) }; // ���� ����, ���� ����
	printf("������ ��ǥ (%.2f, %.2f)\n", vUnit.x, vUnit.y);
	printf("������ ���� : %.2f\n\n", CalcVector2DLength(vUnit));

	Vector2D vPos = { 3.0f, 4.0f };
	printf("������ ��ǥ (%.2f, %.2f)\n", vPos.x, vPos.y);
	printf("������ ���� : %.2f\n", CalcVector2DLength(vPos));

	_getch();
	return 0;
}