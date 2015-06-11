#include "stdafx.h"
#include "PlayerManager.h"


PlayerManager::PlayerManager()
{
}


PlayerManager::~PlayerManager()
{
}

HRESULT PlayerManager::initialize()
{
	_player = new Player;
	_player->initialize();

	_bullet = new Bullet;
	_bullet->initialize(1000);

	return S_OK;
}
void PlayerManager::release()
{
	_player->release();
	_bullet->release();
}
void PlayerManager::update()
{
	if (KEYMANAGER->isOnceKeyDown('1'))
	{
		_player->setY(100);
	}

	if (KEYMANAGER->isStayKeyDown(VK_LBUTTON))
	{
		_bullet->fire(
			_player->getX(), _player->getY(),
			myUtil::getGradeRadianByTwoPoint(_player->getX(), _player->getY(), CAMERA->getMouseX(), CAMERA->getMouseY()),
			20,
			IMAGEMANAGER->findImage("water ball")->getSpriteImage(10, 1));
	}


	if (_player->getRect().bottom + _player->getSpeedY() > STAGE_HEIGHT - LAND_HEIGHT)
	{
		_player->setSpeedY(0);
		_player->setY(STAGE_HEIGHT - LAND_HEIGHT - _player->getHeight() / 2);
	}

	_player->update();
	_bullet->update();

	float x = _player->getX() + (CAMERA->getMouseX() - _player->getX()) * 0.2;
	float y = _player->getY() + (CAMERA->getMouseY() - _player->getY()) * 0.2;

	CAMERA->setX(x);
	CAMERA->setY(y);
}
void PlayerManager::render()
{
	_player->render();
	_bullet->render();
}