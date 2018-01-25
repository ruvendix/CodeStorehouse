/*
 * <���� ����>
 * ������ ����ȭ�� Ȯ���غ��� �����Դϴ�.
 * �����п��� ũ��� ������ ���� ���ʹ� ���� �� ���� ���ͷ� ����մϴ�.
 * ������ ����п����� ��ǥ�� ��ġ�ؾ� ���� ���ͷ� ����մϴ�.
 * �̷� ���̰� �ֱ� ������ �̷а��� ��߳��� �κ��� �ֽ��ϴ�.
 * �׷��� �� �κ��� �������ִ� ������ �ֽ��ϴ�. �ٷ� ����ȭ�Դϴ�.
 * ����ȭ�� �̿��ϸ� �����а� ������� ���� ������Ѽ� ������ �� �ֽ��ϴ�.
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
	Vector2D vPlayerPos  = { 14.0f, 8.0f };

	// �÷��̾��� ��ǥ�� ���� ���̸� �˾ƺ��ϴ�.
	printf("<<�÷��̾��� ��ǥ�� ���� ����>>\n");
	printf("����ȭ�ϱ� ���� vPlayerPos ��ǥ : (%.2f, %.2f)\n", vPlayerPos.x, vPlayerPos.y);
	printf("����ȭ�ϱ� ���� vPlayerPos ���� : %.2f\n", vPlayerPos.CalcLength());

	// ���� ���Ͱ� �Ǿ��� ���� �÷��̾� ��ǥ�� ���մϴ�.
	// ���� ���ʹ� ���̰� 1�̹Ƿ� ���̴� ���� ������ �ʽ��ϴ�.
	vPlayerPos.Normalize();
	printf("����ȭ�� ���� vPlayerPos ��ǥ   : (%.2f, %.2f)\n\n", vPlayerPos.x, vPlayerPos.y);

	//////////////////////////////////////////////////////////////////////////

	// �̹����� �÷��̾ ���͸� �ٶ󺸴� ������ ���ؼ�
	// ���� ������ �̵��Ǵ� �� �����غ� �ſ���.
	// �ϴ��� �÷��̾��� ��ǥ���� �������Ѿ߰ڱ���.
	vPlayerPos.setPos(14.0f, 8.0f);
	Vector2D vMonsterPos = { 50.0f, 60.0f };

	// ���� ��ġ - �÷��̾� ��ġ => ���Ϳ� �÷��̾��� �Ÿ�
	// �������� �ǹ̷δ� (�÷��̾ ���͸� �ٶ󺸴� ����)
	// ���� �ִ� ������ �ñ��ϸ� ������ ������ �����ϼ���.
	Vector2D vDir = vMonsterPos - vPlayerPos;

	// ���Ϳ� �÷��̾��� �Ÿ��� 1�� ������ݴϴ�.
	// �׷��� ������� ��ǥ ������ ��� �� �ֽ��ϴ�.
	// ���� ������ ������ ���� ������ �� �ֽ��ϴ�.
	vDir.Normalize();

	// �̵����� ���ؼ� �÷��̾� ��ġ�� �����մϴ�.
	printf("<<�÷��̾��� �ǽð� ��ǥ ��ȭ>>\n");
	for (int i = 0; i < 4; ++i)
	{
		vPlayerPos += vDir * 2.0f;
		printf("%d��° �̵� ���� vPlayerPos ��ǥ : (%.2f, %.2f)\n",
			i + 1, vPlayerPos.x, vPlayerPos.y);
	}

	_getch();
	return 0;
}