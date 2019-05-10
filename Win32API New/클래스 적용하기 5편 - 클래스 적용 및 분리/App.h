// =====================================================================================
// Copyright(c) 2019, Ruvendix. All Rights Reserved.
// 
// �� ���۹��� ũ������Ƽ�� Ŀ���� ������ǥ�� 4.0 ���� ���̼����� ���� �̿��� �� �ֽ��ϴ�.
// http://creativecommons.org/licenses/by/4.0/
// =====================================================================================

// �ߺ� ���� �������Դϴ�.
// #pragma once�� ������ #define Guarder�� ����մϴ�.
#ifndef APP_H
#define APP_H

// RXWindow�� ����մϴ�.
#include "Wnd.h"

// RXWindowClass�� ����մϴ�.
#include "WndClass.h"

/*
	���α׷��� ���� ��ƾ�� ����մϴ�.
	�߻� Ŭ�����̹Ƿ� ����� �ʼ��Դϴ�.
*/
class RXApp
{
public:
	RXApp() = default;
	virtual ~RXApp() = default;

	virtual INT32 Run() = 0;
};

#endif