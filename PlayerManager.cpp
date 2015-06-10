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
			myUtil::getGradeRadianByTwoPoint(_player->getX(), _player->getY(), _mousePoint.x, _mousePoint.y),
			20,
			IMAGEMANAGER->findImage("water ball")->getSpriteImage(10, 1));
	}


	if (_player->getRect().bottom + _player->getSpeedY() > WIN_SIZE_Y - LAND_HEIGHT)
	{
		_player->setSpeedY(0);
		_player->setY(WIN_SIZE_Y - LAND_HEIGHT - _player->getHeight() / 2);
	}

	_player->update();
	_bullet->update();
}
void PlayerManager::render()
{
	_player->render();
	_bullet->render();
}