/*
 * <���� ����>
 * �������� �˾ƺ��� �����Դϴ�.
 * ���ӿ��� �������� �����ϸ� �޸𸮸� ������ �� �ִٴ� ������ ������
 * ������ ���Ǵ� ���� ���� �ʾƿ�. 4X4 ��Ŀ��� ���� ���� �����ϱ��.
 * ������ � ���� �� �������� ������ �����Ŀ� ������ ���� ����ȭ ȿ���� �ֽ��ϴ�.
 * ���⼭�� �������� std::map���� �����غ��� �͸� �غ��Կ�.
 */

// double���� float���� ��ҵǴ� �� ���
#pragma warning(disable : 4305)

#include <conio.h>   // CMD ������� �ٷ�� ���� ���(��ǥ��)
#include <windows.h> // CMD Ȯ�� ����� �̿��ϱ� ���� ���(��ǥ��)
#include <cstdio>    // CMD ������� �ٷ�� ���� ���(ǥ��)
#include <cmath>     // ������ �ٷ�� ���� ���(ǥ��)
#include <cfloat>    // �Ǽ��� �ٷ�� ���� ���(ǥ��)
#include <map>       // std::map�� �ٷ�� ���� ���(ǥ��)

// �������� ��� �� ����
struct SparseMatrixInfo
{
	int row;
	int col;
};

// std::map�� ���������� �����ڸ� �̿��Ϸ���
// �ڷ��� ���ΰ� �ƴ϶� �ܺο� ��������� �մϴ�.
// std::map�� ���������� < �����ڸ� �̿��ϴµ�
// ���⿡ �´� 3���� ��Ģ�� �����ؼ� �������ָ� �˴ϴ�.
// �ݴ�Ī��(Antisymmetric), ������(Transitive), ��ݻ���(Irreflexive)
// �̷��� 3���� �ִµ� ���⿡���� �ݴ�Ī���� �����ҰԿ�.
bool operator< (const SparseMatrixInfo& lhs, const SparseMatrixInfo& rhs)
{
	// �ݴ�Ī��(Antisymmetric)
	// A < B�� true��
	// A > B�� flase���� �մϴ�.
	// if ~ else�� ���谡 �ƴ϶� if�� �и��ؾ� �մϴ�.

	if (lhs.row < rhs.row)
	{
		return true;
	}

	if (lhs.row > rhs.row)
	{
		return false;
	}

	if (lhs.col < rhs.col)
	{
		return true;
	}

	return false;
}

// ������(Sparse Matrix)
// ���Ǹ� ���� ������Ŀ��� �����մϴ�.
// ���� ���� ���´� 0���� �νĵ˴ϴ�.
// ��� ���� �̹� ���� �����Ѵٸ� ���ο� ������ �����ϴ�.
class SparseMatrix
{
public:
	// �⺻ ������ 4X4 ����Դϴ�.
	SparseMatrix()
	{
		m_sparseInfo.row = 4;
		m_sparseInfo.col = 4;
	}

	SparseMatrix(int row)
	{
		m_sparseInfo.row = row;
		m_sparseInfo.col = row;
	}

	~SparseMatrix() = default;

	bool IsValidInfo(int row, int col)
	{
		if ( (row < 0) ||
			 (col < 0) ||
			 (row > m_sparseInfo.row - 1) ||
			 (col > m_sparseInfo.col - 1) )
		{
			printf("������ ������ϴ�! (0, 0) ~ (%d, %d)\n", m_sparseInfo.row, m_sparseInfo.col);
			return false;
		}

		return true;
	}

	void Insert(int row, int col, float rValue)
	{
		if (IsValidInfo(row, col) == false)
		{
			return;
		}

		SparseMatrixInfo info = { row, col };
		std::map<SparseMatrixInfo, float>::iterator i = m_mapMatSparse.find(info);

		if (i != m_mapMatSparse.end())
		{
			printf("�ش� ��ġ�� �̹� ���� �����ϹǷ� ���� �����ϴ�.\n");
			printf("(%d, %d)�� %.2f�� %.2f�� ��ü�˴ϴ�.\n", row, col, i->second, rValue);
			m_mapMatSparse.erase(i);
		}
		else
		{
			printf("���ο� ���� �����մϴ�! (%d, %d) <= %.2f\n", row, col, rValue);
		}

		m_mapMatSparse.insert(std::make_pair(info, rValue)); // ���ο� ��� ���� ������ �ֱ�
	}

	float FindValue(int row, int col, bool bGuide = true) // �����ϱ� �⺻ ���ڸ� ���Կ�
	{
		if (IsValidInfo(row, col) == false)
		{
			return 0.0f;
		}

		SparseMatrixInfo info = { row, col };
		std::map<SparseMatrixInfo, float>::iterator i = m_mapMatSparse.find(info);

		if (i != m_mapMatSparse.end())
		{
			return i->second;
		}

		if (bGuide)
		{
			printf("�ش� ��� ���� ���� �����Ƿ� 0�� ��ȯ�մϴ�.\n");
		}

		return 0.0f; // ���� ������ 0�� ��ȯ�ϴ� �� �ٷ� �������Դϴ�.
	}

	void ShowElement()
	{
		for (int row = 0; row < m_sparseInfo.row; ++row)
		{
			for (int col = 0; col < m_sparseInfo.col; ++col)
			{
				float rValue = FindValue(row, col, false);
				printf("%.2f\t", rValue);
			}

			printf("\n");
		}
	}
	
private:
	std::map<SparseMatrixInfo, float> m_mapMatSparse;
	SparseMatrixInfo m_sparseInfo; // ��������� ������ �����ϱ� ���� ����
};


int main()
{
	printf("�������� Ȯ���غ��� �����Դϴ�.\n\n");

	SparseMatrix sparseMatrix4X4;
	printf("sparseMatrix4X4\n");
	printf("-------------------------------\n");
	sparseMatrix4X4.ShowElement();
	printf("-------------------------------\n\n");

	sparseMatrix4X4.Insert(1, 2, 5.0f);
	
	float rValue = 0.0f;

	rValue = sparseMatrix4X4.FindValue(1, 2);
	printf("ã�� �� => %.2f\n\n", rValue);

	rValue = sparseMatrix4X4.FindValue(1, 3);
	printf("ã�� �� => %.2f\n\n", rValue);

	rValue = sparseMatrix4X4.FindValue(1, 4);
	printf("ã�� �� => %.2f\n\n", rValue);

	printf("sparseMatrix4X4\n");
	printf("-------------------------------\n");
	sparseMatrix4X4.ShowElement();
	printf("-------------------------------\n\n");

	_getch();
	return 0;
}