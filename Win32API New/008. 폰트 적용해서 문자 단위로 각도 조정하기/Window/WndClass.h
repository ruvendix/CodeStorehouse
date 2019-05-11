// =====================================================================================
// Copyright(c) 2019, Ruvendix. All Rights Reserved.
// 
// �� ���۹��� ũ������Ƽ�� Ŀ���� ������ǥ�� 4.0 ���� ���̼����� ���� �̿��� �� �ֽ��ϴ�.
// http://creativecommons.org/licenses/by/4.0/
// =====================================================================================

// �ߺ� ���� �������Դϴ�.
// #pragma once�� ������ #define Guarder�� ����մϴ�.
#ifndef WND_CLASS_H
#define WND_CLASS_H

// ���� ����� ����մϴ�.
#include "Common/Common.h"

/*
	������ Ŭ���� ���� �� �������Դϴ�.
*/
class RXWndClass
{
public:
	RXWndClass() = default;
	virtual ~RXWndClass() = default;

	HRESULT Init(const std::wstring& szWndClass);
	HRESULT RegisterWndClass();

	// ============================================================
	// Setter
	void setWindowClassName(const std::wstring& szWndClass)
	{
		m_szWndClass = szWndClass;
		m_wcex.lpszClassName = m_szWndClass.c_str();
	}

private:
	// RXWndClass �������ν�, �ܺο� �������� �ʽ��ϴ�.
	static LRESULT CALLBACK WndProcedure(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

	WNDCLASSEX   m_wcex;       // ������ Ŭ���� �����Դϴ�.
	std::wstring m_szWndClass; // ������ Ŭ���� �̸��Դϴ�.
};

#endif