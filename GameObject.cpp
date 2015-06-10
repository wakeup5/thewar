#include "stdafx.h"
#include "GameObject.h"


GameObject::GameObject()
{
	_centerX = 0.0f;
	_centerY = 0.0f;

	_width = 0;
	_height = 0;

	_speedX = 0.0f;
	_speedY = 0.0f;

	_angleD = 0.0f;
	_angleR = 0.0f;

	_speed = 0.0f;
}


GameObject::~GameObject()
{

}

void GameObject::initialize(float centerX, float centerY, int width, int height, float angleD, float speed)
{
	setPosition(centerX, centerY);
	setAngleD(angleD);
	setSpeed(speed);
	setSize(width, height);
	updateRect();
}

void GameObject::setAngleD(float angleD)
{
	_angleD = angleD;
	while (_angleD < 0) _angleD += 360;
	while (_angleD > 360) _angleD -= 360;

	_angleR = _angleD * M_PI / 180;

	_speedX = _speed * cos(_angleR);
	_speedY = -_speed * sin(_angleR);
}
float GameObject::getAngleD()
{
	return _angleD;
}

void GameObject::setAngleR(float angleR)
{
	_angleR = angleR;
	while (_angleR < 0) _angleR += 2 * M_PI;
	while (_angleR > 2 * M_PI) _angleR -= 2 * M_PI;

	_angleD = _angleR * 180 / M_PI;

	_speedX = _speed * cos(_angleR);
	_speedY = -_speed * sin(_angleR);
}
float GameObject::getAngleR()
{
	return _angleR;
}

void GameObject::setSpeedX(float speedX)
{
	_speedX = speedX;

	_angleR = atan2(-_speedY, _speedX);
	_angleD = _angleR * 180 / M_PI;

	_speed = (sqrt(pow(_speedX, 2) + pow(_speedY, 2)));
}
float GameObject::getSpeedX()
{
	return _speedX;
}

void GameObject::setSpeedY(float speedY)
{
	_speedY = speedY;

	_angleR = atan2(-_speedY, _speedX);
	_angleD = _angleR * 180 / M_PI;

	_speed = (sqrt(pow(_speedX, 2) + pow(_speedY, 2)));
}
float GameObject::getSpeedY()
{
	return _speedY;
}

void GameObject::setSpeed(float speed)
{
	/*
	if (speed < 0)
	{
		speed = speed * -1;
		setAngleD(getAngleD() + 180);
	}
	*/

	_speed = speed;

	_speedX = _speed * cos(_angleR);
	_speedY = -_speed * sin(_angleR);
}

float GameObject::getSpeed()
{
	return _speed;
}

void GameObject::activate()
{
	_centerX += _speedX * TIMEMANAGER->getElapsedTime() * 100;
	_centerY += _speedY * TIMEMANAGER->getElapsedTime() * 100;

	updateRect();
}

void GameObject::activate(float gravity)
{
	_speedY += gravity;
	activate();
}
