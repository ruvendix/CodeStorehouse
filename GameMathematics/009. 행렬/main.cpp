/*
 * <파일 설명>
 * 행렬의 정의를 확인해보는 예제입니다.
 * 행렬은 고등학교 과정이 아니므로 자세하게 설명하려고 합니다.
 * 게임 프로그래밍에서 행렬은 필수 개념이므로 반드시 알아야 합니다.
 * 예전에는 행렬이 고등학교 과정이었는데 어느 순간에 대학교 과정으로 넘어갔더군요.
 * 그래서 설명이 불친절해졌는데... 덕분에 행렬에 접근하기가 어려워졌습니다.
 * 행렬을 아예 모른다고 가정을 한 상태에서 진행할게요.
 */

// double에서 float으로 축소되는 것 허용
#pragma warning(disable : 4305)

#include <conio.h>   // CMD 입출력을 다루기 위한 헤더(비표준)
#include <windows.h> // CMD 확장 기능을 이용하기 위한 헤더(비표준)
#include <cstdio>    // CMD 입출력을 다루기 위한 헤더(표준)
#include <cmath>     // 수학을 다루기 위한 헤더(표준)
#include <cfloat>    // 실수를 다루기 위한 헤더(표준)

// 행렬 클래스
class Matrix4X4
{
public:
	// 초기화는 0으로 설정합니다.
	// 이런 행렬을 영행렬(Zero Matrix)이라 부릅니다.
	Matrix4X4()
	{
		m_r00 = 0.0f; m_r01 = 0.0f; m_r02 = 0.0f; m_r03 = 0.0f;
		m_r10 = 0.0f; m_r11 = 0.0f; m_r12 = 0.0f; m_r13 = 0.0f;
		m_r20 = 0.0f; m_r21 = 0.0f; m_r22 = 0.0f; m_r23 = 0.0f;
		m_r30 = 0.0f; m_r31 = 0.0f; m_r32 = 0.0f; m_r33 = 0.0f;

		//// 위와 같은 겁니다.
		//for (int row = 0; row < 4; ++row)
		//{
		//	for (int col = 0; col < 4; ++col)
		//	{
		//		m_rElement[row][col] = 0.0f;
		//	}
		//}
	}

	~Matrix4X4() = default;

	void ShowElement()
	{
		printf("    1열   2열   3열   4열\n");
		printf("1행 %.2f  %.2f  %.2f  %.2f\n", m_r00, m_r01, m_r02, m_r03);
		printf("2행 %.2f  %.2f  %.2f  %.2f\n", m_r10, m_r11, m_r12, m_r13);
		printf("3행 %.2f  %.2f  %.2f  %.2f\n", m_r20, m_r21, m_r22, m_r23);
		printf("4행 %.2f  %.2f  %.2f  %.2f\n", m_r30, m_r31, m_r32, m_r33);

		// 위와 같은 겁니다.
		//for (int row = 0; row < 4; ++row)
		//{
		//	for (int col = 0; col < 4; ++col)
		//	{
		//		printf("(%d, %d = %.2f) ", row, col, m_rElement[row][col]);
		//	}
		//  printf("\n");
		//}
	}

	/////////////////////////////////////////////////////////////////
	// Getter
	float getElement(int row, int col)
	{
		return m_rElement[row][col];
	}

	/////////////////////////////////////////////////////////////////
	// Setter
	void setElement(int row, int col, float rVal)
	{
		m_rElement[row][col] = rVal;
	}

private:
	// 배열과 각 요소로 접근하는 방법을 제공하기 위해 공용체를 사용합니다.
	union
	{
		struct // 4 X 4 X 4 = 64바이트
		{
			float m_r00, m_r01, m_r02, m_r03;
			float m_r10, m_r11, m_r12, m_r13;
			float m_r20, m_r21, m_r22, m_r23;
			float m_r30, m_r31, m_r32, m_r33;
		};

		float m_rElement[4][4]; // 4 X 4 X 4 = 64바이트
	};
};

int main()
{
	printf("4행 4열의 행렬값을 출력합니다.\n");
	printf("----------------------------\n");

	Matrix4X4 mat; // 행렬은 약자로 mat이라 표현합니다.
	mat.ShowElement();

	printf("----------------------------\n\n");

	///////////////////////////////////////////////////////////////

	// 행렬값을 설정합니다.
	// 1행
	mat.setElement(0, 0, 1.0f);
	mat.setElement(0, 1, 2.0f);
	mat.setElement(0, 2, 3.0f);
	mat.setElement(0, 3, 4.0f);

	// 2행
	mat.setElement(1, 0, 5.0f);
	mat.setElement(1, 1, 6.0f);
	mat.setElement(1, 2, 7.0f);
	mat.setElement(1, 3, 8.0f);

	// 3행
	mat.setElement(2, 0, 9.0f);
	mat.setElement(2, 1, 8.0f);
	mat.setElement(2, 2, 7.0f);
	mat.setElement(2, 3, 6.0f);

	// 4행
	mat.setElement(3, 0, 5.0f);
	mat.setElement(3, 1, 4.0f);
	mat.setElement(3, 2, 3.0f);
	mat.setElement(3, 3, 2.0f);

	printf("4행 4열의 행렬값을 출력합니다.\n");
	printf("----------------------------\n");
	mat.ShowElement();
	printf("----------------------------\n");

	_getch();
	return 0;
}