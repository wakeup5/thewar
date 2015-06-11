#include "stdafx.h"
#include "Camera.h"


Camera::Camera()
{
}


Camera::~Camera()
{
}
HRESULT Camera::initialize()
{
	_x = 0;
	_y = 0;

	_cameraBuffer = new Image;
	_cameraBuffer->initialize(STAGE_WIDTH, STAGE_HEIGHT);

	return S_OK;
}
void Camera::release()
{
	_cameraBuffer->release();
	SAFE_DELETE(_cameraBuffer);
}

HDC Camera::getCameraDC()
{
	return _cameraBuffer->getMemDC();
}
void Camera::render(HDC hdc)
{
	_cameraBuffer->render(hdc, -_x + WIN_SIZE_X / 2, -_y + WIN_SIZE_Y / 2);
}

void Camera::setX(float x)
{
	if (x > STAGE_WIDTH - WIN_SIZE_X / 2) x = STAGE_WIDTH - WIN_SIZE_X / 2;
	if (x < WIN_SIZE_X / 2) x = WIN_SIZE_X / 2;
	_x = x;
}
void Camera::setY(float y)
{
	if (y > STAGE_HEIGHT - WIN_SIZE_Y / 2) y = STAGE_HEIGHT - WIN_SIZE_Y / 2;
	if (y < WIN_SIZE_Y / 2) y = WIN_SIZE_Y / 2;
	_y = y; 
}
float Camera::getX()
{ 
	return _x; 
}
float Camera::getY()
{
	return _y; 
}

POINT Camera::getMousePoint()
{
	return POINT{ _mousePoint.x - getX() + WIN_SIZE_X / 2, _mousePoint.y - getY() + WIN_SIZE_Y / 2 };
}
int Camera::getMouseX()
{
	return _mousePoint.x + getX() - WIN_SIZE_X / 2;
}
int Camera::getMouseY()
{
	return _mousePoint.y + getY() - WIN_SIZE_Y / 2;
}