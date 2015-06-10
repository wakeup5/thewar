#include "stdafx.h"
#include "util.h"

namespace myUtil
{
	/**	getAngleByTwoPoint
	@date	2015/06/01
	@brief	두개의 좌표를 받아 엇각?을 반환
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
	@brief	두개의 좌표를 받아 두 점사이의 거리를 반환
	*/
	float getDistanceByTwoPoint(float startX, float startY, float endX, float endY)
	{
		float dx = endX - startX;
		float dy = endY - startY;

		return sqrt(dx * dx + dy * dy);
	}

	/**	getGradeRadianByTwoPoint
	@date	2015/06/01
	@brief	두개의 좌표를 받아 그 기울기의 라디안 각도를 반환
	*/
	float getGradeRadianByTwoPoint(float x1, float y1, float x2, float y2)
	{
		return atan2(y1 - y2, x2 - x1);
	}
}