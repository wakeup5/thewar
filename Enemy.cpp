#include "stdafx.h"
#include "Enemy.h"


Enemy::Enemy()
{
}


Enemy::~Enemy()
{
}


HRESULT Enemy::initialize()
{
	_moveImage = IMAGEMANAGER->findImage("enemy move")->getSpriteImage(4, 3);
	_attackImage = IMAGEMANAGER->findImage("enemy shoot")->getSpriteImage(10, 2);
	_attackImage->setFrameY(0);

	_actionTimer = TIMEMANAGER->addTimer();
	_actionNum = 0;

	GameObject::initialize(150, STAGE_HEIGHT - LAND_HEIGHT, 40, 50);
	Unit::initialize();

	return S_OK;
}
void Enemy::release()
{

}
void Enemy::update()
{
	//Land 클래스로 옮겨야 함. 플레이어 바닥 충돌 처리
	if (getRect().bottom + getSpeedY() > STAGE_HEIGHT - LAND_HEIGHT)
	{
		setSpeedY(0);
		setY(STAGE_HEIGHT - LAND_HEIGHT - getHeight() / 2);
	}
	
	//ai
	if (_actionNum < 20)
	{
		left(ENEMY_SPEED);
	}
	else if (_actionNum < 40)
	{
		right(ENEMY_SPEED);
	}
	else if (_actionNum < 50)
	{
		left(ENEMY_SPEED); 
		jump(ENEMY_JUMP);
	}
	else if (_actionNum < 60)
	{
		right(ENEMY_SPEED);
		jump(ENEMY_JUMP);
	}
	else if (_actionNum < 70)
	{
		jump(ENEMY_JUMP);
	}
	else if (_actionNum < 90)
	{
		stay();
	}
	else if (_actionNum < 100)
	{
		downJump();
	}

	printf("%d\n", getState());
	if (_actionTimer->checkTime(1500))
	{
		_actionNum = RANDOM->getInt(100);
	}

	imageFrameUpdate();
	Unit::update();
	activate(GRAVITY_ACCEL);
}
void Enemy::render()
{
	if (getState() != Unit::UNIT_STAY) _moveImage->render(CAMERA->getCameraDC());
	else _attackImage->render(CAMERA->getCameraDC());
}

void Enemy::imageFrameUpdate()
{
	if (getSpeedY() != 0)
	{
		_moveImage->setFrameY(2);
		if (getState() == Unit::UNIT_MOVE_LEFT) 
			_moveImage->setFrameX(3);
		else
			_moveImage->setFrameX(2);
	}
	else
	{
		if (getState() == Unit::UNIT_MOVE_LEFT)
		{
			_moveImage->setFrameY(1);
		}
		else if (getState() == Unit::UNIT_MOVE_RIGHT)
		{
			_moveImage->setFrameY(0);
		}
		_moveImage->nextFrameX(100);
	}

	if (getState() == Unit::UNIT_STAY)
	{
		Player* player = OBJECTMANAGER->findObject<Player>(GUID_PLAYER);
		_attackAngle = myUtil::getGradeDegreeByTwoPoint(getX(), getY(), player->getX(), player->getY());
		_attackImage->setFrameX((_attackAngle) / 360 * 10);

		printf("111   %f \n", _attackAngle);
	}

	_moveImage->setCenter(getX(), getY());
	_attackImage->setCenter(getX(), getY());
}

void Enemy::attack()
{
	_attackImage->setFrameY(1);
}