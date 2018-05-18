/*
 * <���� ����>
 * ������� �˾ƺ��� �����Դϴ�.
 * ���п��� 3 / 3 = 1 �̷��� �Ǵ� ��ó�� ����� ������ ������ �ϴ� ���� ������Դϴ�.
 * �ٸ� ���� �ִٸ� ���������� ���Ǵ� �� �ƴϰ� ����� ������ķ� ���� �� ����ؿ�.
 * (������� * ��������� ����� = �������) �̷� ����Դϴ�.
 * ���߿� ��İ� ������ ������ �˾ƺ� �ǵ� �׶� ������� ����غ� �ſ���.
 * � ���Ϳ� ����� ���ؼ� ��ȯ�� ���� �� �� ����� ������� ���Ϳ� ���ϸ� ��ȯ�Ǳ� ���� ���Ͱ� �˴ϴ�.
 * ������ ���� ������ ���״� �ѹ� �а� �Ѿ����.
 * ���콺 �ҰŹ��� ���ϸ� �ſ� ���ٴ� ���!
 */

// double���� float���� ��ҵǴ� �� ���
#pragma warning(disable : 4305)

#include <conio.h>   // CMD ������� �ٷ�� ���� ���(��ǥ��)
#include <windows.h> // CMD Ȯ�� ����� �̿��ϱ� ���� ���(��ǥ��)
#include <cstdio>    // CMD ������� �ٷ�� ���� ���(ǥ��)
#include <cmath>     // ������ �ٷ�� ���� ���(ǥ��)
#include <cfloat>    // �Ǽ��� �ٷ�� ���� ���(ǥ��)

