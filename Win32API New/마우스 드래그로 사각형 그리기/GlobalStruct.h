// =====================================================================================
// Copyright(c) 2019, Ruvendix. All Rights Reserved.
// 
// �� ���۹��� ũ������Ƽ�� Ŀ���� ������ǥ�� 4.0 ���� ���̼����� ���� �̿��� �� �ֽ��ϴ�.
// http://creativecommons.org/licenses/by/4.0/
// =====================================================================================

// �ߺ� ���� �������Դϴ�.
// #pragma once�� ������ #define Guarder�� ����մϴ�.
#ifndef GLOBAL_STRUCT_H_
#define GLOBAL_STRUCT_H_

// ǥ�� ����� ����մϴ�.
#include "Standard.h"

/*
	���� ����ü �����Դϴ�.
	����ü�� POD(Plain Old Data) ���ַ� �����մϴ�.
	���� POD�� �ƴ� ���� �ֽ��ϴ�.
*/

// 2D ��ǥ������ ��ġ�Դϴ�. �ٿ��� ��ġ�� ǥ���մϴ�.
// ����� �ǹ̷δ� Vector 2D�� ������
// ���������� ����ϴ� �� �ƴϹǷ� �� �� ���������� ǥ���մϴ�.
struct PositionInfo
{
	INT32 x;
	INT32 y;
};

// �ػ� �����Դϴ�.
// �ػ󵵴� �ȼ� �Ǵ� ��Ʈ�� ���� �ǹ̰� ��������
// �Ϲ������δ� (���� X ����)�� �ǹ��մϴ�.
struct ResolutionInfo
{
	INT32 width;
	INT32 height;
};

// ������ ���� �����Դϴ�.
// ����� ��ġ�� �ػ� ������ �ֽ��ϴ�.
struct WndCreateInfo
{
	PositionInfo   posInfo;        // 2D ��ǥ
	ResolutionInfo resolutionInfo; // �ػ� ����
};

#endif