/** commonMacroFunction
@file	commonMacroFunction.h
@author	박진한(wlsgks5@naver.com)
@date	2015/05/12
@brief	간편하게 사용할 인라인 매크로 함수들 선언.
*/
#include "stdafx.h"

/* ================================================================================
 * ===========================  ## 구조체 ##  ======================================
 * ================================================================================*/

/** POINTRECT POINT와 RECT를 포함
@date	2015/05/13
*/
typedef struct tagPOINTRECT
{
	POINT point;
	RECT rect;
} POINTRECT;

/* ================================================================================
 * ===========================  ## 좌표 생성 함수 ##  ===============================
 * ================================================================================ */

/** makePoint 좌표를 입력하면 포인트 변수를 만들어 리턴
@date	2015/05/12
@param	x x좌표
@param	y y좌표
@return	POINT
*/
inline POINT makePoint(int x, int y)
{
	return POINT{ x, y };
}

/** makeRect 좌표와 폭을 입력하면 Rect를 만들어 리턴
@date	2015/05/12
@param	int x left
@param	int y top
@param	int width 폭
@param	int height 높이
@return	RECT
*/
inline RECT makeRect(int x, int y, int width, int height)
{
	return RECT{ x, y, x + width, y + height };
}

/** makeRectCenter 중심 좌표를 중심으로 Rect를 만들어 리턴
@date	2015/05/12
@param	int centerX 중심 x좌표
@param	int centerY 중심 y좌표
@param	int width 폭
@param	int height 높이
@return	RECT
*/
inline RECT makeRectCenter(int centerX, int centerY, int width, int height)
{
	return RECT{ centerX - (width / 2), centerY - (height / 2), centerX + (width / 2), centerY + (height / 2) };
}

/** makeRectCenter 중심 좌표POINT를 중심으로 Rect를 만들어 리턴
@date	2015/05/13
@param	POINT x, y 중심 좌표 POINT
@param	int width 폭
@param	int height 높이
@return	RECT
*/
inline RECT makeRectCenter(POINT &p, int width, int height)
{
	return makeRectCenter(p.x, p.y, width, height);//RECT{ p.x - (width / 2), p.y - (height / 2), p.x + (width / 2), p.y + (height / 2) };
}

/** makeRectCenter 마우스 좌표를 입력 받아 포인트를 리턴
@date	2015/05/13
@param	LPARAM
@return	POINT
*/
inline POINT makeMousePoint(LPARAM lParam)
{
	return POINT{ static_cast<int>(LOWORD(lParam)), static_cast<int>(HIWORD(lParam)) };
}

/** makePointRectCenter 중심좌표와 크기를 입력받아 POINT와 RECT가 포함된 구조체를 리턴
@date	2015/05/13
@param	int centerX 중심 x좌표
@param	int centerY 중심 y좌표
@param	int width 폭
@param	int height 높이
@return	POINTRECT
*/
inline POINTRECT makePointRectCenter(int centerX, int centerY, int width, int height)
{
	return POINTRECT{ makePoint(centerX, centerY), makeRectCenter(centerX, centerY, width, height) };
}

/** makePointRectCenter 중심좌표와 크기를 입력받아 POINT와 RECT가 포함된 구조체를 리턴
@date	2015/05/13
@param	POINT 중심좌표 POINT
@param	int width 폭
@param	int height 높이
@return	POINTRECT
*/
inline POINTRECT makePointRectCenter(POINT p, int width, int height)
{
	return POINTRECT{ p, makeRectCenter(p.x, p.y, width, height) };
}

/** reverseRect RECT의 left, right와 top, bottom이 서로 자리가 바뀐 경우 서로 값을 바꿔준다.
@date	2015/05/16
@param	RECT
@return	RECT
*/
inline RECT reverseRect(RECT &rect)
{
	int temp;

	if (rect.left > rect.right)
	{
		temp = rect.left;
		rect.left = rect.right;
		rect.right = temp;
	}

	if (rect.top > rect.bottom)
	{
		temp = rect.top;
		rect.top = rect.bottom;
		rect.bottom = temp;
	}

	return rect;
}

