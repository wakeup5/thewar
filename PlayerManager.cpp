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
	playerFireUpdate();

	if (KEYMANAGER->isOnceKeyDown('0'))
	{
		_player->setWater(1);
	}

	_player->update();
	_bullet->update();

	//카메라 위치 스테이지 클래스로 옮겨야 함.
	float x = _player->getX() + (CAMERA->getMouseX() - _player->getX()) * 0.3;
	float y = _player->getY() + (CAMERA->getMouseY() - _player->getY()) * 0.3;

	CAMERA->setX(x);
	CAMERA->setY(y);
}

void PlayerManager::playerFireUpdate()
{
	if (KEYMANAGER->isStayKeyDown(VK_LBUTTON) && _player->getWater() > 0)
	{
		float fireAngleR = myUtil::getGradeRadianByTwoPoint(_player->getX(), _player->getY(), CAMERA->getMouseX(), CAMERA->getMouseY());
		switch (_player->getWeapon())
		{
		case Player::PLAYER_WEAPON_PISTOL:
			if (TIMEMANAGER->addTimer("player weapon pistol")->checkTime(200))
			{
				_bullet->fire(_player->getX(), _player->getY(), fireAngleR, 15, IMAGEMANAGER->findImage("water ball")->getSpriteImage(10, 1));
				_player->setWater(_player->getWater() - 0.005);
			}
			break;
		case Player::PLAYER_WEAPON_SMG:
			if (TIMEMANAGER->addTimer("player weapon smg")->checkTime(75))
			{
				_bullet->fire(_player->getX(), _player->getY(), fireAngleR, 15, IMAGEMANAGER->findImage("water ball")->getSpriteImage(10, 1));
				_player->setWater(_player->getWater() - 0.003);
			}
			break;
		case Player::PLAYER_WEAPON_SNIPER:
			if (TIMEMANAGER->addTimer("player weapon sniper")->checkTime(800))
			{
				_bullet->fire(_player->getX(), _player->getY(), fireAngleR, 25, IMAGEMANAGER->findImage("water ball")->getSpriteImage(10, 1));
				_player->setWater(_player->getWater() - 0.01);
			}
			break;
		case Player::PLAYER_WEAPON_WATERBOMB:
			if (TIMEMANAGER->addTimer("player weapon bomb")->checkTime(1500))
			{
				_bullet->fire(_player->getX(), _player->getY(), fireAngleR, 8, IMAGEMANAGER->findImage("water ball")->getSpriteImage(10, 1));
				_player->setWater(_player->getWater() - 0.05);
			}
			break;
		}
	}
}

void PlayerManager::render()
{
	_player->render();
	_bullet->render();
}