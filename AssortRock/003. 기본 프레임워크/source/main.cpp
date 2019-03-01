#include "main.h"
#include "global_instance\misc\RXCore.h"
#include "global_instance\misc\RXPerformanceProfiler.h"

void Test_BubbleSort();
void Test_SelectionSort();
void Test_InsertionSort();

INT32 APIENTRY _tWinMain(
	HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	LPTSTR    szCmdLine,
	INT32     cmdShow)
{
	//_CrtSetBreakAlloc(418);

	UNREFERENCED_PARAMETER(hInstance);
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(szCmdLine);
	UNREFERENCED_PARAMETER(cmdShow);

	RXCORE->OnDrive();

	Test_BubbleSort();
	Test_BubbleSort();

	Test_SelectionSort();
	Test_SelectionSort();
	Test_SelectionSort();

	Test_InsertionSort();

	return RXCORE->getMessageCode();
}

void Test_BubbleSort()
{
	PERFORMANCE_PROFILER_START();

	INT32 arr[] = { 9, 1, 6, 2, 8, 3, 5, 4, 7 };
	INT32 arrSize = _countof(arr);
	for (INT32 i = 0; i < arrSize - 1; ++i)
	{
		for (INT32 j = 0; j < (arrSize - 1) - i; ++j)
		{
			if (arr[j] > arr[j + 1])
			{
				INT32 temp = arr[j];
				arr[j] = arr[j + 1];
				arr[j + 1] = temp;
			}
		}
	}

	PERFORMANCE_PROFILER_END();
}

void Test_SelectionSort()
{
	PERFORMANCE_PROFILER_START();

	INT32 arr[] = { 9, 1, 6, 2, 8, 3, 5, 4, 7 };
	INT32 arrSize = _countof(arr);
	for (INT32 i = 0; i < arrSize - 1; ++i)
	{
		INT32 minIdx = i;
		for (INT32 j = i + 1; j < arrSize; ++j)
		{
			if (arr[minIdx] > arr[j])
			{
				minIdx = j;
			}
		}

		INT32 temp = arr[i];
		arr[i] = arr[minIdx];
		arr[minIdx] = temp;
	}

	PERFORMANCE_PROFILER_END();
}

void Test_InsertionSort()
{
	PERFORMANCE_PROFILER_START();

	INT32 arr[] = { 9, 1, 6, 2, 8, 3, 5, 4, 7 };
	INT32 arrSize = _countof(arr);
	for (INT32 i = 1; i < arrSize; ++i)
	{
		INT32 backup = arr[i];
		INT32 j = 0;
		for (j = i - 1; j >= 0; --j)
		{
			if (backup < arr[j])
			{
				arr[j + 1] = arr[j];
			}
			else
			{
				break;
			}
		}

		arr[j + 1] = backup;
	}

	PERFORMANCE_PROFILER_END();
}