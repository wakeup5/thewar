#pragma once

#include <cmath>

#define DEG_TO_RAD		180 / M_PI

#define FLOAT_EPSILON	0.001f									//�÷� ���Ƿ�
#define FLOAT_TO_INT(f1) static_cast<int>(f1 * FLOAT_EPSILON)	//�Ǽ��� ���������� ��ȯ�Ѵ�
#define FLOAT_EQUAL(f1, f2) (fabs(f1 - f2) <= FLOAT_EPSILON)
//fabs�� �Ҽ��� ���� ���밪�� ��ȯ�Ѵ�

namespace myUtil
{
	/// �ΰ��� ��ǥ�� �޾� ����?�� ��ȯ
	float getAngleByTwoPoint(float startX, float startY, float endX, float endY);

	/// �ΰ��� ��ǥ ������ �Ÿ��� ��ȯ
	float getDistanceByTwoPoint(float startX, float startY, float endX, float endY);

	/// �ΰ��� ��ǥ�� �޾� ������ ���� ������ ��ȯ
	float getGradeRadianByTwoPoint(float x1, float y1, float x2, float y2);
	float getGradeDegreeByTwoPoint(float x1, float y1, float x2, float y2);

	//���� ������ ��׸� ������ ��ȯ
	float degreeFromRadian(float radian);
	//��׸� ������ ���� ������ ��ȯ
	float radianFromDegree(float degree);
}