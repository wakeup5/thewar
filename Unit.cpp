#include "stdafx.h"
#include "Unit.h"

HRESULT Unit::initialize()
{
	_jumpTimer = TIMEMANAGER->addTimer();
	_hitTimer = TIMEMANAGER->addTimer();
	_dialogTimer = TIMEMANAGER->addTimer();
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

	if (_state == Unit::UNIT_HIT && _hitTimer->checkTime(280))
	{
		stay();
	}
}

void Unit::render()
{
	if (_isDialog)
	{
		SetBkMode(CAMERA->getCameraDC(), TRANSPARENT);
		SetTextColor(CAMERA->getCameraDC(), RGB(0, 0, 0));

		float width = _dialog.size() * 10;

		drawRectangleCenter(CAMERA->getCameraDC(), getX(), getY() - getHeight(), width, 28);
		TextOut(CAMERA->getCameraDC(), getX() - width / 2 + 7, getY() - getHeight() - 8, _dialog.c_str(), _dialog.size());

		if (_dialogTimer->checkTime(_time))
		{
			_isDialog = false;
		}
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

void Unit::hit()
{
	_state = Unit::UNIT_HIT;
	_hitTimer->checkTime(1);
}

void Unit::dialog(string speek, float time)
{
	_dialog = speek;
	_time = time;
	_isDialog = true;
	_dialogTimer->checkTime(1);
}