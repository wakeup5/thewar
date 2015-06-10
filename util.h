#pragma once

#include <cmath>

#define DEG_TO_RAD		180 / M_PI

#define FLOAT_EPSILON	0.001f									//플룻 엡실론
#define FLOAT_TO_INT(f1) static_cast<int>(f1 * FLOAT_EPSILON)	//실수를 정수형으로 변환한다
#define FLOAT_EQUAL(f1, f2) (fabs(f1 - f2) <= FLOAT_EPSILON)
//fabs는 소수점 차의 절대값을 반환한다

namespace myUtil
{
	/// 두개의 좌표를 받아 엇각?을 반환
	float getAngleByTwoPoint(float startX, float startY, float endX, float endY);

	/// 두개의 좌표 사이의 거리를 반환
	float getDistanceByTwoPoint(float startX, float startY, float endX, float endY);

	/// 두개의 좌표를 받아 기울기의 라디안 각도를 반환
	float getGradeRadianByTwoPoint(float x1, float y1, float x2, float y2);
}