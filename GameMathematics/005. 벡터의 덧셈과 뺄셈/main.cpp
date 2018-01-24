/*
 * <���� ����>
 * ������ ������ ������ Ȯ���غ��� �����Դϴ�.
 * ���������� �ǹ̿� ��������� �ǹ� �� �� �˰� ������ ���ƿ�.
 * ���α׷��ֿ����� ��������� �ǹ̸� �����ϴµ� Ư��, ������ �߿��մϴ�.
 * ������ ������ ���������� ������ �����ϱⰡ ���� ���� �ſ���.
 */

// double���� float���� ��ҵǴ� �� ���
#pragma warning(disable : 4305)

#include <conio.h>   // CMD ������� �ٷ�� ���� ���(��ǥ��)
#include <windows.h> // CMD Ȯ�� ����� �̿��ϱ� ���� ���(��ǥ��)
#include <cstdio>    // CMD ������� �ٷ�� ���� ���(ǥ��)
#include <cmath>     // ������ �ٷ�� ���� ���(ǥ��)

// ���� ����ü
struct VectorBase2D
{
	float x; // ������ ù ��° ����
	float y; // ������ �� ��° ����
};

// ���� Ŭ����
// ��������� ���� ������ ����մϴ�.
class Vector2D : public VectorBase2D
{
public:
	Vector2D()
	{
		// ������
		x = 0.0f;
		y = 0.0f;
	}

	Vector2D(float rX, float rY)
	{
		// �Ϲ� ����
		x = rX;
		y = rY;
	}
	
	~Vector2D() = default;

	float CalcLength()
	{
		// ��Ÿ��� ������ ���� �غ��� ������ ������ ������ ������ �˴ϴ�.
		return sqrtf(powf(x, 2) + powf(y, 2));
	}

	Vector2D& Add(const Vector2D& vPos)
	{
		x += vPos.x;
		y += vPos.y;
		return *this;
	}

	Vector2D& Subtarct(const Vector2D& vPos)
	{
		x -= vPos.x;
		y -= vPos.y;
		return *this;
	}

	// ������ �����ε��� �����մϴ�.
	Vector2D operator+ (const Vector2D& rhs)
	{
		Vector2D vResult;
		vResult.x = x + rhs.x;
		vResult.y = y + rhs.y;
		return vResult;
	}

	Vector2D& operator+= (const Vector2D& rhs)
	{
		*this = *this + rhs;
		return *this;
	}

	Vector2D operator- (const Vector2D& rhs)
	{
		Vector2D vResult;
		vResult.x = x - rhs.x;
		vResult.y = y - rhs.y;
		return vResult;
	}

	Vector2D& operator-= (const Vector2D& rhs)
	{
		*this = *this - rhs;
		return *this;
	}
};

int main()
{
	Vector2D vFirstPos  = { 1.0f, 4.0f };
	Vector2D vSecondPos = { 3.0f, 2.0f };

	// �� ���͸� ���մϴ�.
	// ���⼭�� vFirstPos�� ��ġ�� ���մϴ�.
	// �׸�ŭ �̵��ߴٰ� �����ϸ� �˴ϴ�.
	printf("<<������ ����>>\n");
	printf("�̵��ϱ� ���� vFirstPos ��ǥ : (%.2f, %.2f)\n", vFirstPos.x, vFirstPos.y);
	printf("�̵��ϱ� ���� vFirstPos ���� : %.2f\n\n", vFirstPos.CalcLength());

	vFirstPos.Add(vSecondPos);
	//vFirstPos += vSecondPos; // Add()�� �����ϴ�.
	printf("�̵��� ���� vFirstPos ��ǥ   : (%.2f, %.2f)\n", vFirstPos.x, vFirstPos.y);
	printf("�̵��� ���� vFirstPos ����   : %.2f\n\n", vFirstPos.CalcLength());

	// �� ���͸� ���ϴ�.
	// ���⼭�� vFirstPos�� ��ġ�� ���մϴ�.
	// �׸�ŭ ���������� �̵��ߴٰ� �����ϸ� �˴ϴ�.
	printf("<<������ ����>>\n");
	printf("�̵��ϱ� ���� vFirstPos ��ǥ : (%.2f, %.2f)\n", vFirstPos.x, vFirstPos.y);
	printf("�̵��ϱ� ���� vFirstPos ���� : %.2f\n\n", vFirstPos.CalcLength());

	vFirstPos.Subtarct(vSecondPos);
	//vFirstPos -= vSecondPos; // Subtarct()�� �����ϴ�.
	printf("�̵��� ���� vFirstPos ��ǥ   : (%.2f, %.2f)\n", vFirstPos.x, vFirstPos.y);
	printf("�̵��� ���� vFirstPos ����   : %.2f\n", vFirstPos.CalcLength());

	_getch();
	return 0;
}