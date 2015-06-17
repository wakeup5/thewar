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

	_water = 1.0f;
	_hp = 1.0f;

	_selectWeapon = Player::PLAYER_WEAPON_PISTOL;

	GameObject::initialize(0, 0, 40, 40);
	Unit::initialize();

	return S_OK;
}
void Player::release()
{
	//_image->release();
}
void Player::update()
{
	moveUpdate();
	selectWeaponUpdate();
	collisionUpdate();
	imageFrameUpdate();

	//�÷��̾� ü�� �ڿ� ȸ��
	if (TIMEMANAGER->addTimer("player health point up")->checkTime(100) && getHp() < 1)
	{
		setHp(getHp() + 0.005);
	}

	if (getRect().bottom + getSpeedY() > STAGE_HEIGHT - LAND_HEIGHT)
	{
		setSpeedY(0);
		setY(STAGE_HEIGHT - LAND_HEIGHT - getHeight() / 2);
	}

	//�̹��� ��ġ ��
	_moveImage->setCenter(getX(), getY());
	_stayImage->setCenter(getX(), getY());
	_armImage->setCenter(getX(), getY());
}

void Player::moveUpdate()
{
	//�÷��̾� �̵�
	if (KEYMANAGER->isStayKeyDown('A') && getRect().left > 0) left(PLAYER_SPEED);
	if (KEYMANAGER->isStayKeyDown('D') && getRect().right < STAGE_WIDTH) right(PLAYER_SPEED);
	if (KEYMANAGER->isOnceKeyUp('D') || KEYMANAGER->isOnceKeyUp('A'))
	{
		stay();
		_moveImage->setFrameX(0);
	}

	//����
	if (KEYMANAGER->isOnceKeyDown(VK_SPACE) && getSpeedY() == 0) jump(PLAYER_JUMP);
	//��������
	if (KEYMANAGER->isOnceKeyDown('S') && getSpeedY() == 0) downJump();
	//���� ������Ʈ
	Unit::update();
	
	//������Ʈ ���� ���� ������
	activate(GRAVITY_ACCEL);
}

void Player::selectWeaponUpdate()
{
	if (KEYMANAGER->isOnceKeyDown('1')) setWeapon(PLAYER_WEAPON_PISTOL);
	else if (KEYMANAGER->isOnceKeyDown('2')) setWeapon(PLAYER_WEAPON_SMG);
	else if (KEYMANAGER->isOnceKeyDown('3')) setWeapon(PLAYER_WEAPON_SNIPER);
	//else if (KEYMANAGER->isOnceKeyDown('4')) setWeapon(PLAYER_WEAPON_WATERBOMB);
}

void Player::collisionUpdate()
{
	//�ٴ�
	if (getRect().bottom + getSpeedY() > STAGE_HEIGHT)
	{
		setSpeedY(0);
		setY(STAGE_HEIGHT - getHeight() / 2);
	}
	//õ��
	/*
	if (getRect().top + getSpeedY() < 0)
	{
		setSpeedY(-getSpeedY() * 0.5);
		setY(getHeight() / 2);
	}
	*/

}
void Player::imageFrameUpdate()
{
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

	if (getState() == Unit::UNIT_MOVE_LEFT || getState() == Unit::UNIT_MOVE_RIGHT)
	{
		_moveImage->nextFrameX(150);
	}

	//������ ���� �� ���� ����
	float armAngleR = myUtil::getGradeRadianByTwoPoint(getX(), getY(), CAMERA->getMouseX(), CAMERA->getMouseY());
	int frame = ((myUtil::degreeFromRadian(armAngleR) + 15) / 360) * 14;
	_armImage->setFrameX(frame);
}


void Player::render()
{
	if (getState() == Unit::UNIT_STAY)
	{
		_stayImage->render(CAMERA->getCameraDC());
	}
	else
	{
		_moveImage->render(CAMERA->getCameraDC());
	}
	_armImage->render(CAMERA->getCameraDC());

	Unit::render();
}