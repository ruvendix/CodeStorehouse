/*
 * <���� ����>
 * ������ ������ Ȯ���غ��� �����Դϴ�.
 * ������ ������ ���� �� �ϳ��ε� ���� ����� �� ���Ϳ� ���� ������ �ֱ� ������
 * �����̶�� �θ��ϴ�. ���⼭ ���ϴ� ���� ������ ���� �����̶�� �մϴ�.
 * �����п����� ������ �� ���Ͱ� �̷�� ���� ������ �ΰ�,
 * ����п����� ������ �� ������ ���г����� ���� ������ �Ӵϴ�.
 * �� �� �˾Ƶδ� �� �����ϴ�.
 */

// double���� float���� ��ҵǴ� �� ���
#pragma warning(disable : 4305)

#include <conio.h>   // CMD ������� �ٷ�� ���� ���(��ǥ��)
#include <windows.h> // CMD Ȯ�� ����� �̿��ϱ� ���� ���(��ǥ��)
#include <cstdio>    // CMD ������� �ٷ�� ���� ���(ǥ��)
#include <cmath>     // ������ �ٷ�� ���� ���(ǥ��)
#include <cfloat>    // �Ǽ��� �ٷ�� ���� ���(ǥ��)

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

	Vector2D& Normalize()
	{
		float rLength = CalcLength();

		// ������ ���̸�ŭ ��ǥ�� �����ָ� �˴ϴ�.
		// ������ ���� : 1 = (x, y) : (unitX, unitY)
		// ��ʽĿ� ���� {(unitX, unitY) = (x, y) / ������ ����}�� �˴ϴ�.
		x /= rLength;
		y /= rLength;

		return *this;
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

	float DotProduct(const Vector2D& vPos)
	{
		float rResult = 0.0f;
		
		// ù ��° ���г����� �����Դϴ�.
		rResult += x * vPos.x;

		// �� ��° ���г����� �����Դϴ�.
		rResult += y * vPos.y;

		return rResult;
	}

	void setPos(float rX, float rY)
	{
		x = rX;
		y = rY;
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

	Vector2D operator* (float rScalar)
	{
		Vector2D vResult;
		vResult.x = x * rScalar;
		vResult.y = y * rScalar;
		return vResult;
	}

	Vector2D& operator*= (float rScalar)
	{
		*this = *this * rScalar;
		return *this;
	}
};

int main()
{
	Vector2D vFirstPos  = { 5, 4 };
	Vector2D vSecondPos = { 12, 8 };

	float rResult = vFirstPos.DotProduct(vSecondPos);
	printf("�� ������ �������� %.2f�Դϴ�.\n", rResult);
	if (rResult <= FLT_EPSILON)
	{
		printf("�� ������ ���̰��� 90���Դϴ�.\n");
	}

	printf("\n");
	vFirstPos.setPos(2, 3);
	vSecondPos.setPos(-3, 2);

	rResult = vFirstPos.DotProduct(vSecondPos);
	printf("�� ������ �������� %.2f�Դϴ�.\n", rResult);
	if (rResult <= FLT_EPSILON)
	{
		printf("�� ������ ���̰��� 90���Դϴ�.\n");
	}

	_getch();
	return 0;
}