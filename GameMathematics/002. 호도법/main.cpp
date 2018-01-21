/*
 * <파일 설명>
 * 호도법을 확인해보는 예제입니다.
 * 호도법은 호의 길이에 따른 각도의 크기를 나타내는 방법입니다.
 * 일반각과 다른 개념이므로 헷갈리면 안 됩니다.
 * 프로그래밍에서는 일반각이 아니라 호도법을 사용합니다.
 * 따라서 일반각을 호도법으로 변환하는 방법을 반드시 알아둬야 합니다.
 */

// double에서 float으로 축소되는 것 허용
#pragma warning(disable : 4305)

#include <conio.h>   // CMD 입출력을 다루기 위한 헤더(비표준)
#include <windows.h> // CMD 확장 기능을 이용하기 위한 헤더(비표준)
#include <cstdio>    // CMD 입출력을 다루기 위한 헤더(표준)

#define _USE_MATH_DEFINES // 수학의 정의값을 사용하기 위한 매크로 상수
#include <cmath>          // 수학을 다루기 위한 헤더(표준)

int main()
{
	// 1라디안(Radian, 줄여서 rad) 구하기
	// 비례식에 의해 r : Θ = 2πr : 360이 되고
	// 결과적으로 Θ = 180 / π이 됩니다.
	float rOneRadian = 180.0f / M_PI; // M_PI는 3.141592...
	printf("1라디안의 값 : %.4f\n\n", rOneRadian);

	// 반지름이 1일 때는 Θ가 곧 호의 길이 비율이 됩니다.
	// 반지름이 1로 고정되어도 호의 길이는 변할 수 있기 때문이죠.
	// 따라서 반원일 때의 호의 길이는 그때의 각도와 비율이 같다고 할 수 있어요.
	// 호의 길이 : Θ = π : 180 => πΘ = 180 X 호의 길이
	// Θ가 곧 호의 길이 비율이므로 π는 180 rad가 됩니다.
	// 이걸 이용하면 60분법과 호도법 변환이 가능해집니다.
	
	float rDegree = 60.0f; // 60도는 180도의 3분의 1입니다.

	// 이제 π가 180 rad임을 이용하면 비례식을 만들 수 있습니다.
	// 60 : x rad = 180 : π rad => x rad = 60 * π * 1 / 180
	// 정리하면 x rad = 60 * (π / 180)
	// 따라서 각도를 호도법으로 변환하는 공식은 (π / 180) 이렇게 되고
	// 호도법을 각도로 변환하는 공식은 (180 / π) 이렇게 됩니다.
	// 외우는 게 아니라 비례식으로 만들어지는 공식임을 알아두세요.

	float rRadian = rDegree * (M_PI / 180.0f);
	printf("60도 => %.4f rad\n", rRadian);

	float rNewDegree = rRadian * (180.0f / M_PI);
	printf("%.4f rad => %.f도\n", rRadian, rNewDegree);

	_getch();
	return 0;
}