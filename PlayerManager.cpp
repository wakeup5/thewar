#include "stdafx.h"
#include "PlayerManager.h"


PlayerManager::PlayerManager()
{
}


PlayerManager::~PlayerManager()
{
	SAFE_DELETE(_queen);
	SAFE_DELETE(_player);
	SAFE_DELETE(_bullet);
}

HRESULT PlayerManager::initialize()
{
	_player = new Player;
	_player->initialize();
	OBJECTMANAGER->addObject(GUID_PLAYER, _player);

	_queen = new Queen;
	_queen->initialize();
	OBJECTMANAGER->addObject(GUID_QUEEN, _queen);

	_bullet = new Bullet;
	_bullet->initialize(1000);
	OBJECTMANAGER->addObject(GUID_PLAYER_BULLET, _bullet);

	return S_OK;
}
void PlayerManager::release()
{
	_queen->release();
	_player->release();
	_bullet->release();
}
void PlayerManager::update()
{
	playerFireUpdate();
	collisionEnemyBullet();

	//치트
	if (KEYMANAGER->isOnceKeyDown('0'))
	{
		_player->setWater(1);
	}

	_player->update();
	_bullet->update();
	_queen->update();

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
				_bullet->fire(_player->getX(), _player->getY(), fireAngleR, 15, IMAGEMANAGER->findImage("water ball")->getSpriteImage(10, 1), 0.6);
				_player->setWater(_player->getWater() - 0.005);
			}
			break;
		case Player::PLAYER_WEAPON_SMG:
			if (TIMEMANAGER->addTimer("player weapon smg")->checkTime(75))
			{
				_bullet->fire(_player->getX(), _player->getY(), fireAngleR, 15, IMAGEMANAGER->findImage("water ball")->getSpriteImage(10, 1), 0.34);
				_player->setWater(_player->getWater() - 0.003);
			}
			break;
		case Player::PLAYER_WEAPON_SNIPER:
			if (TIMEMANAGER->addTimer("player weapon sniper")->checkTime(800))
			{
				_bullet->fire(_player->getX(), _player->getY(), fireAngleR, 25, IMAGEMANAGER->findImage("water ball")->getSpriteImage(10, 1), 1);
				_player->setWater(_player->getWater() - 0.01);
			}
			break;
		case Player::PLAYER_WEAPON_WATERBOMB:
			if (TIMEMANAGER->addTimer("player weapon bomb")->checkTime(1500))
			{
				_bullet->fire(_player->getX(), _player->getY(), fireAngleR, 8, IMAGEMANAGER->findImage("water ball")->getSpriteImage(10, 1), 1);
				_player->setWater(_player->getWater() - 0.05);
			}
			break;
		}
	}
}

void PlayerManager::collisionEnemyBullet()
{
	Bullet::LBullet* enemyBullet = OBJECTMANAGER->findObject<Bullet>(GUID_ENEMY_BULLET)->getBullet();
	RECT r;
	for (Bullet::LIBullet liBullet = enemyBullet->begin(); liBullet != enemyBullet->end();)
	{
		if (IntersectRect(&r, &(*liBullet)->getRect(), &_player->getRect()))
		{
			_player->setHp(_player->getHp() - (*liBullet)->getDamage());
			EFFECTMANAGER->addEffect(IMAGEMANAGER->findImage("water ball pop")->getSpriteImage((*liBullet)->getX(), (*liBullet)->getY(), 4, 1));
			liBullet = enemyBullet->erase(liBullet);
		}
		else
		{
			liBullet++;
		}
	}

	for (Bullet::LIBullet liBullet = enemyBullet->begin(); liBullet != enemyBullet->end();)
	{
		if (IntersectRect(&r, &(*liBullet)->getRect(), &_queen->getRect()))
		{
			_queen->setHp(_queen->getHp() - (*liBullet)->getDamage());
			_queen->hit();
			EFFECTMANAGER->addEffect(IMAGEMANAGER->findImage("water ball pop")->getSpriteImage((*liBullet)->getX(), (*liBullet)->getY(), 4, 1));
			liBullet = enemyBullet->erase(liBullet);
		}
		else
		{
			liBullet++;
		}
	}
}

void PlayerManager::render()
{
	_player->render();
	_bullet->render();
	_queen->render();
}