/*
 * <파일 설명>
 * 벡터의 정규화를 확인해보는 예제입니다.
 * 기하학에서 크기와 방향이 같은 벡터는 전부 다 같은 벡터로 취급합니다.
 * 하지만 대수학에서는 좌표가 일치해야 같은 벡터로 취급합니다.
 * 이런 차이가 있기 때문에 이론과는 어긋나는 부분이 있습니다.
 * 그런데 그 부분을 보완해주는 개념이 있습니다. 바로 정규화입니다.
 * 정규화를 이용하면 기하학과 대수학을 서로 연결시켜서 생각할 수 있습니다.
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
	Vector2D vPlayerPos  = { 14.0f, 8.0f };

	// 플레이어의 좌표와 벡터 길이를 알아봅니다.
	printf("<<플레이어의 좌표와 벡터 길이>>\n");
	printf("정규화하기 전의 vPlayerPos 좌표 : (%.2f, %.2f)\n", vPlayerPos.x, vPlayerPos.y);
	printf("정규화하기 전의 vPlayerPos 길이 : %.2f\n", vPlayerPos.CalcLength());

	// 단위 벡터가 되었을 때의 플레이어 좌표를 구합니다.
	// 단위 벡터는 길이가 1이므로 길이는 따로 구하지 않습니다.
	vPlayerPos.Normalize();
	printf("정규화한 후의 vPlayerPos 좌표   : (%.2f, %.2f)\n\n", vPlayerPos.x, vPlayerPos.y);

	//////////////////////////////////////////////////////////////////////////

	// 이번에는 플레이어가 몬스터를 바라보는 방향을 구해서
	// 몬스터 쪽으로 이동되는 걸 구현해볼 거예요.
	// 일단은 플레이어의 좌표부터 복구시켜야겠군요.
	vPlayerPos.setPos(14.0f, 8.0f);
	Vector2D vMonsterPos = { 50.0f, 60.0f };

	// 몬스터 위치 - 플레이어 위치 => 몬스터와 플레이어의 거리
	// 기하학의 의미로는 (플레이어가 몬스터를 바라보는 방향)
	// 위에 있는 내용이 궁금하면 벡터의 뺄셈을 참고하세요.
	Vector2D vDir = vMonsterPos - vPlayerPos;

	// 몬스터와 플레이어의 거리를 1로 만들어줍니다.
	// 그래야 대수학의 좌표 종속을 벗어날 수 있습니다.
	// 방향 정보만 있으면 어디든 적용할 수 있습니다.
	vDir.Normalize();

	// 이동량을 구해서 플레이어 위치에 적용합니다.
	printf("<<플레이어의 실시간 좌표 변화>>\n");
	for (int i = 0; i < 4; ++i)
	{
		vPlayerPos += vDir * 2.0f;
		printf("%d번째 이동 후의 vPlayerPos 좌표 : (%.2f, %.2f)\n",
			i + 1, vPlayerPos.x, vPlayerPos.y);
	}

	_getch();
	return 0;
}