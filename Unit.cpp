#include "stdafx.h"
#include "Unit.h"

HRESULT Unit::initialize()
{
	_jumpTimer = TIMEMANAGER->addTimer();

	return S_OK;
}

void Unit::release()
{
	
}

void Unit::update()
{
	if (_jumpState == Unit::UNIT_JUMP_START && _jumpTimer->checkTime(200))
	{
		_jumpState = Unit::UNIT_JUMP_UP;
	}

	if (_jumpState == Unit::UNIT_JUMP_UP && getSpeedY() > 0)
	{
		_jumpState = Unit::UNIT_JUMP_DOWN;
	}
}

void Unit::jump(float jump)
{
	if (getSpeedY() != 0) return;

	setSpeedY(-jump);
	_jumpState = Unit::UNIT_JUMP_START;
	_jumpTimer->checkTime(1);
}
void Unit::downJump()
{
	if (getSpeedY() != 0) return;

	setSpeedY(GRAVITY_ACCEL);
	_jumpState = Unit::UNIT_JUMP_START;
	_jumpTimer->checkTime(1);
}
void Unit::left(float speed)
{
	if (getRect().left < 0) return;

	_state = Unit::UNIT_MOVE_LEFT;
	setX(getX() - speed);
}
void Unit::right(float speed)
{
	if (getRect().right > STAGE_WIDTH) return;

	_state = Unit::UNIT_MOVE_RIGHT;
	setX(getX() + speed);
}
void Unit::stay()
{
	if (getSpeedY() != 0) return;

	_state = Unit::UNIT_STAY;
}
void Unit::attack()
{

}