/*
 * <파일 설명>
 * 벡터의 내적을 확인해보는 예제입니다.
 * 내적은 벡터의 곱셈 중 하나인데 연산 결과가 두 벡터와 같은 공간에 있기 때문에
 * 내적이라고 부릅니다. 여기서 말하는 벡터 공간은 내적 공간이라고도 합니다.
 * 기하학에서의 내적은 두 벡터가 이루는 각에 중점을 두고,
 * 대수학에서의 내적은 두 벡터의 성분끼리의 곱에 중점을 둡니다.
 * 둘 다 알아두는 게 좋습니다.
 */

// double에서 float으로 축소되는 것 허용
#pragma warning(disable : 4305)

#include <conio.h>   // CMD 입출력을 다루기 위한 헤더(비표준)
#include <windows.h> // CMD 확장 기능을 이용하기 위한 헤더(비표준)
#include <cstdio>    // CMD 입출력을 다루기 위한 헤더(표준)
#include <cmath>     // 수학을 다루기 위한 헤더(표준)
#include <cfloat>    // 실수를 다루기 위한 헤더(표준)

// 벡터 구조체
struct VectorBase2D
{
	float x; // 벡터의 첫 번째 성분
	float y; // 벡터의 두 번째 성분
};

// 벡터 클래스
// 멤버변수는 자유 접근을 허용합니다.
class Vector2D : public VectorBase2D
{
public:
	Vector2D()
	{
		// 영벡터
		x = 0.0f;
		y = 0.0f;
	}

	Vector2D(float rX, float rY)
	{
		// 일반 벡터
		x = rX;
		y = rY;
	}

	~Vector2D() = default;

	float CalcLength()
	{
		// 피타고라스 정리에 의해 밑변과 높이의 제곱은 빗변의 제곱이 됩니다.
		return sqrtf(powf(x, 2) + powf(y, 2));
	}

	Vector2D& Normalize()
	{
		float rLength = CalcLength();

		// 벡터의 길이만큼 좌표를 나눠주면 됩니다.
		// 벡터의 길이 : 1 = (x, y) : (unitX, unitY)
		// 비례식에 의해 {(unitX, unitY) = (x, y) / 벡터의 길이}가 됩니다.
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
		
		// 첫 번째 성분끼리의 곱셈입니다.
		rResult += x * vPos.x;

		// 두 번째 성분끼리의 곱셈입니다.
		rResult += y * vPos.y;

		return rResult;
	}

	void setPos(float rX, float rY)
	{
		x = rX;
		y = rY;
	}

	// 연산자 오버로딩도 지원합니다.
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
	printf("두 벡터의 내적값은 %.2f입니다.\n", rResult);
	if (rResult <= FLT_EPSILON)
	{
		printf("두 벡터의 사이각은 90도입니다.\n");
	}

	printf("\n");
	vFirstPos.setPos(2, 3);
	vSecondPos.setPos(-3, 2);

	rResult = vFirstPos.DotProduct(vSecondPos);
	printf("두 벡터의 내적값은 %.2f입니다.\n", rResult);
	if (rResult <= FLT_EPSILON)
	{
		printf("두 벡터의 사이각은 90도입니다.\n");
	}

	_getch();
	return 0;
}