/** makePointByRect RECT의 중심 좌표 리턴
@date	2015/05/16
@param	RECT
@return	POINT
*/
inline POINT makePointByRect(RECT &r)
{
	r = reverseRect(r);
	return POINT{ r.left + (r.right - r.left) / 2, r.top + (r.bottom - r.top) / 2 };
}

/* ================================================================================
* ===========================  ## 도형 그리기 함수 ##  =============================
* ================================================================================ */

/** drawLine 좌표를 입력받아 선을 그린다.
@date	2015/05/12
@param	HDC 윈도우 dc의 핸들
@param	int x1 시작 x좌표
@param	int y1 시작 y좌표
@param	int x2 끝 x좌표
@param	int y2 끝 y좌표
*/
inline void drawLine(HDC hdc, int x1, int y1, int x2, int y2)
{
	MoveToEx(hdc, x1, y1, NULL);
	LineTo(hdc, x2, y2);
}

/** drawLine 좌표를 입력받아 선을 그린다.
@date	2015/05/12
@param	HDC 윈도우 dc의 핸들
@param	POINT 시작 좌표
@param	POINT 끝 좌표
*/
inline void drawLine(HDC hdc, POINT a, POINT b)
{
	MoveToEx(hdc, a.x, a.y, NULL);
	LineTo(hdc, b.x, b.y);
}

/** drawLines 여러 좌표들을 받아 여러개의 선을 그린다.
@date	2015/05/12
@param	HDC 윈도우 dc의 핸들
@param	vector<POINT> 여러개의 포인트들
*/
inline void drawLines(HDC hdc, std::vector<POINT> &pointVector)
{
	std::vector<POINT>::iterator iter;

	for (iter = pointVector.begin(); iter != pointVector.end(); iter++)
	{
		if (iter == pointVector.begin()) MoveToEx(hdc, iter->x, iter->y, NULL);
		else LineTo(hdc, iter->x, iter->y);
	}
}

/** drawRectangle 좌표와 크기를 입력받아 사각형을 그린다.
@date	2015/05/12
@param	HDC 윈도우 dc의 핸들
@param	int x left
@param	int y top
@param	int width 폭
@param	int height 높이
*/
inline void drawRectangle(HDC hdc, int x, int y, int width, int height)
{
	Rectangle(hdc, x, y, x + width, y + height);
}

/** drawRectangle RECT를 입력받아 사각형을 그린다.
@date	2015/05/12
@brief	RECT를 받기 때문에 left, top, right, bottom 기준으로 입력 받는다.
@param	HDC 윈도우 dc의 핸들
@param	RECT
*/
inline void drawRectangle(HDC hdc, RECT &r)
{
	Rectangle(hdc, r.left, r.top, r.right, r.bottom);
}

/** drawRectangleCenter 좌표를 중심으로 사각형을 그린다.
@date	2015/05/12
@param	HDC 윈도우 dc의 핸들
@param	int centerX 중심 좌표 x
@param	int centerY 중심 좌표 y
@param	int width 폭
@param	int height 높이
*/
inline void drawRectangleCenter(HDC hdc, int centerX, int centerY, int width, int height)
{
	Rectangle(hdc, centerX - (width / 2), centerY - (height / 2), centerX + (width / 2), centerY + (height / 2));
}

/** drawRectangleCenter 좌표를 중심으로 사각형을 그린다.
@date	2015/05/13
@param	HDC 윈도우 dc의 핸들
@param	POINT x, y 중심 좌표 POINT
@param	int width 폭
@param	int height 높이
*/
inline void drawRectangleCenter(HDC hdc, POINT &p, int width, int height)
{
	//Rectangle(hdc, centerX - (width / 2), centerY - (height / 2), centerX + (width / 2), centerY + (height / 2));
	drawRectangleCenter(hdc, p.x, p.y, width, height);
}

/** drawEllipse 좌표와 크기를 받아 중심으로 원을 그린다.
@date	2015/05/12
@param	HDC 윈도우 dc의 핸들
@param	int x left
@param	int y top
@param	int width 폭
@param	int height 높이
*/
inline void drawEllipse(HDC hdc, int x, int y, int width, int height)
{
	Ellipse(hdc, x, y, x + width, y + height);
}

