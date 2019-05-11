// =====================================================================================
// Copyright(c) 2019, Ruvendix. All Rights Reserved.
// 
// �� ���۹��� ũ������Ƽ�� Ŀ���� ������ǥ�� 4.0 ���� ���̼����� ���� �̿��� �� �ֽ��ϴ�.
// http://creativecommons.org/licenses/by/4.0/
// =====================================================================================

// �ߺ� ���� �������Դϴ�.
// #pragma once�� ������ #define Guarder�� ����մϴ�.
#ifndef MY_APP_H
#define MY_APP_H

// RXApp�� ����մϴ�.
#include "App.h"

// RXNewWnd�� ����մϴ�.
#include "NewWnd.h"

/*
	���� ��ƾ�� ����մϴ�.
*/
class RXMyApp : public RXApp
{
public:
	RXMyApp();
	RXMyApp(const std::wstring& szTitle, INT32 x, INT32 y, INT32 clientWidth, INT32 clientHeight);
	virtual ~RXMyApp();
	
	virtual HRESULT InitWndClass();
	virtual INT32   Run() override;

private:
	RXWndClass*   m_pWndClass;     // ������ Ŭ�����Դϴ�.
	RXWnd*        m_pWnd;          // �������Դϴ�.
	WndCreateInfo m_wndCreateInfo; // ������ ���� �����Դϴ�.
};

#endif