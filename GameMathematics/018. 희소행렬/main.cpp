/*
 * <파일 설명>
 * 희소행렬을 알아보는 예제입니다.
 * 게임에도 희소행렬을 적용하면 메모리를 절약할 수 있다는 장점이 있지만
 * 실제로 사용되는 곳은 많지 않아요. 4X4 행렬에는 별로 쓸모가 없으니까요.
 * 하지만 어떤 맵을 각 구역별로 나누고 희소행렬에 적용할 때는 최적화 효과가 있습니다.
 * 여기서는 희소행렬을 std::map으로 구현해보는 것만 해볼게요.
 */

// double에서 float으로 축소되는 것 허용
#pragma warning(disable : 4305)

#include <conio.h>   // CMD 입출력을 다루기 위한 헤더(비표준)
#include <windows.h> // CMD 확장 기능을 이용하기 위한 헤더(비표준)
#include <cstdio>    // CMD 입출력을 다루기 위한 헤더(표준)
#include <cmath>     // 수학을 다루기 위한 헤더(표준)
#include <cfloat>    // 실수를 다루기 위한 헤더(표준)
#include <map>       // std::map을 다루기 위한 헤더(표준)

// 희소행렬의 행과 열 정보
struct SparseMatrixInfo
{
	int row;
	int col;
};

// std::map이 내부적으로 연산자를 이용하려면
// 자료형 내부가 아니라 외부에 정의해줘야 합니다.
// std::map은 내부적으로 < 연산자를 이용하는데
// 여기에 맞는 3가지 법칙을 적용해서 구현해주면 됩니다.
// 반대칭적(Antisymmetric), 추이적(Transitive), 비반사적(Irreflexive)
// 이렇게 3개가 있는데 여기에서는 반대칭적만 적용할게요.
bool operator< (const SparseMatrixInfo& lhs, const SparseMatrixInfo& rhs)
{
	// 반대칭적(Antisymmetric)
	// A < B가 true면
	// A > B는 flase여야 합니다.
	// if ~ else의 관계가 아니라 if로 분리해야 합니다.

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

// 희소행렬(Sparse Matrix)
// 편의를 위해 정방행렬에만 적용합니다.
// 값이 없는 상태는 0으로 인식됩니다.
// 행과 열에 이미 값이 존재한다면 새로운 값으로 덮어씌웁니다.
class SparseMatrix
{
public:
	// 기본 범위는 4X4 행렬입니다.
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
			printf("범위를 벗어났습니다! (0, 0) ~ (%d, %d)\n", m_sparseInfo.row, m_sparseInfo.col);
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
			printf("해당 위치에 이미 값이 존재하므로 새로 덮어씌웁니다.\n");
			printf("(%d, %d)의 %.2f가 %.2f로 대체됩니다.\n", row, col, i->second, rValue);
			m_mapMatSparse.erase(i);
		}
		else
		{
			printf("새로운 값을 삽입합니다! (%d, %d) <= %.2f\n", row, col, rValue);
		}

		m_mapMatSparse.insert(std::make_pair(info, rValue)); // 새로운 행과 열에 데이터 넣기
	}

	float FindValue(int row, int col, bool bGuide = true) // 예제니까 기본 인자를 쓸게요
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
			printf("해당 행과 열에 값이 없으므로 0을 반환합니다.\n");
		}

		return 0.0f; // 값이 없으면 0을 반환하는 게 바로 희소행렬입니다.
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
	SparseMatrixInfo m_sparseInfo; // 정방행렬의 범위를 저장하기 위한 변수
};


int main()
{
	printf("희소행렬을 확인해보는 예제입니다.\n\n");

	SparseMatrix sparseMatrix4X4;
	printf("sparseMatrix4X4\n");
	printf("-------------------------------\n");
	sparseMatrix4X4.ShowElement();
	printf("-------------------------------\n\n");

	sparseMatrix4X4.Insert(1, 2, 5.0f);
	
	float rValue = 0.0f;

	rValue = sparseMatrix4X4.FindValue(1, 2);
	printf("찾은 값 => %.2f\n\n", rValue);

	rValue = sparseMatrix4X4.FindValue(1, 3);
	printf("찾은 값 => %.2f\n\n", rValue);

	rValue = sparseMatrix4X4.FindValue(1, 4);
	printf("찾은 값 => %.2f\n\n", rValue);

	printf("sparseMatrix4X4\n");
	printf("-------------------------------\n");
	sparseMatrix4X4.ShowElement();
	printf("-------------------------------\n\n");

	_getch();
	return 0;
}