/** drawEllipse RECT를 받아 중심으로 원을 그린다.
@date	2015/05/12
@brief	RECT를 받기 때문에 left, top, right, bottom 기준으로 입력 받는다.
@param	HDC 윈도우 dc의 핸들
@param	RECT
*/
inline void drawEllipse(HDC hdc, RECT &r)
{
	Ellipse(hdc, r.left, r.top, r.right, r.bottom);
}

/** drawEllipseCenter 좌표를 중심으로 원을 그린다.
@date	2015/05/12
@param	HDC 윈도우 dc의 핸들
@param	int centerX 중심 좌표 x
@param	int centerY 중심 좌표 y
@param	int width 폭
@param	int height 높이
*/
inline void drawEllipseCenter(HDC hdc, int centerX, int centerY, int width, int height)
{
	Ellipse(hdc, centerX - (width / 2), centerY - (height / 2), centerX + (width / 2), centerY + (height / 2));
}

/** drawEllipseCenter 좌표를 중심으로 원을 그린다.
@date	2015/05/13
@param	HDC 윈도우 dc의 핸들
@param	POINT x, y 중심 좌표 POINT
@param	int width 폭
@param	int height 높이
*/
inline void drawEllipseCenter(HDC hdc, POINT &p, int width, int height)
{
	//Ellipse(hdc, centerX - (width / 2), centerY - (height / 2), centerX + (width / 2), centerY + (height / 2));
	drawEllipseCenter(hdc, p.x, p.y, width, height);
}

/* ================================================================================
* ===========================  ## 충돌 체크 함수 ##  ===============================
* ================================================================================ */

/** checkInRectangle POINT가 RECT 내에 있는지 체크. 충돌 체크
@date	2015/05/12
@param	POINT
@param	RECT
@return	bool 안에 존재하는지의 여부
*/
inline bool checkInRectangle(POINT &point, RECT &rect)
{
	rect = reverseRect(rect);

	if (point.x >= rect.left &&
		point.x <= rect.right &&
		point.y >= rect.top &&
		point.y <= rect.bottom)
		return true;
	else
		return false;
}
inline bool isCollisionRectangle(POINT &p, RECT &r)
{
	return checkInRectangle(p, r);
}

/** checkInRectangle RECT가 RECT 내에 있는지 체크.충돌 체크
@date	2015/05/12
@date	2015/05/17 조건 수정
@param	RECT
@param	RECT
@return	bool 안에 존재하는지의 여부
*/
inline bool checkInRectangle(RECT &rect1, RECT &rect2)
{
	rect1 = reverseRect(rect1);
	rect2 = reverseRect(rect2);

	if (rect1.left < rect2.right &&
		rect1.right > rect2.left &&
		rect1.top < rect2.bottom &&
		rect1.bottom > rect2.top)
	{
		return true;
	}
	else
	{
		return false;
	}
}
inline bool isCollisionRectangle(RECT &r1, RECT &r2)
{
	return checkInRectangle(r1, r2);
}

/** checkInEllipse POINT가 RECT(원) 내에 있는지 체크.충돌 체크
@date	2015/05/12
@param	POINT
@param	RECT
@return	bool 안에 존재하는지의 여부
*/
inline bool checkInEllipse(POINT &p, RECT &r)
{
	r = reverseRect(r);

	int x = p.x - (r.left + (r.right - r.left) / 2);
	int y = p.y - (r.top + (r.bottom - r.top) / 2);
	int width = (r.right - r.left) / 2;
	int height = (r.bottom - r.top) / 2;

	if (pow(x, 2) / pow(width, 2) + pow(y, 2) / pow(height, 2) <= 1)
	{
		return true;
	}

	return false;
}
inline bool isCollisionEllipse(POINT &p, RECT &r)
{
	return checkInEllipse(p, r);
}

