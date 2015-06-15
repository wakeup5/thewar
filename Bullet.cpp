#include "stdafx.h"
#include "Bullet.h"


HRESULT OBullet::initialize(float x, float y, float angleR, float speed, SpriteImage* spriteImage, float frameSpeed)
{
	GameNode::initialize();

	setAngleR(angleR);
	setSpeed(speed);
	_image = spriteImage;
	_frameSpeed = frameSpeed;

	_startX = x;
	_startY = y;

	setX(x);
	setY(y);

	setSize(spriteImage->getFrameWidth(), spriteImage->getFrameHeight());

	return S_OK;
}
void OBullet::release()
{
	_image->release();
}
void OBullet::update()
{
	activate(BULLET_GRAVITY_ACCEL);
	_image->setCenter(getX(), getY());
	_image->nextFrame(_frameSpeed);
}
void OBullet::render()
{
	_image->render(CAMERA->getCameraDC());
}

HRESULT Bullet::initialize(float range)
{
	GameNode::initialize();

	_range = range;

	return S_OK;
}
void Bullet::release()
{
	for (_liBullet = _lBullet.begin(); _liBullet != _lBullet.end();)
	{
		//(*_liBullet)->release();
		//SAFE_DELETE(*_liBullet);

		_liBullet = _lBullet.erase(_liBullet);
	}
	_lBullet.clear();
}
void Bullet::update()
{
	for (_liBullet = _lBullet.begin(); _liBullet != _lBullet.end();)
	{
		(*_liBullet)->update();

		//라이프 타임
		if (_range < myUtil::getDistanceByTwoPoint((*_liBullet)->getStartX(), (*_liBullet)->getStartY(), (*_liBullet)->getX(), (*_liBullet)->getY()) ||
			(*_liBullet)->getY() > STAGE_HEIGHT - LAND_HEIGHT)
		{
			EFFECTMANAGER->addEffect(
				IMAGEMANAGER->findImage("water ball pop")->getSpriteImage((*_liBullet)->getX(), (*_liBullet)->getY(), 4, 1));
			_liBullet = _lBullet.erase(_liBullet);
		}
		else
		{
			_liBullet++;
		}
	}
}
void Bullet::render()
{
	for (_liBullet = _lBullet.begin(); _liBullet != _lBullet.end(); _liBullet++)
	{
		(*_liBullet)->render();
	}
}

void Bullet::fire(float x, float y, float angleR, float speed, SpriteImage* spriteImage)
{
	OBullet* oBullet = new OBullet;
	oBullet->initialize(x, y, angleR, speed, spriteImage, 50);

	_lBullet.push_back(oBullet);
}