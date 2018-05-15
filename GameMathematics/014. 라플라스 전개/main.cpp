/*
 * <파일 설명>
 * 라플라스 전개로 행렬식을 구해보는 예제입니다.
 * 게임에서 행렬식을 구할 때 라플라스 전개를 사용하는데 다른 방법도 있기는 해요.
 * 게임에서는 4X4행렬을 사용하다 보니 행렬식이 굉장히 복잡해진다는 단점이 있지만
 * 관례적으로 라플라스 전개가 많이 사용됩니다. 다른 방법은 가우스 소거법이 있는데
 * 이건 난도가 좀 있으므로 다음 예제에서 보여드릴게요.
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

		// 위와 같은 겁니다.
		//for (int row = 0; row < 4; ++row)
		//{
		//	for (int col = 0; col < 4; ++col)
		//	{
		//		m_rElement[row][col] = 0.0f;
		//	}
		//}
	}

	Matrix4X4(float r00, float r01, float r02, float r03,
		float r10, float r11, float r12, float r13,
		float r20, float r21, float r22, float r23,
		float r30, float r31, float r32, float r33)
	{
		m_r00 = r00; m_r01 = r01; m_r02 = r02; m_r03 = r03;
		m_r10 = r10; m_r11 = r11; m_r12 = r12; m_r13 = r13;
		m_r20 = r20; m_r21 = r21; m_r22 = r22; m_r23 = r23;
		m_r30 = r30; m_r31 = r31; m_r32 = r32; m_r33 = r33;
	}

	~Matrix4X4() = default;

	// 영행렬로 만들어줍니다.
	Matrix4X4* Zero()
	{
		m_r00 = 0.0f; m_r01 = 0.0f; m_r02 = 0.0f; m_r03 = 0.0f;
		m_r10 = 0.0f; m_r11 = 0.0f; m_r12 = 0.0f; m_r13 = 0.0f;
		m_r20 = 0.0f; m_r21 = 0.0f; m_r22 = 0.0f; m_r23 = 0.0f;
		m_r30 = 0.0f; m_r31 = 0.0f; m_r32 = 0.0f; m_r33 = 0.0f;

		// 위와 같은 겁니다.
		//for (int row = 0; row < 4; ++row)
		//{
		//	for (int col = 0; col < 4; ++col)
		//	{
		//		m_rElement[row][col] = 0.0f;
		//	}
		//}

		return this;
	}

	// 정방행렬(Square Matrix)은 행과 열의 수가 같은 행렬을 말해요.
	// Matrix4X4를 사용하고 있는데 행과 열의 수가 4로 똑같죠? 정방행렬입니다.
	// 정방행렬에서만 정의되는 행렬이 있는데 그게 바로 단위행렬입니다.
	// 벡터에 단위벡터가 있는 것처럼 행렬에도 기준이 되는 행렬이 단위행렬입니다.
	// 단위행렬은 행과 열이 같은 요소만 1이고 나머지는 0인 행렬을 말해요.
	// 따라서 대각만 1로 설정하는 게 아니라! 0도 꼭 설정해줘야 합니다!
	Matrix4X4* Identity()
	{
		m_r00 = 1.0f; m_r01 = 0.0f; m_r02 = 0.0f; m_r03 = 0.0f;
		m_r10 = 0.0f; m_r11 = 1.0f; m_r12 = 0.0f; m_r13 = 0.0f;
		m_r20 = 0.0f; m_r21 = 0.0f; m_r22 = 1.0f; m_r23 = 0.0f;
		m_r30 = 0.0f; m_r31 = 0.0f; m_r32 = 0.0f; m_r33 = 1.0f;

		// 위와 같은 겁니다.
		//for (int row = 0; row < 4; ++row)
		//{
		//	for (int col = 0; col < 4; ++col)
		//	{
		//		if (row == col)
		//		{
		//			m_rElement[row][col] = 1.0f;
		//		}
		//		else
		//		{
		//			m_rElement[row][col] = 0.0f;
		//		}
		//	}
		//}

		return this;
	}

	// 대각행렬은 행과 열이 같은 요소를 제외한 나머지 요소가 0인 행렬을 말해요.
	// 단위행렬과 비슷해서 헷갈릴 수 있으니까 주의해야 해요.
	// 행과 열이 같은 요소를 기존 그대로 유지시켜주는 게 핵심!
	Matrix4X4* Diagonal()
	{
		m_r00 = m_r00; m_r01 = 0.0f;  m_r02 = 0.0f;  m_r03 = 0.0f;
		m_r10 = 0.0f;  m_r11 = m_r11; m_r12 = 0.0f;  m_r13 = 0.0f;
		m_r20 = 0.0f;  m_r21 = 0.0f;  m_r22 = m_r22; m_r23 = 0.0f;
		m_r30 = 0.0f;  m_r31 = 0.0f;  m_r32 = 0.0f;  m_r33 = m_r33;

		// 위와 같은 겁니다.
		//for (int row = 0; row < 4; ++row)
		//{
		//	for (int col = 0; col < 4; ++col)
		//	{
		//		if (row != col)
		//		{
		//			m_rElement[row][col] = 0.0f;
		//		}
		//	}
		//}

		return this;
	}

	// 전치행렬은 행과 열을 바꿔주는 행렬을 말해요.
	// 행과 열이 같은 요소는 변화가 없지만 나머지 성분들은 변화가 생기게 되죠.
	// 전치행렬은 여기저기에 많이 사용되니까 만드는 방법을 잘 알아둬야 해요.
	// 전치행렬은 특성상 요소를 Swap해야 하는데 두 개의 구현 방법에 차이가 있으니 잘 보세요.
	Matrix4X4* Transpose()
	{
		float rTemp = 0.0f;

		// 4X4 행렬에서 전치행렬에 영향을 받는 요소는
		// 01 02 03 12 13 23입니다.

		// 0행 1열과 1행 0열의 Swap
		rTemp = m_r01;
		m_r01 = m_r10;
		m_r10 = rTemp;

		// 0행 2열과 2행 0열의 Swap
		rTemp = m_r02;
		m_r02 = m_r20;
		m_r20 = rTemp;

		// 0행 3열과 3행 0열의 Swap
		rTemp = m_r03;
		m_r03 = m_r30;
		m_r30 = rTemp;

		// 1행 2열과 2행 1열의 Swap
		rTemp = m_r12;
		m_r12 = m_r21;
		m_r21 = rTemp;

		// 1행 3열과 3행 1열의 Swap
		rTemp = m_r13;
		m_r13 = m_r31;
		m_r31 = rTemp;

		// 2행 3열과 3행 2열의 Swap
		rTemp = m_r23;
		m_r23 = m_r32;
		m_r32 = rTemp;

		// 위와 같은 겁니다.
		//for (int row = 0; row < 4; ++row)
		//{
		//	for (int col = row; col < 4; ++col)
		//	{
		//		if (row != col)
		//		{
		//			rTemp                = m_rElement[row][col]; // 기존값 보관
		//			m_rElement[row][col] = m_rElement[col][row]; // 기존값 덮어씌우기
		//			m_rElement[col][row] = rTemp;                // 기존값 대입
		//		}
		//	}
		//}

		return this;
	}

	Matrix4X4* Add(const Matrix4X4& rhs)
	{
		m_r00 += rhs.m_r00; m_r01 += rhs.m_r01; m_r02 += rhs.m_r02; m_r03 += rhs.m_r03;
		m_r10 += rhs.m_r10; m_r11 += rhs.m_r11; m_r12 += rhs.m_r12; m_r13 += rhs.m_r13;
		m_r20 += rhs.m_r20; m_r21 += rhs.m_r21; m_r22 += rhs.m_r22; m_r23 += rhs.m_r23;
		m_r30 += rhs.m_r30; m_r31 += rhs.m_r31; m_r32 += rhs.m_r32; m_r33 += rhs.m_r33;

		return this;
	}

	Matrix4X4* Subtract(const Matrix4X4& rhs)
	{
		m_r00 -= rhs.m_r00; m_r01 -= rhs.m_r01; m_r02 -= rhs.m_r02; m_r03 -= rhs.m_r03;
		m_r10 -= rhs.m_r10; m_r11 -= rhs.m_r11; m_r12 -= rhs.m_r12; m_r13 -= rhs.m_r13;
		m_r20 -= rhs.m_r20; m_r21 -= rhs.m_r21; m_r22 -= rhs.m_r22; m_r23 -= rhs.m_r23;
		m_r30 -= rhs.m_r30; m_r31 -= rhs.m_r31; m_r32 -= rhs.m_r32; m_r33 -= rhs.m_r33;

		return this;
	}

	Matrix4X4* MultiplyScalar(float rScalar)
	{
		m_r00 *= rScalar; m_r01 *= rScalar; m_r02 *= rScalar; m_r03 *= rScalar;
		m_r10 *= rScalar; m_r11 *= rScalar; m_r12 *= rScalar; m_r13 *= rScalar;
		m_r20 *= rScalar; m_r21 *= rScalar; m_r22 *= rScalar; m_r23 *= rScalar;
		m_r30 *= rScalar; m_r31 *= rScalar; m_r32 *= rScalar; m_r33 *= rScalar;

		// 위와 같은 겁니다.
		//for (int row = 0; row < 4; ++row)
		//{
		//	for (int col = row; col < 4; ++col)
		//	{
		//		m_rElement[row][col] *= rScalar;
		//	}
		//}

		return this;
	}

	// 행렬의 곱셈을 정의합니다.
	// matFirst와 matSecond가 있을 때 matFirst의 열과 matSecond의 행이 같아야 곱셈이 정의됩니다.
	// 하지만 Matrix4X4에서는 matFirst의 열이 4, matSecond의 행이 4일 때만 곱셈이 정의됩니다.
	// 나중에 벡터와 곱하게 되는데 벡터도 요소 4개로 확장되어야 곱셈이 정의됩니다.
	// 행렬의 곱셈은 matFirst의 행과 matSecond의 열을 차례로 곱해주면 됩니다.
	// 이때 matSecond의 열은 옆으로 이동하지만 matFirst의 행은 고정되어야 합니다.
	// matSecond의 열을 다 돌아야 matFirst의 행을 증가시킬 수 있습니다.
	// 연산되는 모습을 자세히 보면 벡터의 내적을 구하는 것과 같습니다.
	// 행렬의 덧셈과 뺄셈 그리고 스칼라곱셈은 교환법칙(자리를 바꿔서 연산해도 결과가 같은 것)이
	// 성립하지 않으므로 곱하는 순서가 매우 중요합니다! 이걸 꼭 기억해야 해요!
	Matrix4X4* Multiply(const Matrix4X4& rhs)
	{
		Matrix4X4 matTemp;

		// 행렬의 0행과 rhs의 열의 곱셈입니다.
		matTemp.m_r00 =
			(m_r00 * rhs.m_r00) + (m_r01 * rhs.m_r10) + (m_r02 * rhs.m_r20) + (m_r03 * rhs.m_r30);
		matTemp.m_r01 =
			(m_r00 * rhs.m_r01) + (m_r01 * rhs.m_r11) + (m_r02 * rhs.m_r21) + (m_r03 * rhs.m_r31);
		matTemp.m_r02 =
			(m_r00 * rhs.m_r02) + (m_r01 * rhs.m_r12) + (m_r02 * rhs.m_r22) + (m_r03 * rhs.m_r32);
		matTemp.m_r03 =
			(m_r00 * rhs.m_r03) + (m_r01 * rhs.m_r13) + (m_r02 * rhs.m_r23) + (m_r03 * rhs.m_r33);

		// 행렬의 1행과 rhs의 열의 곱셈입니다.
		matTemp.m_r10 =
			(m_r10 * rhs.m_r00) + (m_r11 * rhs.m_r10) + (m_r12 * rhs.m_r20) + (m_r13 * rhs.m_r30);
		matTemp.m_r11 =
			(m_r10 * rhs.m_r01) + (m_r11 * rhs.m_r11) + (m_r12 * rhs.m_r21) + (m_r13 * rhs.m_r31);
		matTemp.m_r12 =
			(m_r10 * rhs.m_r02) + (m_r11 * rhs.m_r12) + (m_r12 * rhs.m_r22) + (m_r13 * rhs.m_r32);
		matTemp.m_r13 =
			(m_r10 * rhs.m_r03) + (m_r11 * rhs.m_r13) + (m_r12 * rhs.m_r23) + (m_r13 * rhs.m_r33);

		// 행렬의 2행과 rhs의 열의 곱셈입니다.
		matTemp.m_r20 =
			(m_r20 * rhs.m_r00) + (m_r21 * rhs.m_r10) + (m_r22 * rhs.m_r20) + (m_r23 * rhs.m_r30);
		matTemp.m_r21 =
			(m_r20 * rhs.m_r01) + (m_r21 * rhs.m_r11) + (m_r22 * rhs.m_r21) + (m_r23 * rhs.m_r31);
		matTemp.m_r22 =
			(m_r20 * rhs.m_r02) + (m_r21 * rhs.m_r12) + (m_r22 * rhs.m_r22) + (m_r23 * rhs.m_r32);
		matTemp.m_r23 =
			(m_r20 * rhs.m_r03) + (m_r21 * rhs.m_r13) + (m_r22 * rhs.m_r23) + (m_r23 * rhs.m_r33);

		// 행렬의 3행과 rhs의 열의 곱셈입니다.
		matTemp.m_r30 =
			(m_r30 * rhs.m_r00) + (m_r31 * rhs.m_r10) + (m_r32 * rhs.m_r20) + (m_r33 * rhs.m_r30);
		matTemp.m_r31 =
			(m_r30 * rhs.m_r01) + (m_r31 * rhs.m_r11) + (m_r32 * rhs.m_r21) + (m_r33 * rhs.m_r31);
		matTemp.m_r32 =
			(m_r30 * rhs.m_r02) + (m_r31 * rhs.m_r12) + (m_r32 * rhs.m_r22) + (m_r33 * rhs.m_r32);
		matTemp.m_r33 =
			(m_r30 * rhs.m_r03) + (m_r31 * rhs.m_r13) + (m_r32 * rhs.m_r23) + (m_r33 * rhs.m_r33);

		// 값을 중복해서 사용하기 때문에 임시변수에 넣었다가 갱신합니다.
		*this = matTemp;

		return this;
	}

	// 라플라스 전개를 이용해서 행렬식을 구합니다.
	// 2X2행렬식을 이용하면 4X4행렬식도 구할 수 있지만 계산이 좀 복잡해집니다.
	// 하지만 게임에서는 4X4행렬을 사용하므로 4X4행렬식은 구할 줄 알아야 해요.
	// 행렬식은 말 그대로 하나의 식이라 결과는 하나의 값이 됩니다.
	// LE => LaplaceExpansion
	float CalcDeterminantByLE()
	{
		float rDet = 0.0f; // Det는 Determinant의 약자

		// 행렬식 구하는 기준은 윗행 전개입니다.
		// 즉, 4X4를 3X3으로 분리할 때는 1행을! 3X3을 2X2로 분리할 때는 2행을 이용합니다!
		// 라플라스 전개에 따르면 아무 행과 아무 열을 선택해도 행렬식의 값은 동일합니다.
		// 1행 전개는 FE(First Element), 2행 전개는 SE(Second Element)로 표현할게요. (마땅히 쓸 단어가...)
		// 원래는 그냥 써도 되는데 각 행렬식을 구분하기 위해 표시합니다.
		
		float rFE[4]   = { m_r00, m_r01, m_r02, m_r03 }; // 1행 전개에 사용할 요소
		float rSE[4]   = { m_r10, m_r11, m_r12, m_r13 }; // 2행 전개에 사용할 요소
		float rTemp[4] = { 0.0f, 0.0f, 0.0f, 0.0f };     // 행렬식 중간 결과를 저장할 변수
		
		// 첫 번째 중간 결과입니다.
		// 부호를 확실히 표시하기 위해 +도 쓸게요.
		rTemp[0] = +rFE[0] * ( +(rSE[1] * ( (m_r22 * m_r33) - (m_r23 * m_r32) ) )
			                   -(rSE[2] * ( (m_r21 * m_r33) - (m_r23 * m_r31) ) )
			                   +(rSE[3] * ( (m_r21 * m_r32) - (m_r22 * m_r31) ) ) );

		rTemp[1] = -rFE[1] * ( +(rSE[0] * ( (m_r22 * m_r33) - (m_r23 * m_r32) ) )
			                   -(rSE[2] * ( (m_r20 * m_r33) - (m_r23 * m_r30) ) )
			                   +(rSE[3] * ( (m_r20 * m_r32) - (m_r22 * m_r30) ) ) );

		rTemp[2] = +rFE[2] * ( +(rSE[0] * ( (m_r21 * m_r33) - (m_r23 * m_r31) ) )
					           -(rSE[1] * ( (m_r20 * m_r33) - (m_r23 * m_r30) ) )
					           +(rSE[3] * ( (m_r20 * m_r31) - (m_r21 * m_r30) ) ) );

		rTemp[3] = -rFE[3] * ( +(rSE[0] * ( (m_r21 * m_r32) - (m_r22 * m_r31) ) )
							   -(rSE[1] * ( (m_r20 * m_r32) - (m_r22 * m_r30) ) )
							   +(rSE[2] * ( (m_r20 * m_r31) - (m_r21 * m_r30) ) ) );

		// 각 부분을 구했으면 전부 더해줍니다.
		// 전부 더한 결과가 4X4행렬식의 값이 됩니다. (헥헥...)
		// 반복문을 사용해도 되는데 좀 더 확실하게 보여드리기 위해 하나씩 쓸게요.
		rDet = rTemp[0] + rTemp[1] + rTemp[2] + rTemp[3];

		return rDet;
	}

	void ShowElement()
	{
		printf("     1열     2열     3열     4열\n");
		printf("1행 %6.2f  %6.2f  %6.2f  %6.2f\n", m_r00, m_r01, m_r02, m_r03);
		printf("2행 %6.2f  %6.2f  %6.2f  %6.2f\n", m_r10, m_r11, m_r12, m_r13);
		printf("3행 %6.2f  %6.2f  %6.2f  %6.2f\n", m_r20, m_r21, m_r22, m_r23);
		printf("4행 %6.2f  %6.2f  %6.2f  %6.2f\n", m_r30, m_r31, m_r32, m_r33);

		// 위와 같은 겁니다.
		//for (int row = 0; row < 4; ++row)
		//{
		//	for (int col = 0; col < 4; ++col)
		//	{
		//		printf("(%d, %d = %6.2f) ", row, col, m_rElement[row][col]);
		//	}
		//  printf("\n");
		//}
	}

	/////////////////////////////////////////////////////////////////
	// Getter
	float getElement(int row, int col)
	{
		if ((row < 0) ||
			(row > 4 - 1) ||
			(col < 0) ||
			(col > 4 - 1))
		{
			printf("행과 열의 범위를 맞춰주세요!\n");
			printf("허용 범위 (0, 0) ~ (3, 3) => 오류(%d, %d)\n", row, col);
			return 0.0f;
		}

		return m_rElement[row][col];
	}

	/////////////////////////////////////////////////////////////////
	// Setter
	void setElement(int row, int col, float rVal)
	{
		if ((row < 0) ||
			(row > 4 - 1) ||
			(col < 0) ||
			(col > 4 - 1))
		{
			printf("행과 열의 범위를 맞춰주세요!\n");
			printf("허용 범위 (0, 0) ~ (3, 3) => 오류(%d, %d)\n", row, col);
			return;
		}

		m_rElement[row][col] = rVal;
	}

	// 연산자 오버로딩의 구현 라인수를 줄였습니다.
	// 원본을 보존한다면 코드를 재활용할 수 있습니다.

	Matrix4X4 operator +(const Matrix4X4& rhs)
	{
		Matrix4X4 mat = *this;
		mat.Add(rhs);
		return mat;
	}

	Matrix4X4 operator -(const Matrix4X4& rhs)
	{
		Matrix4X4 mat = *this;
		mat.Subtract(rhs);
		return mat;
	}

	Matrix4X4 operator *(float rScalar)
	{
		Matrix4X4 mat = *this;
		mat.MultiplyScalar(rScalar);
		return mat;
	}

	Matrix4X4 operator *(const Matrix4X4& rhs)
	{
		Matrix4X4 mat = *this;
		mat.Multiply(rhs);
		return mat;
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
	printf("4행 4열 행렬의 행렬식을 구해봅니다.\n\n");
	printf("mat\n");
	printf("-----------------------------------\n");
	Matrix4X4 mat( 2.0f, -1.0f, 3.0f,  0.0f,
		          -3.0f,  1.0f, 0.0f,  4.0f,
		          -2.0f,  1.0f, 4.0f,  1.0f,
		          -1.0f,  3.0f, 0.0f, -2.0f);
	mat.ShowElement();
	printf("-----------------------------------\n\n");

	/////////////////////////////////////////////////////////////////
	printf("mat의 행렬식을 구합니다.\n");
	printf("-----------------------------------\n");
	printf("mat의 행렬식 결과 => %.2f\n", mat.CalcDeterminantByLE());
	printf("-----------------------------------\n\n\n\n");
	/////////////////////////////////////////////////////////////////

	for (int i = 0; i < 4; ++i)
	{
		mat.setElement(0, i, 0.0f);
	}

	printf("mat\n");
	printf("-----------------------------------\n");
	mat.ShowElement();
	printf("-----------------------------------\n\n");
	/////////////////////////////////////////////////////////////////
	printf("mat의 1행을 0으로 바꾼 후의 행렬식을 구합니다.\n");
	printf("-----------------------------------\n");
	printf("mat의 행렬식 결과 => %.2f\n", mat.CalcDeterminantByLE());
	printf("-----------------------------------\n\n");
	/////////////////////////////////////////////////////////////////

	_getch();
	return 0;
}