/** checkInEllipse 사각형과 원의 충돌 처리
@date	2015/05/16
@param	RECT 사각형
@param	RECT 원
@return	bool 안에 존재하는지의 여부
*/
inline bool checkInEllipse(RECT &rectangle, RECT &ellipse)
{
	POINT ellipseCenter = makePointByRect(ellipse);

	rectangle = reverseRect(rectangle);
	ellipse = reverseRect(ellipse);

	//개선의 가능성이 있으면 개선 해야지..
	if (checkInEllipse(makePoint(rectangle.left + 1, rectangle.top + 1), ellipse) || //각 사각형의 모서리가 원 안에 있을때
		checkInEllipse(makePoint(rectangle.right - 1, rectangle.top + 1), ellipse) ||
		checkInEllipse(makePoint(rectangle.left + 1, rectangle.bottom - 1), ellipse) ||
		checkInEllipse(makePoint(rectangle.right - 1, rectangle.bottom - 1), ellipse) ||
		checkInRectangle(ellipseCenter, rectangle) || //원 중심이 사각형 안에 있을때
		(ellipseCenter.x >= rectangle.left && ellipseCenter.x <= rectangle.right && //원 중심의 x값이 사각형 폭 안에 있으면서 사각형 아래가 원 위, 사각형 위가 원 아래 안에 있으면
		ellipse.top < rectangle.bottom && ellipse.bottom > rectangle.top) ||
		(ellipseCenter.y >= rectangle.top && ellipseCenter.y <= rectangle.bottom && //y 값
		ellipse.left < rectangle.right && ellipse.right > rectangle.left))
	{
		return true;
	}
	else
	{
		return false;
	}
}
inline bool isCollisionEllipse(RECT &rectangle, RECT &ellipse)
{
	return checkInEllipse(rectangle, ellipse);
}

/** checkInCircleToCircle 원과 원 충돌.
@date	2015/05/20
@param	RECT 원1
@param	RECT 원2
@return	bool 안에 존재하는지의 여부
*/
inline bool checkInCircleToCircle(const RECT &c1, const RECT &c2)
{
	int circleRadius1 = (c1.right - c1.left) / 2;
	int circleRadius2 = (c2.right - c2.left) / 2;

	POINT circleCenter1 = POINT{ c1.left + circleRadius1, c1.top + circleRadius1 };
	POINT circleCenter2 = POINT{ c2.left + circleRadius2, c2.top + circleRadius2 };
	
	if (pow(circleCenter1.x - circleCenter2.x, 2) + pow(circleCenter1.y - circleCenter2.y, 2)
		<= pow(circleRadius1 + circleRadius2, 2))
	{
		return true;
	}

	return false;
}
inline bool isCollisionCircle(RECT &c1, RECT &c2)
{
	return checkInCircleToCircle(c1, c2);
}

/** getAngleToCollisionCircle 원과 원 충돌 후의 각도를 리턴.
@date	2015/05/21
@param	float 자신 원의 중심x
@param	float 자신 원의 중심y
@param	float 다른 원의 중심x
@param	float 다른 원의 중심y
@return	float 충돌 후의 각도
*/
/*
inline float getAngleRadian(float x1, float y1, float x2, float y2)
{
	float x = x2 - x1;
	float y = y2 - y1;
	float hypo = sqrt(x * x + y * y);
	float angle = acosf(x / hypo);
	if (y2 > y1)
	{
		angle = 2 * M_PI - angle;
		if (angle >= 2 * M_PI) angle -= 2 * M_PI;
	}
	return angle;
}
*/

/** getDistance 두 점 사이의 거리를 리턴
@date	2015/05/22
@param	float
@param	float
@param	float
@param	float
@return	float
*/
/*
inline float getDistance(float x1, float y1, float x2, float y2)
{
	return sqrt(pow(x1 - x2, 2) + pow(y1 - y2, 2));
}
*/

/** getRadianByTwoPosition 두 점의 기울기로 라디안 각도를 구함
@date	2015/05/22
@param	float
@param	float
@param	float
@param	float
@return	float
*/
/*
inline float getRadianByTwoPosition(float x1, float y1, float x2, float y2)
{
	return atan2(y1 - y2, x2 - x1);
}
*/
