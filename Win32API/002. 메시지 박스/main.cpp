/*
 * <���� ����>
 * �޽��� �ڽ� �׽�Ʈ ���α׷��Դϴ�.
 * �޽��� �ڽ��� ����ڿ��� ���� ���α׷��� ��Ȳ�� �˷��� �� ����մϴ�.
 * �ַ� ������ ��������� ������ �� ����մϴ�.
 */

#include <cstdio>  // snprintf()�� ����ϱ� ���� ���Խ�ŵ�ϴ�.
#include <cstdlib> // _countof ��ũ�θ� ����ϱ� ���� ���Խ�ŵ�ϴ�. �迭�� ������ �����ִ� ��ũ�� �Լ��Դϴ�.

// ������ ��� ���Ͽ��� �ּҷ� �ʿ�� �ϴ� �͵鸸 ���Խ�ŵ�ϴ�.
#ifdef WIN32_LEAN_AND_MEAN
#include <windows.h>
#else
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#undef  WIN32_LEAN_AND_MEAN
#endif

struct MessageBoxStyleInfo
{
	INT32  styleValue;
	LPCSTR strStyleGuide;
};

INT32 main()
{
	MessageBoxStyleInfo messageBoxStyleInfoTable[] =
	{
        { MB_OK,                "Ȯ��" },
        { MB_OKCANCEL,          "Ȯ�� | ���" },
        { MB_ABORTRETRYIGNORE,  "�ߴ� | �ٽ� �õ� | ����" },
        { MB_YESNO,             "�� | �ƴϿ�" },
        { MB_YESNOCANCEL,       "�� | �ƴϿ� | ���" },
        { MB_RETRYCANCEL,       "�ٽ� �õ� | ���" },
        { MB_CANCELTRYCONTINUE, "��� | �ٽ� �õ� | ���" },
        { MB_HELP,              "Ȯ�� | ����" },
        { MB_USERICON,          "����� ���� ������ | Ȯ��" },
        { MB_ICONQUESTION,      "����ǥ ������ | Ȯ��" },
        { MB_ICONERROR,         "���� ������ | Ȯ��" },   // MB_ICONSTOP, MB_ICONERROR ����
        { MB_ICONWARNING,       "��� ������ | Ȯ��" },   // MB_ICONEXCLAMATION ����
        { MB_ICONINFORMATION,   "����ǥ ������ | Ȯ��" }, // MB_ICONASTERISK ����
        { MB_TOPMOST,           "�ֻ����� ��ġ(�ٸ� ������ �������� ����) | Ȯ��" },
        { MB_RIGHT,             "������ ���� | Ȯ��" },
        { MB_RTLREADING,        "�����ʿ��� ���� ����(�⺻ ��Ÿ���� �ݴ�) | Ȯ��" } // RTL => Right To Left
	};

	for (INT32 i = 0; i < _countof(messageBoxStyleInfoTable); ++i)
	{
		CHAR strStyleValue[256] = "";
		snprintf(strStyleValue, 256, "��Ÿ�ϰ� : %x\n", messageBoxStyleInfoTable[i].styleValue);

		CHAR strStyleGuide[256] = "";
		snprintf(strStyleGuide, 256, "��Ÿ�� �ȳ� : %s\n", messageBoxStyleInfoTable[i].strStyleGuide);

		CHAR strStyleContent[256] = "";
		strncat_s(strStyleContent, strStyleValue, 256);
		strncat_s(strStyleContent, strStyleGuide, 256);
		OutputDebugString(strStyleContent); // ���־� ��Ʃ��� ���â�� ���ڿ��� ������ݴϴ�.
		MessageBox(nullptr, strStyleContent, "�޽��� �ڽ� ĸ��", messageBoxStyleInfoTable[i].styleValue);
	}

	return 0;
}