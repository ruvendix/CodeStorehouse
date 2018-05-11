/*
 * <���� ����>
 * ������ ������ Ȯ���غ��� �����Դϴ�.
 * ������ ������ ���� �� �ϳ��ε� ���� ����� �� ���Ϳ� �ٸ� ������ �ֱ� ������
 * �����̶�� �θ��ϴ�. ���⼭ ���ϴ� ���� ������ ���� �����̶�� �մϴ�.
 * �����п����� ������ �� ���� ��ο��� ������ ���͸� �ǹ��ϰ�,
 * ����п����� ������ �� ������ ��ǥ�� Ư�� ������� ���� �Ϳ� ������ �Ӵϴ�.
 * �� �� �˾Ƶδ� �� �����ϴ�.
 */

// double���� float���� ��ҵǴ� �� ���
#pragma warning(disable : 4305)

#include <conio.h>   // CMD ������� �ٷ�� ���� ���(��ǥ��)
#include <windows.h> // CMD Ȯ�� ����� �̿��ϱ� ���� ���(��ǥ��)
#include <cstdio>    // CMD ������� �ٷ�� ���� ���(ǥ��)
#include <cmath>     // ������ �ٷ�� ���� ���(ǥ��)
#include <cfloat>    // �Ǽ��� �ٷ�� ���� ���(ǥ��)

// ���� Ŭ����
// ���� ������ 3�������� ����ø��ϴ�.
class Vector3D
{
public:
	Vector3D()
	{
		// ������
		m_rX = 0.0f;
		m_rY = 0.0f;
		m_rZ = 0.0f;
	}

	Vector3D(float rX, float rY, float rZ)
	{
		// �Ϲ� ����
		m_rX = rX;
		m_rY = rY;
		m_rZ = rZ;
	}

	~Vector3D() = default;

	float CalcLength()
	{
		// ��Ÿ��� ������ ���� �غ��� ������ ������ ������ ������ �˴ϴ�.
		return std::sqrt(std::pow(m_rX, 2) + std::pow(m_rY, 2) + std::pow(m_rZ, 2));
	}

	Vector3D& Normalize()
	{
		float rLength = CalcLength();

		// ������ ���̸�ŭ ��ǥ�� �����ָ� �˴ϴ�.
		// ������ ���� : 1 = (x, y, z) : (unitX, unitY, unitZ)
		// ��ʽĿ� ���� {(unitX, unitY, unitZ) = (x, y, z) / ������ ����}�� �˴ϴ�.
		m_rX /= rLength;
		m_rY /= rLength;
		m_rZ /= rLength;

		return *this;
	}

	Vector3D& Add(const Vector3D& vPos)
	{
		m_rX += vPos.m_rX;
		m_rY += vPos.m_rY;
		m_rZ += vPos.m_rZ;
		return *this;
	}

	Vector3D& Subtarct(const Vector3D& vPos)
	{
		m_rX -= vPos.m_rX;
		m_rY -= vPos.m_rY;
		m_rZ -= vPos.m_rZ;
		return *this;
	}

	float DotProduct(const Vector3D& vPos)
	{
		float rResult = 0.0f;

		// ù ��° ���г����� �����Դϴ�.
		rResult += m_rX * vPos.m_rX;

		// �� ��° ���г����� �����Դϴ�.
		rResult += m_rY * vPos.m_rY;

		// �� ��° ���г����� �����Դϴ�.
		rResult += m_rZ * vPos.m_rZ;

		return rResult;
	}

	Vector3D CrossProduct(const Vector3D& vPos)
	{
		Vector3D vResult;

		// ���� ���� ���� ������ �����ϹǷ� ���� ������ �е��� �ѹ� ã�ƺ�����.
		// ������ �ܿ�Ⱑ ����ٸ� "��罺 ��Ģ"�� �˻��غ�����.
		vResult.m_rX = (m_rY * vPos.m_rZ) - (m_rZ * vPos.m_rY);
		vResult.m_rY = (m_rZ * vPos.m_rX) - (m_rX * vPos.m_rZ);
		vResult.m_rZ = (m_rX * vPos.m_rY) - (m_rY * vPos.m_rX);

		return vResult;
	}

	/////////////////////////////////////////////////////////////////
	// Getter
	float getX() const noexcept
	{
		return m_rX;
	}

	float getY() const noexcept
	{
		return m_rY;
	}

	float getZ() const noexcept
	{
		return m_rZ;
	}

	/////////////////////////////////////////////////////////////////
	// Setter
	void setPos(float rX, float rY, float rZ)
	{
		m_rX = rX;
		m_rY = rY;
		m_rZ = rZ;
	}

	// ������ �����ε��� �����մϴ�.
	Vector3D operator+ (const Vector3D& rhs)
	{
		Vector3D vResult;
		vResult.m_rX = m_rX + rhs.m_rX;
		vResult.m_rY = m_rY + rhs.m_rY;
		vResult.m_rZ = m_rZ + rhs.m_rZ;
		return vResult;
	}

	Vector3D& operator+= (const Vector3D& rhs)
	{
		*this = *this + rhs;
		return *this;
	}

	Vector3D operator- (const Vector3D& rhs)
	{
		Vector3D vResult;
		vResult.m_rX = m_rX - rhs.m_rX;
		vResult.m_rY = m_rY - rhs.m_rY;
		vResult.m_rZ = m_rZ - rhs.m_rZ;
		return vResult;
	}

	Vector3D& operator-= (const Vector3D& rhs)
	{
		*this = *this - rhs;
		return *this;
	}

	Vector3D operator* (float rScalar)
	{
		Vector3D vResult;
		vResult.m_rX = m_rX * rScalar;
		vResult.m_rY = m_rY * rScalar;
		vResult.m_rZ = m_rZ * rScalar;
		return vResult;
	}

	Vector3D& operator*= (float rScalar)
	{
		*this = *this * rScalar;
		return *this;
	}

private:
	float m_rX;
	float m_rY;
	float m_rZ;
};

int main()
{
	Vector3D vFirstPos  = { 1.0f, -7.0f, 1.0f };
	Vector3D vSecondPos = { 5.0f,  2.0f, 4.0f };
	
	// (vFirstPos X vSecondPos)�� �����ϴ�.
	// ��, vFirstPos -> vSecondPos�� �հ����� ������ ��
	// ���� �հ����� ������ ����� ������.
	Vector3D rCross = vFirstPos.CrossProduct(vSecondPos);
	printf("vFirstPos(%.2f, %.2f, %.2f)\tvSecondPos(%.2f, %.2f, %.2f)\n",
		vFirstPos.getX(), vFirstPos.getY(), vFirstPos.getZ(),
		vSecondPos.getX(), vSecondPos.getY(), vSecondPos.getZ());
	printf("vFirstPos X vSecondPos = (%.2f, %.2f, %.2f)\n",
		rCross.getX(), rCross.getY(), rCross.getZ());

	_getch();
	return 0;
}