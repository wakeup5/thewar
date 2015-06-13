#include "stdafx.h"
#include "util.h"

namespace myUtil
{
	/**	getAngleByTwoPoint
	@date	2015/06/01
	@brief	�ΰ��� ��ǥ�� �޾� ����?�� ��ȯ
	*/
	float getAngleByTwoPoint(float startX, float startY, float endX, float endY)
	{
		float x = endX - startX;
		float y = endY - startY;

		float d = sqrtf(x * x + y * y);
		float angle = acos(x / d);

		if (y > 0) angle = M_PI * 2 - angle;
		return angle;
	}

	/**	getDistanceByTwoPoint
	@date	2015/06/01
	@brief	�ΰ��� ��ǥ�� �޾� �� �������� �Ÿ��� ��ȯ
	*/
	float getDistanceByTwoPoint(float startX, float startY, float endX, float endY)
	{
		float dx = endX - startX;
		float dy = endY - startY;

		return sqrt(dx * dx + dy * dy);
	}

	/**	getGradeRadianByTwoPoint
	@date	2015/06/01
	@brief	�ΰ��� ��ǥ�� �޾� �� ������ ���� ������ ��ȯ
	*/
	float getGradeRadianByTwoPoint(float x1, float y1, float x2, float y2)
	{
		if (y1 > y2)
		{
			return atan2(y1 - y2, x2 - x1);
		}
		else
		{
			return 2 * M_PI - atan2(y2 - y1, x2 - x1);
		}
	}
	/**	getGradeDegreeByTwoPoint
	@date	2015/06/13
	@brief	�ΰ��� ��ǥ�� �޾� �� ������ ��׸� ������ ��ȯ
	*/
	float getGradeDegreeByTwoPoint(float x1, float y1, float x2, float y2)
	{
		return degreeFromRadian(getGradeRadianByTwoPoint(x1, y1, x2, y2));
	}

	//���� ������ ��׸� ������ ��ȯ
	float degreeFromRadian(float radian)
	{
		return (radian / (2 * M_PI)) * 360;
	}
	//��׸� ������ ���� ������ ��ȯ
	float radianFromDegree(float degree)
	{
		return (degree / 360) * (2 * M_PI);
	}
}