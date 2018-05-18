/*
 * <파일 설명>
 * 역행렬을 알아보는 예제입니다.
 * 수학에서 3 / 3 = 1 이렇게 되는 것처럼 행렬의 나눗셈 역할을 하는 것이 역행렬입니다.
 * 다른 점이 있다면 나눗셈으로 사용되는 건 아니고 행렬을 단위행렬로 만들 때 사용해요.
 * (기존행렬 * 기존행렬의 역행렬 = 단위행렬) 이런 방식입니다.
 * 나중에 행렬과 벡터의 곱셈을 알아볼 건데 그때 역행렬을 사용해볼 거예요.
 * 어떤 벡터에 행렬을 곱해서 변환을 줬을 때 그 행렬의 역행렬을 벡터에 곱하면 변환되기 이전 벡터가 됩니다.
 * 지금은 무슨 말인지 모를테니 한번 읽고만 넘어가세요.
 * 가우스 소거법에 비하면 매우 쉽다는 사실!
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

	// 4X4행렬의 소행렬식을 구합니다.
	// 라플라스 전개를 이용하며 인자는 위행 위열부터 전달해야 합니다.
	// 전에 구현한 라플라스 전개도 아래의 함수를 이용해서 좀 더 간단히 구현해볼게요.
	// 매개변수 이름은 전과 똑같이 FE(First Element), SE(Second Element)로 표현할게요.
	float CalcMinorDeterminantByLE(float rFE1, float rFE2, float rFE3,
		                           float rSE1, float rSE2, float rSE3,
		                           float rSE4, float rSE5, float rSE6)
	{
		float rMinorDet = 0.0f;
		float rTemp[3]  = { 0.0f, 0.0f, 0.0f }; // 행렬식 중간 결과를 저장할 변수

		rTemp[0] = +rFE1 * (rSE2 * rSE6 - rSE3 * rSE5);
		rTemp[1] = -rFE2 * (rSE1 * rSE6 - rSE3 * rSE4);
		rTemp[2] = +rFE3 * (rSE1 * rSE5 - rSE2 * rSE4);

		rMinorDet = rTemp[0] + rTemp[1] + rTemp[2];
		return rMinorDet;
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
		rTemp[0] = +rFE[0] * CalcMinorDeterminantByLE(m_r11, m_r12, m_r13,
			                                          m_r21, m_r22, m_r23,
			                                          m_r31, m_r32, m_r33);

		rTemp[1] = -rFE[1] * CalcMinorDeterminantByLE(m_r10, m_r12, m_r13,
			                                          m_r20, m_r22, m_r23,
			                                          m_r30, m_r32, m_r33);

		rTemp[2] = +rFE[2] * CalcMinorDeterminantByLE(m_r10, m_r11, m_r13,
			                                          m_r20, m_r21, m_r23,
			                                          m_r30, m_r31, m_r33);

		rTemp[3] = -rFE[3] * CalcMinorDeterminantByLE(m_r10, m_r11, m_r12,
			                                          m_r20, m_r21, m_r22,
			                                          m_r30, m_r31, m_r32);

		// 각 부분을 구했으면 전부 더해줍니다.
		// 전부 더한 결과가 4X4행렬식의 값이 됩니다. (헥헥...)
		// 반복문을 사용해도 되는데 좀 더 확실하게 보여드리기 위해 하나씩 쓸게요.
		rDet = rTemp[0] + rTemp[1] + rTemp[2] + rTemp[3];

		return rDet;
	}

	// 가우스 소거법을 이용해서 행렬식을 구합니다.
	// 구하는 방법은 다음과 같습니다.
	//
	// 1. 기준 요소가 0이라면 기준 행과 임의의 행을 바꿔준다.
	//    이때는 행렬식의 부호가 바뀝니다.
	//
	// 2. 기준 행을 이용해서 나머지 행의 기준 요소를 0으로 만들어준다.
	//    한 행 또는 한 열에 어떤 수를 곱해서 더하거나 빼도 행렬식의 값은 변화되지 않습니다.
	//
	// 3. 마지막 행 기준 요소가 0이라면 행렬식은 0이 되므로 0을 반환합니다.
	//    그게 아니라면, 상삼각행렬이 완성된 상태이므로 행렬식을 구합니다.
	//
	// 4. 상삼각행렬을 이용해서 행렬식을 구합니다.
	//    상삼각행렬에서의 행렬식은 대각 요소를 전부 곱한 값과 같습니다.
	//    라플라스 전개를 해보면 여인자가 0이 되는 곳이 많은데 결과적으로는
	//    대각 요소만 나열되어서 곱하는 형태가 됩니다.
	//
	// GEM => Gaussian Elemination Method
	float CalcDeterminantByGEM()
	{
		float rDet = 1.0f; // 행렬식의 초깃값은 부호를 바꿀 수 있어야 하므로 1로 설정합니다.

		Matrix4X4 mat = *this; // 행렬식을 구하는 게 목적이므로 기존 행렬의 복사본을 이용합니다.

		// 기준 행을 시작으로 다음 행으로 진행되는데
		// 마지막 행은 처리해줄 게 없으므로 마지막 행은 제외됩니다.
		// 0, 1, 2, 3이 있을 때 0, 1, 2까지만 연산됩니다.
		for (int row = 0; row < 4 - 1; ++row)
		{
			// 첫 번째 기준 요소는 (0, 0)의 값입니다.
			// 가우스 소거법의 기준 요소는 행이므로 Row로 표시할게요. 열도 Row로 표시됩니다.
			// 왜 행이냐면 기준 요소가 0인 경우 기준 요소를 바꿔야 하는데 이것을 Pivot이라 표시해요.
			// Pivot에는 중심점이라는 뜻이 있는데 기준 요소가 0이라면 기준 행이 될 수 없으므로
			// 기준 행의 교체, 즉! 중심점을 재설정한다는 의미로 Pivot이라는 단어가 사용됩니다.
			//
			// 기준 요소가 0이라면 기준 행을 재설정해야 합니다.
			if (mat.getElement(row, row) == 0.0f)
			{
				int pivot = row; // 기준 행이 곧 중심점입니다.

				// 중심점을 재설정할 때 가장 절댓값이 큰 기준 요소로 설정합니다.
				// 그래야 가우스 소거법을 계산할 때 분모의 값을 크게 만들 수 있습니다.
				// 꼭 절댓값이 크지 않아도 계산은 성립하지만 일반적으로는 이렇게 한다네요.
				for (int nextRow = row + 1; nextRow < 4; ++nextRow)
				{
					// 위에서도 설명했지만 가우스 소거법의 중심은 행이므로 열도 행으로 표시합니다.
					// 기준 요소끼리 비교할 때 행만 비교하면 되므로 열은 고정시킵니다.
					// row라는 표기가 헷갈릴 수 있는데 여기서는 row가 col의 개념입니다.
					if (std::abs(mat.getElement(pivot, row)) < std::abs(mat.getElement(nextRow, row)))
					{
						pivot = nextRow;
					}
				}

				if (pivot != row)
				{
					mat.SwapRow(pivot, row); // 기준 행을 변경합니다, Swap이므로 순서는 무관해요.
					rDet *= -1.0f;           // 행렬식의 성질에 의해 행렬식의 부호가 바뀝니다.
				}
				// 중심점을 바꾸지 못했다면 기준 행의 기준 요소는 0이므로 행렬식의 값은 0입니다.
				// 즉, 이 경우는 pivot과 row가 같을 때입니다.
				else
				{
					return 0.0f;
				}
			}

			// 기준 행을 이용해서 기준 행을 제외한 나머지 행의 기준 요소를 0으로 만들어줍니다.
			// 이 과정이 전방 소거입니다. 반대로는 후방 소거가 있습니다.
			for (int nextRow = row + 1; nextRow < 4; ++nextRow)
			{
				// 이미 기준 요소가 0이라면 계산해줄 필요가 없습니다.
				if (mat.getElement(nextRow, row) == 0.0f)
				{
					continue;
				}

				// 나머지 행의 기준 요소를 0으로 만들기 위해 곱해주는 값입니다.
				// 이것을 유도하는 건 다음과 같습니다.
				//
				// 한 행 또는 한 열에 어떤 숫자를 곱해서 다른 행 또는 열에 더하거나 빼도
				// 행렬식의 값은 바뀌지 않아요. 여기서 주의해야 할 건 행은 행끼리 열은 열끼리 맟추기!
				// 예를 들어 row의 모든 요소에 어떤 숫자를 곱해서 nextRow의 모든 요소를 더하거나 빼도
				// 행렬식의 값은 그대로라는 거예요. 그런데 상삼각행렬을 만들기 위해서는
				// 기준 요소를 0으로 만들어야 하므로 기준 요소만큼 빼줘야 합니다.
				// 정리하자면 nextRow의 기준 요소가 0이 되려면 그 기준 요소만큼 빼주면 됩니다.
				// 그런데 row의 기준 요소의 값을 예측할 수 없으므로 곱했던 걸 다시 나눠주는 거죠.
				// 즉, (nextRow의 요소 - row의 요소 * nextRow의 기준 요소 / row의 기준 요소) 이렇게 됩니다.
				//
				// 왜 이런 짓을 하냐면 상삼각행렬을 만들기 위해 기준 행의 기준 요소만
				// 0으로 만들어주려고 하는 거예요.
				float rZeroBase = mat.getElement(nextRow, row) / mat.getElement(row, row);

				// nextRow의 모든 요소에 rZeroBase를 적용합니다.
				// 여기서는 열을 이동해야 하므로 col이라는 변수를 따로 사용할게요.
				// 상삼각행렬을 만드는 과정에서 기준 요소의 이전 요소는 이미 0이므로 신경 쓰지 않아도 돼요.
				for (int col = row; col < 4; ++col)
				{
					float rTemp = mat.getElement(nextRow, col) - mat.getElement(row, col) * rZeroBase;
					mat.setElement(nextRow, col, rTemp);
				}
			}
		}

		float rSign = rDet;

		// 여기까지 오면 상삼각행렬이 만들어진 상태이므로
		// 대각 요소만 곱해주면 그게 곧 행렬식의 값이 됩니다.
		// 반복문을 사용해도 되지만 좀 더 자세히 써볼게요.
		rDet = rDet * mat.getElement(0, 0) * mat.getElement(1, 1)
			* mat.getElement(2, 2) * mat.getElement(3, 3);

		// 상삼각행렬을 출력해봅니다.
		printf("mat의 상삼각행렬입니다.\n");
		printf("-----------------------------------\n");
		mat.ShowElement();
		printf("-----------------------------------\n");
		printf("행렬식 계산 : %.2f * %.2f * %.2f * %.2f * %.2f\n",
			rSign, mat.getElement(0, 0), mat.getElement(1, 1),
			mat.getElement(2, 2), mat.getElement(3, 3));
		printf("-----------------------------------\n");

		return rDet;
	}

	void SwapRow(int firstRow, int secondRow)
	{
		// 기존 행의 요소를 백업합니다.
		// Swap의 기본은 백업이죠.
		float rTemp[4] = { 0.0f, 0.0f, 0.0f, 0.0f };
		for (int i = 0; i < 4; ++i)
		{
			rTemp[i] = getElement(firstRow, i);
		}

		// 기존 행에 Swap할 행의 요소를 대입합니다.
		for (int i = 0; i < 4; ++i)
		{
			float rSecondRowElement = getElement(secondRow, i);
			setElement(firstRow, i, rSecondRowElement);
		}

		// Swap할 행에 기존 행의 요소를 대입합니다.
		for (int i = 0; i < 4; ++i)
		{
			setElement(secondRow, i, rTemp[i]);
		}
	}

	// 과거에는 행렬이 고등학교 과정에 포함되어있어서 그냥 공식을 외웠지만
	// 대학교 과정으로 올라오면서 공식을 유도하는 방법까지 알려줍니다.
	// 역행렬은 행렬식의 역수 * 수반행렬입니다.
	// 즉, 행렬식이 0이라면 역행렬은 정의되지 않고, 행렬식이 있어야 하므로 정방행렬만 해당됩니다.
	// 수반행렬은 처음 들어보는 용어일텐데 여인자로 이루어진 행렬의 전치행렬을 수반행렬이라고 해요.
	// 따라서 행렬식만 알고 있으면 수반행렬만 새로 적용하면 되겠죠?
	Matrix4X4* Inverse()
	{
		// 역행렬이 존재하는지 행렬식으로 판단해봅니다.
		float rDet = CalcDeterminantByLE(); // 전에 구현한 가우스 소거법을 사용해도 됩니다.
		
		if (rDet == 0.0f) // 실수는 ==으로 비교할 수 없지만 0은 제외입니다.
		{
			printf("역행렬이 존재하지 않습니다! (Det = %.2f)\n", rDet);
			printf("-----------------------------------\n");
			return nullptr;
		}

		// 행렬식의 값이 0이 아니라면 역행렬이 존재하는 것이므로
		// 여인자를 쭉 구한 뒤에 전치시켜서 수반행렬로 만들어줍니다.
		// 동일한 작업이 계속 반복되므로 함수로 묶어서 처리할게요.
		Matrix4X4 matTemp;

		/////////////////////////////////////////////////////////////////
		// 1행 전개
		matTemp.m_r00 = +1 * CalcMinorDeterminantByLE(m_r11, m_r12, m_r13,
                                                      m_r21, m_r22, m_r23,
                                                      m_r31, m_r32, m_r33);

		matTemp.m_r01 = -1 * CalcMinorDeterminantByLE(m_r10, m_r12, m_r13,
                                                      m_r20, m_r22, m_r23,
                                                      m_r30, m_r32, m_r33);

		matTemp.m_r02 = +1 * CalcMinorDeterminantByLE(m_r10, m_r11, m_r13,
                                                      m_r20, m_r21, m_r23,
                                                      m_r30, m_r31, m_r33);

		matTemp.m_r03 = -1 * CalcMinorDeterminantByLE(m_r10, m_r11, m_r12,
                                                      m_r20, m_r21, m_r22,
                                                      m_r30, m_r31, m_r32);

		/////////////////////////////////////////////////////////////////
		// 2행 전개
		matTemp.m_r10 = -1 * CalcMinorDeterminantByLE(m_r01, m_r02, m_r03,
                                                      m_r21, m_r22, m_r23,
                                                      m_r31, m_r32, m_r33);

		matTemp.m_r11 = +1 * CalcMinorDeterminantByLE(m_r00, m_r02, m_r03,
                                                      m_r20, m_r22, m_r23,
                                                      m_r30, m_r32, m_r33);

		matTemp.m_r12 = -1 * CalcMinorDeterminantByLE(m_r00, m_r01, m_r03,
                                                      m_r20, m_r21, m_r23,
                                                      m_r30, m_r31, m_r33);

		matTemp.m_r13 = +1 * CalcMinorDeterminantByLE(m_r00, m_r01, m_r02,
                                                      m_r20, m_r21, m_r22,
                                                      m_r30, m_r31, m_r32);

		/////////////////////////////////////////////////////////////////
		// 3행 전개
		matTemp.m_r20 = +1 * CalcMinorDeterminantByLE(m_r01, m_r02, m_r03,
                                                      m_r11, m_r12, m_r13,
                                                      m_r31, m_r32, m_r33);

		matTemp.m_r21 = -1 * CalcMinorDeterminantByLE(m_r00, m_r02, m_r03,
                                                      m_r10, m_r12, m_r13,
                                                      m_r30, m_r32, m_r33);

		matTemp.m_r22 = +1 * CalcMinorDeterminantByLE(m_r00, m_r01, m_r03,
                                                      m_r10, m_r11, m_r13,
                                                      m_r30, m_r31, m_r33);

		matTemp.m_r23 = -1 * CalcMinorDeterminantByLE(m_r00, m_r01, m_r02,
                                                      m_r10, m_r11, m_r12,
                                                      m_r30, m_r31, m_r32);

		/////////////////////////////////////////////////////////////////
		// 4행 전개
		matTemp.m_r30 = -1 * CalcMinorDeterminantByLE(m_r01, m_r02, m_r03,
                                                      m_r11, m_r12, m_r13,
                                                      m_r21, m_r22, m_r23);

		matTemp.m_r31 = +1 * CalcMinorDeterminantByLE(m_r00, m_r02, m_r03,
                                                      m_r10, m_r12, m_r13,
                                                      m_r20, m_r22, m_r23);

		matTemp.m_r32 = -1 * CalcMinorDeterminantByLE(m_r00, m_r01, m_r03,
                                                      m_r10, m_r11, m_r13,
                                                      m_r20, m_r21, m_r23);

		matTemp.m_r33 = +1 * CalcMinorDeterminantByLE(m_r00, m_r01, m_r02,
                                                      m_r10, m_r11, m_r12,
                                                      m_r20, m_r21, m_r22);

		matTemp.Transpose();
		matTemp.MultiplyScalar(1.0f / rDet);
		*this = matTemp;

		return this;
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
	printf("4행 4열 행렬의 역행렬을 구해봅니다.\n\n");
	printf("mat\n");
	printf("-----------------------------------\n");
	Matrix4X4 mat( 1.0f,  1.0f,  1.0f, -1.0f,
		           1.0f,  1.0f, -1.0f,  1.0f,
		           1.0f, -1.0f,  1.0f,  1.0f,
		          -1.0f,  1.0f,  1.0f,  1.0f);
	mat.ShowElement();
	printf("-----------------------------------\n\n");

	/////////////////////////////////////////////////////////////////
	printf("mat의 역행렬을 구합니다.\n");
	printf("-----------------------------------\n");
	mat.Inverse();
	mat.ShowElement();
	printf("-----------------------------------\n\n");
	/////////////////////////////////////////////////////////////////
	printf("역행렬의 역행렬은 기존행렬입니다.\n");
	printf("-----------------------------------\n");
	mat.Inverse();
	mat.ShowElement();
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
	printf("mat의 1행을 0으로 바꾼 후의 역행렬을 구합니다.\n");
	printf("-----------------------------------\n");
	mat.Inverse();
	mat.ShowElement();
	printf("-----------------------------------\n\n");
	/////////////////////////////////////////////////////////////////

	_getch();
	return 0;
}