#include "stdafx.h"
#include "Player.h"


Player::Player()
{
}


Player::~Player()
{
}

HRESULT Player::initialize()
{
	_moveImage = IMAGEMANAGER->findImage("player move")->getSpriteImage(4, 2);
	_stayImage = IMAGEMANAGER->findImage("player stay")->getSpriteImage(1, 2);
	_armImage = IMAGEMANAGER->findImage("player arm")->getSpriteImage(14, 1);

	_playerState = PLAYER_STATE_STAY;

	GameObject::initialize(100, 100, 40, 40);

	return S_OK;
}
void Player::release()
{
	//_image->release();
}
void Player::update()
{
	//플레이어 이동
	if (KEYMANAGER->isStayKeyDown('A'))
	{
		_playerState = PLAYER_STATE_LEFT;
		setX(getX() - 3);
		_moveImage->nextFrameX(150);
	}
	if (KEYMANAGER->isStayKeyDown('D'))
	{
		_playerState = PLAYER_STATE_RIGHT;
		setX(getX() + 3);
		_moveImage->nextFrameX(150);
	}
	if (KEYMANAGER->isOnceKeyUp('D') || KEYMANAGER->isOnceKeyUp('A'))
	{
		_playerState = PLAYER_STATE_STAY;
		_moveImage->setFrameX(0);
	}
	if (KEYMANAGER->isOnceKeyDown(VK_SPACE) && getSpeedY() == 0)
	{
		setSpeedY(-5);
	}

	//오브젝트 값에 따라 움직임
	activate(GRAVITY_ACCEL);
	
	//중력 적용
	//setSpeedY(getSpeedY() + GRAVITY_ACCEL);
	if (getRect().bottom + 0.1 > WIN_SIZE_Y)
	{
		setSpeedY(0);
		setY(WIN_SIZE_Y - getHeight() / 2);
	}

	//표시 스프라이트 프레임
	if (getX() > _mousePoint.x)
	{
		_moveImage->setFrameY(1);
		_stayImage->setFrameY(0);
	}
	else
	{
		_moveImage->setFrameY(0);
		_stayImage->setFrameY(1);
	}

	//각도에 따라 팔 각도 설정
	float armAngleR = myUtil::getGradeRadianByTwoPoint(getX(), getY(), _mousePoint.x, _mousePoint.y);
	int frame = ((myUtil::degreeFromRadian(armAngleR) + 15) / 360) * 14;
	_armImage->setFrameX(frame);

	_moveImage->setCenter(getX(), getY());
	_stayImage->setCenter(getX(), getY());
	_armImage->setCenter(getX(), getY());
}
void Player::render()
{
	if (_playerState == PLAYER_STATE_STAY)
	{
		_stayImage->render(getMemDC());
	}
	else
	{
		_moveImage->render(getMemDC());
	}
		_armImage->render(getMemDC());
}