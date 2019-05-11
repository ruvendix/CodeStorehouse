// =====================================================================================
// Copyright(c) 2019, Ruvendix. All Rights Reserved.
// 
// �� ���۹��� ũ������Ƽ�� Ŀ���� ������ǥ�� 4.0 ���� ���̼����� ���� �̿��� �� �ֽ��ϴ�.
// http://creativecommons.org/licenses/by/4.0/
// =====================================================================================

// �ߺ� ���� �������Դϴ�.
// #pragma once�� ������ #define Guarder�� ����մϴ�.
#ifndef WND_H_
#define WND_H_

// ���� ����� ����մϴ�.
#include "Common.h"

/*
	������ ���� �� �������Դϴ�.
*/
class RXWnd
{
public:
	RXWnd(const std::wstring& szWndTtile);
	virtual ~RXWnd() = default;

	// ======================================================================
	// �޽��� �ڵ鷯�Դϴ�.
	virtual BOOL OnCreate(HWND hWnd, CREATESTRUCT* pCreateStruct);
	virtual void OnDestroy(HWND hWnd);

	// ======================================================================
	// ������ �����Դϴ�.
	HRESULT Create(INT32 x, INT32 y, INT32 clientWidth, INT32 clientHeight, DWORD dwStyle); // �⺻���Դϴ�.

protected:
	std::wstring m_szWndTitle; // ������ �̸��Դϴ�.
	HWND         m_hWnd;       // ������ �ڵ��Դϴ�.
};

#endif