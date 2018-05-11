/*
 * <파일 설명>
 * 벡터의 외적을 확인해보는 예제입니다.
 * 외적은 벡터의 곱셈 중 하나인데 연산 결과가 두 벡터와 다른 공간에 있기 때문에
 * 외적이라고 부릅니다. 여기서 말하는 벡터 공간은 외적 공간이라고도 합니다.
 * 기하학에서의 외적은 두 벡터 모두에게 수직인 벡터를 의미하고,
 * 대수학에서의 외적은 두 벡터의 좌표를 특정 방법으로 곱한 것에 중점을 둡니다.
 * 둘 다 알아두는 게 좋습니다.
 */

// double에서 float으로 축소되는 것 허용
#pragma warning(disable : 4305)

#include <conio.h>   // CMD 입출력을 다루기 위한 헤더(비표준)
#include <windows.h> // CMD 확장 기능을 이용하기 위한 헤더(비표준)
#include <cstdio>    // CMD 입출력을 다루기 위한 헤더(표준)
#include <cmath>     // 수학을 다루기 위한 헤더(표준)
#include <cfloat>    // 실수를 다루기 위한 헤더(표준)

// 벡터 클래스
// 외적 때문에 3차원으로 끌어올립니다.
class Vector3D
{
public:
	Vector3D()
	{
		// 영벡터
		m_rX = 0.0f;
		m_rY = 0.0f;
		m_rZ = 0.0f;
	}

	Vector3D(float rX, float rY, float rZ)
	{
		// 일반 벡터
		m_rX = rX;
		m_rY = rY;
		m_rZ = rZ;
	}

	~Vector3D() = default;

	float CalcLength()
	{
		// 피타고라스 정리에 의해 밑변과 높이의 제곱은 빗변의 제곱이 됩니다.
		return std::sqrt(std::pow(m_rX, 2) + std::pow(m_rY, 2) + std::pow(m_rZ, 2));
	}

	Vector3D& Normalize()
	{
		float rLength = CalcLength();

		// 벡터의 길이만큼 좌표를 나눠주면 됩니다.
		// 벡터의 길이 : 1 = (x, y, z) : (unitX, unitY, unitZ)
		// 비례식에 의해 {(unitX, unitY, unitZ) = (x, y, z) / 벡터의 길이}가 됩니다.
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

		// 첫 번째 성분끼리의 곱셈입니다.
		rResult += m_rX * vPos.m_rX;

		// 두 번째 성분끼리의 곱셈입니다.
		rResult += m_rY * vPos.m_rY;

		// 세 번째 성분끼리의 곱셈입니다.
		rResult += m_rZ * vPos.m_rZ;

		return rResult;
	}

	Vector3D CrossProduct(const Vector3D& vPos)
	{
		Vector3D vResult;

		// 외적 공식 유도 과정은 복잡하므로 관심 있으신 분들은 한번 찾아보세요.
		// 공식을 외우기가 힘들다면 "사루스 법칙"을 검색해보세요.
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

	// 연산자 오버로딩도 지원합니다.
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
	
	// (vFirstPos X vSecondPos)와 같습니다.
	// 즉, vFirstPos -> vSecondPos로 손가락을 감쌌을 때
	// 엄지 손가락이 외적의 결과인 셈이죠.
	Vector3D rCross = vFirstPos.CrossProduct(vSecondPos);
	printf("vFirstPos(%.2f, %.2f, %.2f)\tvSecondPos(%.2f, %.2f, %.2f)\n",
		vFirstPos.getX(), vFirstPos.getY(), vFirstPos.getZ(),
		vSecondPos.getX(), vSecondPos.getY(), vSecondPos.getZ());
	printf("vFirstPos X vSecondPos = (%.2f, %.2f, %.2f)\n",
		rCross.getX(), rCross.getY(), rCross.getZ());

	_getch();
	return 0;
}