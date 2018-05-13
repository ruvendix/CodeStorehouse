/*
 * <���� ����>
 * ��İ� ����� ������ Ȯ���غ��� �����Դϴ�.
 * �Ϲ����� ������ ������ �ٸ����� ������ ������ �˰� ������ ���� ���صǽ� �ſ���.
 * ���� ����� �ǰ� �̻��ѵ� ����� ������ �׷��� �����߱� ������ �״�� �޾Ƶ鿩�� �մϴ�.
 * 2 * 3�� 2 + 2 + 2��� ���������� Ǯ� �� ����? ����� ������ *�� �̿��� ���������� Ǯ��ϴ�.
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
		if ( (row < 0) ||
			 (row > 4 - 1) ||
			 (col < 0) ||
			 (col > 4 - 1) )
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
		if ( (row < 0) ||
			 (row > 4 - 1) ||
			 (col < 0) ||
			 (col > 4 - 1) )
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
	printf("4�� 4�� ��ĳ����� ������ Ȯ���غ��ϴ�.\n\n");
	printf("matFirst\n");
	printf("-----------------------------------\n");
	Matrix4X4 matFirst(5.0f, 2.0f, 6.0f, 1.0f,
                       0.0f, 6.0f, 2.0f, 0.0f,
                       3.0f, 8.0f, 1.0f, 4.0f,
                       1.0f, 8.0f, 5.0f, 6.0f);
	matFirst.ShowElement();
	printf("-----------------------------------\n\n");
	
	printf("matSecond\n");
	printf("-----------------------------------\n");
	Matrix4X4 matSecond(7.0f, 5.0f, 8.0f, 0.0f,
                        1.0f, 8.0f, 2.0f, 6.0f,
                        9.0f, 4.0f, 3.0f, 8.0f,
                        5.0f, 3.0f, 7.0f, 9.0f);
	matSecond.ShowElement();
	printf("-----------------------------------\n\n");

	Matrix4X4 matTemp = matFirst;
	Matrix4X4 matIdentity;
	matIdentity.Identity();

	/////////////////////////////////////////////////////////////////
	printf("matFirst�� ��������� ���մϴ�.\n");
	printf("-----------------------------------\n");
	matFirst.Multiply(matIdentity);
	matFirst.ShowElement();
	printf("-----------------------------------\n\n");
	/////////////////////////////////////////////////////////////////
	printf("matSecond�� ��������� ���մϴ�.\n");
	printf("-----------------------------------\n");
	matSecond.Multiply(matIdentity);
	matSecond.ShowElement();
	printf("-----------------------------------\n\n");
	/////////////////////////////////////////////////////////////////
	printf("matFirst�� matSecond�� ���մϴ�.\n");
	printf("-----------------------------------\n");
	matFirst.Multiply(matSecond);
	matFirst.ShowElement();
	printf("-----------------------------------\n\n");
	/////////////////////////////////////////////////////////////////
	printf("matSecond�� matFirst�� ���մϴ�.\n");
	printf("-----------------------------------\n");
	matFirst = matTemp;
	matTemp  = matSecond;
	matSecond.Multiply(matFirst);
	matSecond.ShowElement();
	printf("-----------------------------------\n\n");
	/////////////////////////////////////////////////////////////////
	printf("matTemp�� matFirst�� matSecond�� ���� ����� �����մϴ�.\n");
	printf("-----------------------------------\n");
	matSecond = matTemp;
	matTemp.Zero();
	matTemp = matFirst * matSecond;
	matTemp.ShowElement();
	printf("-----------------------------------\n\n");
	/////////////////////////////////////////////////////////////////
	printf("matTemp�� matSecond�� matFirst�� ���� ����� �����մϴ�.\n");
	printf("-----------------------------------\n");
	matTemp.Zero();
	matTemp = matSecond * matFirst;
	matTemp.ShowElement();
	printf("-----------------------------------\n\n");

	_getch();
	return 0;
}