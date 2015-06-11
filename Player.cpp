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

	OBJECTMANAGER->addObject(GUID_PLAYER, this);

	return S_OK;
}
void Player::release()
{
	//_image->release();
}
void Player::update()
{
	//�÷��̾� �̵�
	if (KEYMANAGER->isStayKeyDown('A') && getRect().left > 0)
	{
		_playerState = PLAYER_STATE_LEFT;
		setX(getX() - PLAYER_SPEED);
	}
	if (KEYMANAGER->isStayKeyDown('D') && getRect().right < STAGE_WIDTH)
	{
		_playerState = PLAYER_STATE_RIGHT;
		setX(getX() + PLAYER_SPEED);
	}
	if (KEYMANAGER->isOnceKeyUp('D') || KEYMANAGER->isOnceKeyUp('A'))
	{
		_playerState = PLAYER_STATE_STAY;
		_moveImage->setFrameX(0);
	}
	if (KEYMANAGER->isOnceKeyDown(VK_SPACE) && getSpeedY() == 0)
	{
		setSpeedY(-PLAYER_JUMP);
	}

	//������Ʈ ���� ���� ������
	activate(GRAVITY_ACCEL);

	//�ٴ�
	if (getRect().bottom + getSpeedY() > STAGE_HEIGHT)
	{
		setSpeedY(0);
		setY(STAGE_HEIGHT - getHeight() / 2);
	}
	//õ��
	if (getRect().top + getSpeedY() < 0)
	{
		setSpeedY(-getSpeedY() * 0.5);
		setY(getHeight() / 2);
	}

	//ǥ�� ��������Ʈ ������
	if (getX() > CAMERA->getMouseX())
	{
		_moveImage->setFrameY(1);
		_stayImage->setFrameY(0);
	}
	else
	{
		_moveImage->setFrameY(0);
		_stayImage->setFrameY(1);
	}

	if (_playerState == PLAYER_STATE_RIGHT || _playerState == PLAYER_STATE_LEFT)
	{
		_moveImage->nextFrameX(150);
	}

	//������ ���� �� ���� ����
	float armAngleR = myUtil::getGradeRadianByTwoPoint(getX(), getY(), CAMERA->getMouseX(), CAMERA->getMouseY());
	int frame = ((myUtil::degreeFromRadian(armAngleR) + 15) / 360) * 14;
	_armImage->setFrameX(frame);

	//�÷��̾� ü�� ȸ��
	if (TIMEMANAGER->addTimer("player health point up")->checkTime(100) && getHp() < 1)
	{
		setHp(getHp() + 0.005);
	}

	//�̹��� ��ġ ��
	_moveImage->setCenter(getX(), getY());
	_stayImage->setCenter(getX(), getY());
	_armImage->setCenter(getX(), getY());
}
void Player::render()
{
	if (_playerState == PLAYER_STATE_STAY)
	{
		_stayImage->render(CAMERA->getCameraDC());
	}
	else
	{
		_moveImage->render(CAMERA->getCameraDC());
	}
	_armImage->render(CAMERA->getCameraDC());
}