/*
 * <파일 설명>
 * 벡터의 정의를 확인해보는 예제입니다.
 * 벡터는 기하학적인 의미와 대수적인 의미가 있는데
 * 프로그래밍에서는 대수적인 의미만 생각합니다.
 * 그래도 기하학적인 의미를 알아두면 좋은 점이 많아요.
 */

// double에서 float으로 축소되는 것 허용
#pragma warning(disable : 4305)

#include <conio.h>   // CMD 입출력을 다루기 위한 헤더(비표준)
#include <windows.h> // CMD 확장 기능을 이용하기 위한 헤더(비표준)
#include <cstdio>    // CMD 입출력을 다루기 위한 헤더(표준)
#include <cmath>     // 수학을 다루기 위한 헤더(표준)

// 벡터 클래스
struct Vector2D
{
	float x; // 벡터의 첫 번째 성분
	float y; // 벡터의 두 번째 성분
};

float CalcVector2DLength(const Vector2D& vPos)
{
	// 피타고라스 정리에 의해 밑변과 높이의 제곱은 빗변의 제곱이 됩니다.
	return sqrtf((vPos.x * vPos.x) + (vPos.y * vPos.y));
}

int main()
{
	Vector2D vZero = { 0.0f, 0.0f }; // 제로 벡터, 영벡터
	printf("벡터의 좌표 (%.2f, %.2f)\n", vZero.x, vZero.y);
	printf("벡터의 길이 : %.2f\n\n", CalcVector2DLength(vZero));

	// sqrtf()는 루트를 씌워주는 함수입니다.
	Vector2D vUnit = { 1.0f / sqrtf(2.0f), 1.0f / sqrtf(2.0f) }; // 유닛 벡터, 단위 벡터
	printf("벡터의 좌표 (%.2f, %.2f)\n", vUnit.x, vUnit.y);
	printf("벡터의 길이 : %.2f\n\n", CalcVector2DLength(vUnit));

	Vector2D vPos = { 3.0f, 4.0f };
	printf("벡터의 좌표 (%.2f, %.2f)\n", vPos.x, vPos.y);
	printf("벡터의 길이 : %.2f\n", CalcVector2DLength(vPos));

	_getch();
	return 0;
}