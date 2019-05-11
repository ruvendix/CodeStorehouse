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

#endif