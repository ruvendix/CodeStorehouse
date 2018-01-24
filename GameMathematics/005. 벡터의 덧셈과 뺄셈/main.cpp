/*
 * <파일 설명>
 * 벡터의 덧셈과 뺄셈을 확인해보는 예제입니다.
 * 기하학적인 의미와 대수학적인 의미 둘 다 알고 있으면 좋아요.
 * 프로그래밍에서는 대수학적인 의미만 생각하는데 특히, 뺄셈이 중요합니다.
 * 벡터의 덧셈은 간단하지만 뺄셈은 이해하기가 쉽지 않을 거예요.
 */

// double에서 float으로 축소되는 것 허용
#pragma warning(disable : 4305)

#include <conio.h>   // CMD 입출력을 다루기 위한 헤더(비표준)
#include <windows.h> // CMD 확장 기능을 이용하기 위한 헤더(비표준)
#include <cstdio>    // CMD 입출력을 다루기 위한 헤더(표준)
#include <cmath>     // 수학을 다루기 위한 헤더(표준)

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
};

int main()
{
	Vector2D vFirstPos  = { 1.0f, 4.0f };
	Vector2D vSecondPos = { 3.0f, 2.0f };

	// 두 벡터를 더합니다.
	// 여기서는 vFirstPos의 위치가 변합니다.
	// 그만큼 이동했다고 생각하면 됩니다.
	printf("<<벡터의 덧셈>>\n");
	printf("이동하기 전의 vFirstPos 좌표 : (%.2f, %.2f)\n", vFirstPos.x, vFirstPos.y);
	printf("이동하기 전의 vFirstPos 길이 : %.2f\n\n", vFirstPos.CalcLength());

	vFirstPos.Add(vSecondPos);
	//vFirstPos += vSecondPos; // Add()와 같습니다.
	printf("이동한 후의 vFirstPos 좌표   : (%.2f, %.2f)\n", vFirstPos.x, vFirstPos.y);
	printf("이동한 후의 vFirstPos 길이   : %.2f\n\n", vFirstPos.CalcLength());

	// 두 벡터를 뺍니다.
	// 여기서는 vFirstPos의 위치가 변합니다.
	// 그만큼 역방향으로 이동했다고 생각하면 됩니다.
	printf("<<벡터의 뺄셈>>\n");
	printf("이동하기 전의 vFirstPos 좌표 : (%.2f, %.2f)\n", vFirstPos.x, vFirstPos.y);
	printf("이동하기 전의 vFirstPos 길이 : %.2f\n\n", vFirstPos.CalcLength());

	vFirstPos.Subtarct(vSecondPos);
	//vFirstPos -= vSecondPos; // Subtarct()와 같습니다.
	printf("이동한 후의 vFirstPos 좌표   : (%.2f, %.2f)\n", vFirstPos.x, vFirstPos.y);
	printf("이동한 후의 vFirstPos 길이   : %.2f\n", vFirstPos.CalcLength());

	_getch();
	return 0;
}