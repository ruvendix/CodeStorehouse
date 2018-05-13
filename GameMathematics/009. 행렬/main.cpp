/*
 * <���� ����>
 * ����� ���Ǹ� Ȯ���غ��� �����Դϴ�.
 * ����� ����б� ������ �ƴϹǷ� �ڼ��ϰ� �����Ϸ��� �մϴ�.
 * ���� ���α׷��ֿ��� ����� �ʼ� �����̹Ƿ� �ݵ�� �˾ƾ� �մϴ�.
 * �������� ����� ����б� �����̾��µ� ��� ������ ���б� �������� �Ѿ������.
 * �׷��� ������ ��ģ�������µ�... ���п� ��Ŀ� �����ϱⰡ ����������ϴ�.
 * ����� �ƿ� �𸥴ٰ� ������ �� ���¿��� �����ҰԿ�.
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

		//// ���� ���� �̴ϴ�.
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
		printf("    1��   2��   3��   4��\n");
		printf("1�� %.2f  %.2f  %.2f  %.2f\n", m_r00, m_r01, m_r02, m_r03);
		printf("2�� %.2f  %.2f  %.2f  %.2f\n", m_r10, m_r11, m_r12, m_r13);
		printf("3�� %.2f  %.2f  %.2f  %.2f\n", m_r20, m_r21, m_r22, m_r23);
		printf("4�� %.2f  %.2f  %.2f  %.2f\n", m_r30, m_r31, m_r32, m_r33);

		// ���� ���� �̴ϴ�.
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
	printf("4�� 4���� ��İ��� ����մϴ�.\n");
	printf("----------------------------\n");

	Matrix4X4 mat; // ����� ���ڷ� mat�̶� ǥ���մϴ�.
	mat.ShowElement();

	printf("----------------------------\n\n");

	///////////////////////////////////////////////////////////////

	// ��İ��� �����մϴ�.
	// 1��
	mat.setElement(0, 0, 1.0f);
	mat.setElement(0, 1, 2.0f);
	mat.setElement(0, 2, 3.0f);
	mat.setElement(0, 3, 4.0f);

	// 2��
	mat.setElement(1, 0, 5.0f);
	mat.setElement(1, 1, 6.0f);
	mat.setElement(1, 2, 7.0f);
	mat.setElement(1, 3, 8.0f);

	// 3��
	mat.setElement(2, 0, 9.0f);
	mat.setElement(2, 1, 8.0f);
	mat.setElement(2, 2, 7.0f);
	mat.setElement(2, 3, 6.0f);

	// 4��
	mat.setElement(3, 0, 5.0f);
	mat.setElement(3, 1, 4.0f);
	mat.setElement(3, 2, 3.0f);
	mat.setElement(3, 3, 2.0f);

	printf("4�� 4���� ��İ��� ����մϴ�.\n");
	printf("----------------------------\n");
	mat.ShowElement();
	printf("----------------------------\n");

	_getch();
	return 0;
}