// ��� Ŭ����
class Matrix4X4
{
public:
	// �ʱ�ȭ�� 0���� �����մϴ�.
	// �̷� ����� �����(Zero Matrix)�̶� �θ��ϴ�.
	Matrix4X4()
	{
		m_r00 = 0.0f; m_r01 = 0.0f; m_r02 = 0.0f; m_r03 = 0.0f;
		m_r10 = 0.0f; m_r11 = 0.0f; m_r12 = 0.0f; m_r13 = 0.0f;
		m_r20 = 0.0f; m_r21 = 0.0f; m_r22 = 0.0f; m_r23 = 0.0f;
		m_r30 = 0.0f; m_r31 = 0.0f; m_r32 = 0.0f; m_r33 = 0.0f;

		// ���� ���� �̴ϴ�.
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

	// ����ķ� ������ݴϴ�.
	Matrix4X4* Zero()
	{
		m_r00 = 0.0f; m_r01 = 0.0f; m_r02 = 0.0f; m_r03 = 0.0f;
		m_r10 = 0.0f; m_r11 = 0.0f; m_r12 = 0.0f; m_r13 = 0.0f;
		m_r20 = 0.0f; m_r21 = 0.0f; m_r22 = 0.0f; m_r23 = 0.0f;
		m_r30 = 0.0f; m_r31 = 0.0f; m_r32 = 0.0f; m_r33 = 0.0f;

		// ���� ���� �̴ϴ�.
		//for (int row = 0; row < 4; ++row)
		//{
		//	for (int col = 0; col < 4; ++col)
		//	{
		//		m_rElement[row][col] = 0.0f;
		//	}
		//}

		return this;
	}

	// �������(Square Matrix)�� ��� ���� ���� ���� ����� ���ؿ�.
	// Matrix4X4�� ����ϰ� �ִµ� ��� ���� ���� 4�� �Ȱ���? ��������Դϴ�.
	// ������Ŀ����� ���ǵǴ� ����� �ִµ� �װ� �ٷ� ��������Դϴ�.
	// ���Ϳ� �������Ͱ� �ִ� ��ó�� ��Ŀ��� ������ �Ǵ� ����� ��������Դϴ�.
	// ��������� ��� ���� ���� ��Ҹ� 1�̰� �������� 0�� ����� ���ؿ�.
	// ���� �밢�� 1�� �����ϴ� �� �ƴ϶�! 0�� �� ��������� �մϴ�!
	Matrix4X4* Identity()
	{
		m_r00 = 1.0f; m_r01 = 0.0f; m_r02 = 0.0f; m_r03 = 0.0f;
		m_r10 = 0.0f; m_r11 = 1.0f; m_r12 = 0.0f; m_r13 = 0.0f;
		m_r20 = 0.0f; m_r21 = 0.0f; m_r22 = 1.0f; m_r23 = 0.0f;
		m_r30 = 0.0f; m_r31 = 0.0f; m_r32 = 0.0f; m_r33 = 1.0f;

		// ���� ���� �̴ϴ�.
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

	// �밢����� ��� ���� ���� ��Ҹ� ������ ������ ��Ұ� 0�� ����� ���ؿ�.
	// ������İ� ����ؼ� �򰥸� �� �����ϱ� �����ؾ� �ؿ�.
	// ��� ���� ���� ��Ҹ� ���� �״�� ���������ִ� �� �ٽ�!
	Matrix4X4* Diagonal()
	{
		m_r00 = m_r00; m_r01 = 0.0f;  m_r02 = 0.0f;  m_r03 = 0.0f;
		m_r10 = 0.0f;  m_r11 = m_r11; m_r12 = 0.0f;  m_r13 = 0.0f;
		m_r20 = 0.0f;  m_r21 = 0.0f;  m_r22 = m_r22; m_r23 = 0.0f;
		m_r30 = 0.0f;  m_r31 = 0.0f;  m_r32 = 0.0f;  m_r33 = m_r33;

		// ���� ���� �̴ϴ�.
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

	// ��ġ����� ��� ���� �ٲ��ִ� ����� ���ؿ�.
	// ��� ���� ���� ��Ҵ� ��ȭ�� ������ ������ ���е��� ��ȭ�� ����� ����.
	// ��ġ����� �������⿡ ���� ���Ǵϱ� ����� ����� �� �˾Ƶ־� �ؿ�.
	// ��ġ����� Ư���� ��Ҹ� Swap�ؾ� �ϴµ� �� ���� ���� ����� ���̰� ������ �� ������.
	Matrix4X4* Transpose()
	{
		float rTemp = 0.0f;

		// 4X4 ��Ŀ��� ��ġ��Ŀ� ������ �޴� ��Ҵ�
		// 01 02 03 12 13 23�Դϴ�.

		// 0�� 1���� 1�� 0���� Swap
		rTemp = m_r01;
		m_r01 = m_r10;
		m_r10 = rTemp;

		// 0�� 2���� 2�� 0���� Swap
		rTemp = m_r02;
		m_r02 = m_r20;
		m_r20 = rTemp;

		// 0�� 3���� 3�� 0���� Swap
		rTemp = m_r03;
		m_r03 = m_r30;
		m_r30 = rTemp;

		// 1�� 2���� 2�� 1���� Swap
		rTemp = m_r12;
		m_r12 = m_r21;
		m_r21 = rTemp;

		// 1�� 3���� 3�� 1���� Swap
		rTemp = m_r13;
		m_r13 = m_r31;
		m_r31 = rTemp;

		// 2�� 3���� 3�� 2���� Swap
		rTemp = m_r23;
		m_r23 = m_r32;
		m_r32 = rTemp;

		// ���� ���� �̴ϴ�.
		//for (int row = 0; row < 4; ++row)
		//{
		//	for (int col = row; col < 4; ++col)
		//	{
		//		if (row != col)
		//		{
		//			rTemp                = m_rElement[row][col]; // ������ ����
		//			m_rElement[row][col] = m_rElement[col][row]; // ������ ������
		//			m_rElement[col][row] = rTemp;                // ������ ����
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

		// ���� ���� �̴ϴ�.
		//for (int row = 0; row < 4; ++row)
		//{
		//	for (int col = row; col < 4; ++col)
		//	{
		//		m_rElement[row][col] *= rScalar;
		//	}
		//}

		return this;
	}

	// ����� ������ �����մϴ�.
	// matFirst�� matSecond�� ���� �� matFirst�� ���� matSecond�� ���� ���ƾ� ������ ���ǵ˴ϴ�.
	// ������ Matrix4X4������ matFirst�� ���� 4, matSecond�� ���� 4�� ���� ������ ���ǵ˴ϴ�.
	// ���߿� ���Ϳ� ���ϰ� �Ǵµ� ���͵� ��� 4���� Ȯ��Ǿ�� ������ ���ǵ˴ϴ�.
	// ����� ������ matFirst�� ��� matSecond�� ���� ���ʷ� �����ָ� �˴ϴ�.
	// �̶� matSecond�� ���� ������ �̵������� matFirst�� ���� �����Ǿ�� �մϴ�.
	// matSecond�� ���� �� ���ƾ� matFirst�� ���� ������ų �� �ֽ��ϴ�.
	// ����Ǵ� ����� �ڼ��� ���� ������ ������ ���ϴ� �Ͱ� �����ϴ�.
	// ����� ������ ���� �׸��� ��Į������� ��ȯ��Ģ(�ڸ��� �ٲ㼭 �����ص� ����� ���� ��)��
	// �������� �����Ƿ� ���ϴ� ������ �ſ� �߿��մϴ�! �̰� �� ����ؾ� �ؿ�!
	Matrix4X4* Multiply(const Matrix4X4& rhs)
	{
		Matrix4X4 matTemp;

		// ����� 0��� rhs�� ���� �����Դϴ�.
		matTemp.m_r00 =
			(m_r00 * rhs.m_r00) + (m_r01 * rhs.m_r10) + (m_r02 * rhs.m_r20) + (m_r03 * rhs.m_r30);
		matTemp.m_r01 =
			(m_r00 * rhs.m_r01) + (m_r01 * rhs.m_r11) + (m_r02 * rhs.m_r21) + (m_r03 * rhs.m_r31);
		matTemp.m_r02 =
			(m_r00 * rhs.m_r02) + (m_r01 * rhs.m_r12) + (m_r02 * rhs.m_r22) + (m_r03 * rhs.m_r32);
		matTemp.m_r03 =
			(m_r00 * rhs.m_r03) + (m_r01 * rhs.m_r13) + (m_r02 * rhs.m_r23) + (m_r03 * rhs.m_r33);

		// ����� 1��� rhs�� ���� �����Դϴ�.
		matTemp.m_r10 =
			(m_r10 * rhs.m_r00) + (m_r11 * rhs.m_r10) + (m_r12 * rhs.m_r20) + (m_r13 * rhs.m_r30);
		matTemp.m_r11 =
			(m_r10 * rhs.m_r01) + (m_r11 * rhs.m_r11) + (m_r12 * rhs.m_r21) + (m_r13 * rhs.m_r31);
		matTemp.m_r12 =
			(m_r10 * rhs.m_r02) + (m_r11 * rhs.m_r12) + (m_r12 * rhs.m_r22) + (m_r13 * rhs.m_r32);
		matTemp.m_r13 =
			(m_r10 * rhs.m_r03) + (m_r11 * rhs.m_r13) + (m_r12 * rhs.m_r23) + (m_r13 * rhs.m_r33);

		// ����� 2��� rhs�� ���� �����Դϴ�.
		matTemp.m_r20 =
			(m_r20 * rhs.m_r00) + (m_r21 * rhs.m_r10) + (m_r22 * rhs.m_r20) + (m_r23 * rhs.m_r30);
		matTemp.m_r21 =
			(m_r20 * rhs.m_r01) + (m_r21 * rhs.m_r11) + (m_r22 * rhs.m_r21) + (m_r23 * rhs.m_r31);
		matTemp.m_r22 =
			(m_r20 * rhs.m_r02) + (m_r21 * rhs.m_r12) + (m_r22 * rhs.m_r22) + (m_r23 * rhs.m_r32);
		matTemp.m_r23 =
			(m_r20 * rhs.m_r03) + (m_r21 * rhs.m_r13) + (m_r22 * rhs.m_r23) + (m_r23 * rhs.m_r33);

		// ����� 3��� rhs�� ���� �����Դϴ�.
		matTemp.m_r30 =
			(m_r30 * rhs.m_r00) + (m_r31 * rhs.m_r10) + (m_r32 * rhs.m_r20) + (m_r33 * rhs.m_r30);
		matTemp.m_r31 =
			(m_r30 * rhs.m_r01) + (m_r31 * rhs.m_r11) + (m_r32 * rhs.m_r21) + (m_r33 * rhs.m_r31);
		matTemp.m_r32 =
			(m_r30 * rhs.m_r02) + (m_r31 * rhs.m_r12) + (m_r32 * rhs.m_r22) + (m_r33 * rhs.m_r32);
		matTemp.m_r33 =
			(m_r30 * rhs.m_r03) + (m_r31 * rhs.m_r13) + (m_r32 * rhs.m_r23) + (m_r33 * rhs.m_r33);

		// ���� �ߺ��ؼ� ����ϱ� ������ �ӽú����� �־��ٰ� �����մϴ�.
		*this = matTemp;

		return this;
	}

	// 4X4����� ����Ľ��� ���մϴ�.
	// ���ö� ������ �̿��ϸ� ���ڴ� ���� �������� �����ؾ� �մϴ�.
	// ���� ������ ���ö� ������ �Ʒ��� �Լ��� �̿��ؼ� �� �� ������ �����غ��Կ�.
	// �Ű����� �̸��� ���� �Ȱ��� FE(First Element), SE(Second Element)�� ǥ���ҰԿ�.
	float CalcMinorDeterminantByLE(float rFE1, float rFE2, float rFE3,
		                           float rSE1, float rSE2, float rSE3,
		                           float rSE4, float rSE5, float rSE6)
	{
		float rMinorDet = 0.0f;
		float rTemp[3]  = { 0.0f, 0.0f, 0.0f }; // ��Ľ� �߰� ����� ������ ����

		rTemp[0] = +rFE1 * (rSE2 * rSE6 - rSE3 * rSE5);
		rTemp[1] = -rFE2 * (rSE1 * rSE6 - rSE3 * rSE4);
		rTemp[2] = +rFE3 * (rSE1 * rSE5 - rSE2 * rSE4);

		rMinorDet = rTemp[0] + rTemp[1] + rTemp[2];
		return rMinorDet;
	}

	// ���ö� ������ �̿��ؼ� ��Ľ��� ���մϴ�.
	// 2X2��Ľ��� �̿��ϸ� 4X4��Ľĵ� ���� �� ������ ����� �� ���������ϴ�.
	// ������ ���ӿ����� 4X4����� ����ϹǷ� 4X4��Ľ��� ���� �� �˾ƾ� �ؿ�.
	// ��Ľ��� �� �״�� �ϳ��� ���̶� ����� �ϳ��� ���� �˴ϴ�.
	// LE => LaplaceExpansion
	float CalcDeterminantByLE()
	{
		float rDet = 0.0f; // Det�� Determinant�� ����

		// ��Ľ� ���ϴ� ������ ���� �����Դϴ�.
		// ��, 4X4�� 3X3���� �и��� ���� 1����! 3X3�� 2X2�� �и��� ���� 2���� �̿��մϴ�!
		// ���ö� ������ ������ �ƹ� ��� �ƹ� ���� �����ص� ��Ľ��� ���� �����մϴ�.
		// 1�� ������ FE(First Element), 2�� ������ SE(Second Element)�� ǥ���ҰԿ�. (������ �� �ܾ...)
		// ������ �׳� �ᵵ �Ǵµ� �� ��Ľ��� �����ϱ� ���� ǥ���մϴ�.
		float rFE[4]   = { m_r00, m_r01, m_r02, m_r03 }; // 1�� ������ ����� ���
		float rSE[4]   = { m_r10, m_r11, m_r12, m_r13 }; // 2�� ������ ����� ���
		float rTemp[4] = { 0.0f, 0.0f, 0.0f, 0.0f };     // ��Ľ� �߰� ����� ������ ����

		// ù ��° �߰� ����Դϴ�.
		// ��ȣ�� Ȯ���� ǥ���ϱ� ���� +�� ���Կ�.
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

		// �� �κ��� �������� ���� �����ݴϴ�.
		// ���� ���� ����� 4X4��Ľ��� ���� �˴ϴ�. (����...)
		// �ݺ����� ����ص� �Ǵµ� �� �� Ȯ���ϰ� �����帮�� ���� �ϳ��� ���Կ�.
		rDet = rTemp[0] + rTemp[1] + rTemp[2] + rTemp[3];

		return rDet;
	}

	// ���콺 �ҰŹ��� �̿��ؼ� ��Ľ��� ���մϴ�.
	// ���ϴ� ����� ������ �����ϴ�.
	//
	// 1. ���� ��Ұ� 0�̶�� ���� ��� ������ ���� �ٲ��ش�.
	//    �̶��� ��Ľ��� ��ȣ�� �ٲ�ϴ�.
	//
	// 2. ���� ���� �̿��ؼ� ������ ���� ���� ��Ҹ� 0���� ������ش�.
	//    �� �� �Ǵ� �� ���� � ���� ���ؼ� ���ϰų� ���� ��Ľ��� ���� ��ȭ���� �ʽ��ϴ�.
	//
	// 3. ������ �� ���� ��Ұ� 0�̶�� ��Ľ��� 0�� �ǹǷ� 0�� ��ȯ�մϴ�.
	//    �װ� �ƴ϶��, ��ﰢ����� �ϼ��� �����̹Ƿ� ��Ľ��� ���մϴ�.
	//
	// 4. ��ﰢ����� �̿��ؼ� ��Ľ��� ���մϴ�.
	//    ��ﰢ��Ŀ����� ��Ľ��� �밢 ��Ҹ� ���� ���� ���� �����ϴ�.
	//    ���ö� ������ �غ��� �����ڰ� 0�� �Ǵ� ���� ������ ��������δ�
	//    �밢 ��Ҹ� �����Ǿ ���ϴ� ���°� �˴ϴ�.
	//
	// GEM => Gaussian Elemination Method
	float CalcDeterminantByGEM()
	{
		float rDet = 1.0f; // ��Ľ��� �ʱ갪�� ��ȣ�� �ٲ� �� �־�� �ϹǷ� 1�� �����մϴ�.

		Matrix4X4 mat = *this; // ��Ľ��� ���ϴ� �� �����̹Ƿ� ���� ����� ���纻�� �̿��մϴ�.

		// ���� ���� �������� ���� ������ ����Ǵµ�
		// ������ ���� ó������ �� �����Ƿ� ������ ���� ���ܵ˴ϴ�.
		// 0, 1, 2, 3�� ���� �� 0, 1, 2������ ����˴ϴ�.
		for (int row = 0; row < 4 - 1; ++row)
		{
			// ù ��° ���� ��Ҵ� (0, 0)�� ���Դϴ�.
			// ���콺 �ҰŹ��� ���� ��Ҵ� ���̹Ƿ� Row�� ǥ���ҰԿ�. ���� Row�� ǥ�õ˴ϴ�.
			// �� ���̳ĸ� ���� ��Ұ� 0�� ��� ���� ��Ҹ� �ٲ�� �ϴµ� �̰��� Pivot�̶� ǥ���ؿ�.
			// Pivot���� �߽����̶�� ���� �ִµ� ���� ��Ұ� 0�̶�� ���� ���� �� �� �����Ƿ�
			// ���� ���� ��ü, ��! �߽����� �缳���Ѵٴ� �ǹ̷� Pivot�̶�� �ܾ ���˴ϴ�.
			//
			// ���� ��Ұ� 0�̶�� ���� ���� �缳���ؾ� �մϴ�.
			if (mat.getElement(row, row) == 0.0f)
			{
				int pivot = row; // ���� ���� �� �߽����Դϴ�.

				// �߽����� �缳���� �� ���� ������ ū ���� ��ҷ� �����մϴ�.
				// �׷��� ���콺 �ҰŹ��� ����� �� �и��� ���� ũ�� ���� �� �ֽ��ϴ�.
				// �� ������ ũ�� �ʾƵ� ����� ���������� �Ϲ������δ� �̷��� �Ѵٳ׿�.
				for (int nextRow = row + 1; nextRow < 4; ++nextRow)
				{
					// �������� ���������� ���콺 �ҰŹ��� �߽��� ���̹Ƿ� ���� ������ ǥ���մϴ�.
					// ���� ��ҳ��� ���� �� �ุ ���ϸ� �ǹǷ� ���� ������ŵ�ϴ�.
					// row��� ǥ�Ⱑ �򰥸� �� �ִµ� ���⼭�� row�� col�� �����Դϴ�.
					if (std::abs(mat.getElement(pivot, row)) < std::abs(mat.getElement(nextRow, row)))
					{
						pivot = nextRow;
					}
				}

				if (pivot != row)
				{
					mat.SwapRow(pivot, row); // ���� ���� �����մϴ�, Swap�̹Ƿ� ������ �����ؿ�.
					rDet *= -1.0f;           // ��Ľ��� ������ ���� ��Ľ��� ��ȣ�� �ٲ�ϴ�.
				}
				// �߽����� �ٲ��� ���ߴٸ� ���� ���� ���� ��Ҵ� 0�̹Ƿ� ��Ľ��� ���� 0�Դϴ�.
				// ��, �� ���� pivot�� row�� ���� ���Դϴ�.
				else
				{
					return 0.0f;
				}
			}

			// ���� ���� �̿��ؼ� ���� ���� ������ ������ ���� ���� ��Ҹ� 0���� ������ݴϴ�.
			// �� ������ ���� �Ұ��Դϴ�. �ݴ�δ� �Ĺ� �ҰŰ� �ֽ��ϴ�.
			for (int nextRow = row + 1; nextRow < 4; ++nextRow)
			{
				// �̹� ���� ��Ұ� 0�̶�� ������� �ʿ䰡 �����ϴ�.
				if (mat.getElement(nextRow, row) == 0.0f)
				{
					continue;
				}

				// ������ ���� ���� ��Ҹ� 0���� ����� ���� �����ִ� ���Դϴ�.
				// �̰��� �����ϴ� �� ������ �����ϴ�.
				//
				// �� �� �Ǵ� �� ���� � ���ڸ� ���ؼ� �ٸ� �� �Ǵ� ���� ���ϰų� ����
				// ��Ľ��� ���� �ٲ��� �ʾƿ�. ���⼭ �����ؾ� �� �� ���� �ೢ�� ���� ������ ���߱�!
				// ���� ��� row�� ��� ��ҿ� � ���ڸ� ���ؼ� nextRow�� ��� ��Ҹ� ���ϰų� ����
				// ��Ľ��� ���� �״�ζ�� �ſ���. �׷��� ��ﰢ����� ����� ���ؼ���
				// ���� ��Ҹ� 0���� ������ �ϹǷ� ���� ��Ҹ�ŭ ����� �մϴ�.
				// �������ڸ� nextRow�� ���� ��Ұ� 0�� �Ƿ��� �� ���� ��Ҹ�ŭ ���ָ� �˴ϴ�.
				// �׷��� row�� ���� ����� ���� ������ �� �����Ƿ� ���ߴ� �� �ٽ� �����ִ� ����.
				// ��, (nextRow�� ��� - row�� ��� * nextRow�� ���� ��� / row�� ���� ���) �̷��� �˴ϴ�.
				//
				// �� �̷� ���� �ϳĸ� ��ﰢ����� ����� ���� ���� ���� ���� ��Ҹ�
				// 0���� ������ַ��� �ϴ� �ſ���.
				float rZeroBase = mat.getElement(nextRow, row) / mat.getElement(row, row);

				// nextRow�� ��� ��ҿ� rZeroBase�� �����մϴ�.
				// ���⼭�� ���� �̵��ؾ� �ϹǷ� col�̶�� ������ ���� ����ҰԿ�.
				// ��ﰢ����� ����� �������� ���� ����� ���� ��Ҵ� �̹� 0�̹Ƿ� �Ű� ���� �ʾƵ� �ſ�.
				for (int col = row; col < 4; ++col)
				{
					float rTemp = mat.getElement(nextRow, col) - mat.getElement(row, col) * rZeroBase;
					mat.setElement(nextRow, col, rTemp);
				}
			}
		}

		float rSign = rDet;

		// ������� ���� ��ﰢ����� ������� �����̹Ƿ�
		// �밢 ��Ҹ� �����ָ� �װ� �� ��Ľ��� ���� �˴ϴ�.
		// �ݺ����� ����ص� ������ �� �� �ڼ��� �Ẽ�Կ�.
		rDet = rDet * mat.getElement(0, 0) * mat.getElement(1, 1)
			* mat.getElement(2, 2) * mat.getElement(3, 3);

		// ��ﰢ����� ����غ��ϴ�.
		printf("mat�� ��ﰢ����Դϴ�.\n");
		printf("-----------------------------------\n");
		mat.ShowElement();
		printf("-----------------------------------\n");
		printf("��Ľ� ��� : %.2f * %.2f * %.2f * %.2f * %.2f\n",
			rSign, mat.getElement(0, 0), mat.getElement(1, 1),
			mat.getElement(2, 2), mat.getElement(3, 3));
		printf("-----------------------------------\n");

		return rDet;
	}

	void SwapRow(int firstRow, int secondRow)
	{
		// ���� ���� ��Ҹ� ����մϴ�.
		// Swap�� �⺻�� �������.
		float rTemp[4] = { 0.0f, 0.0f, 0.0f, 0.0f };
		for (int i = 0; i < 4; ++i)
		{
			rTemp[i] = getElement(firstRow, i);
		}

		// ���� �࿡ Swap�� ���� ��Ҹ� �����մϴ�.
		for (int i = 0; i < 4; ++i)
		{
			float rSecondRowElement = getElement(secondRow, i);
			setElement(firstRow, i, rSecondRowElement);
		}

		// Swap�� �࿡ ���� ���� ��Ҹ� �����մϴ�.
		for (int i = 0; i < 4; ++i)
		{
			setElement(secondRow, i, rTemp[i]);
		}
	}

	// ���ſ��� ����� ����б� ������ ���ԵǾ��־ �׳� ������ �ܿ�����
	// ���б� �������� �ö���鼭 ������ �����ϴ� ������� �˷��ݴϴ�.
	// ������� ��Ľ��� ���� * ��������Դϴ�.
	// ��, ��Ľ��� 0�̶�� ������� ���ǵ��� �ʰ�, ��Ľ��� �־�� �ϹǷ� ������ĸ� �ش�˴ϴ�.
	// ��������� ó�� ���� ������ٵ� �����ڷ� �̷���� ����� ��ġ����� ��������̶�� �ؿ�.
	// ���� ��Ľĸ� �˰� ������ ������ĸ� ���� �����ϸ� �ǰ���?
	Matrix4X4* Inverse()
	{
		// ������� �����ϴ��� ��Ľ����� �Ǵ��غ��ϴ�.
		float rDet = CalcDeterminantByLE(); // ���� ������ ���콺 �ҰŹ��� ����ص� �˴ϴ�.
		
		if (rDet == 0.0f) // �Ǽ��� ==���� ���� �� ������ 0�� �����Դϴ�.
		{
			printf("������� �������� �ʽ��ϴ�! (Det = %.2f)\n", rDet);
			printf("-----------------------------------\n");
			return nullptr;
		}

		// ��Ľ��� ���� 0�� �ƴ϶�� ������� �����ϴ� ���̹Ƿ�
		// �����ڸ� �� ���� �ڿ� ��ġ���Ѽ� ������ķ� ������ݴϴ�.
		// ������ �۾��� ��� �ݺ��ǹǷ� �Լ��� ��� ó���ҰԿ�.
		Matrix4X4 matTemp;

		/////////////////////////////////////////////////////////////////
		// 1�� ����
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
		// 2�� ����
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
		// 3�� ����
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
		// 4�� ����
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
		printf("     1��     2��     3��     4��\n");
		printf("1�� %6.2f  %6.2f  %6.2f  %6.2f\n", m_r00, m_r01, m_r02, m_r03);
		printf("2�� %6.2f  %6.2f  %6.2f  %6.2f\n", m_r10, m_r11, m_r12, m_r13);
		printf("3�� %6.2f  %6.2f  %6.2f  %6.2f\n", m_r20, m_r21, m_r22, m_r23);
		printf("4�� %6.2f  %6.2f  %6.2f  %6.2f\n", m_r30, m_r31, m_r32, m_r33);

		// ���� ���� �̴ϴ�.
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
			printf("��� ���� ������ �����ּ���!\n");
			printf("��� ���� (0, 0) ~ (3, 3) => ����(%d, %d)\n", row, col);
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
			printf("��� ���� ������ �����ּ���!\n");
			printf("��� ���� (0, 0) ~ (3, 3) => ����(%d, %d)\n", row, col);
			return;
		}

		m_rElement[row][col] = rVal;
	}

	// ������ �����ε��� ���� ���μ��� �ٿ����ϴ�.
	// ������ �����Ѵٸ� �ڵ带 ��Ȱ���� �� �ֽ��ϴ�.

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
	// �迭�� �� ��ҷ� �����ϴ� ����� �����ϱ� ���� ����ü�� ����մϴ�.
	union
	{
		struct // 4 X 4 X 4 = 64����Ʈ
		{
			float m_r00, m_r01, m_r02, m_r03;
			float m_r10, m_r11, m_r12, m_r13;
			float m_r20, m_r21, m_r22, m_r23;
			float m_r30, m_r31, m_r32, m_r33;
		};

		float m_rElement[4][4]; // 4 X 4 X 4 = 64����Ʈ
	};
};

int main()
{
	printf("4�� 4�� ����� ������� ���غ��ϴ�.\n\n");
	printf("mat\n");
	printf("-----------------------------------\n");
	Matrix4X4 mat( 1.0f,  1.0f,  1.0f, -1.0f,
		           1.0f,  1.0f, -1.0f,  1.0f,
		           1.0f, -1.0f,  1.0f,  1.0f,
		          -1.0f,  1.0f,  1.0f,  1.0f);
	mat.ShowElement();
	printf("-----------------------------------\n\n");

	/////////////////////////////////////////////////////////////////
	printf("mat�� ������� ���մϴ�.\n");
	printf("-----------------------------------\n");
	mat.Inverse();
	mat.ShowElement();
	printf("-----------------------------------\n\n");
	/////////////////////////////////////////////////////////////////
	printf("������� ������� ��������Դϴ�.\n");
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
	printf("mat�� 1���� 0���� �ٲ� ���� ������� ���մϴ�.\n");
	printf("-----------------------------------\n");
	mat.Inverse();
	mat.ShowElement();
	printf("-----------------------------------\n\n");
	/////////////////////////////////////////////////////////////////

	_getch();
	return 0;
}