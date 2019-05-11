// =====================================================================================
// Copyright(c) 2019, Ruvendix. All Rights Reserved.
// 
// �� ���۹��� ũ������Ƽ�� Ŀ���� ������ǥ�� 4.0 ���� ���̼����� ���� �̿��� �� �ֽ��ϴ�.
// http://creativecommons.org/licenses/by/4.0/
// =====================================================================================

// �ߺ� ���� �������Դϴ�.
// #pragma once�� ������ #define Guarder�� ����մϴ�.
#ifndef MACRO_H_
#define MACRO_H_

// �⺻ �޽��� �ڽ��Դϴ�.
#define MSGBOX(szContents) (::MessageBox(::GetDesktopWindow(), szContents, L"�޽��� �ڽ�", MB_OK))

// ���� �޽��� �ڽ��Դϴ�.
#define ERRMSGBOX(szError) (::MessageBox(::GetDesktopWindow(), szError, L"����", MB_OK))

// ����ü�� ������� size_t�� ��ȯ�մϴ�.
#define NUM(enumValue)           static_cast<size_t>(enumValue)

// �������� ����ü�� ��������� ��ȯ�մϴ�.
#define ENUM(enumType, intValue) static_cast<enumType>(intValue)

// ����� ��忡�� �޸� ���� ��� �����Դϴ�.
#define RXNew new(_NORMAL_BLOCK, __FILE__, __LINE__)

// �����Ҵ�� �����͸� �����ϰ� nullptr�� ����ϴ�.
#define SAFE_DELETE(ptr)\
	if (ptr != nullptr)\
	{\
		delete ptr;\
		ptr = nullptr;\
	}

#endif