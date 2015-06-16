#pragma once
#include "GameObject.h"

class Unit : public GameObject
{
public:
	enum UNIT_STATE
	{
		UNIT_MOVE_LEFT,
		UNIT_MOVE_RIGHT,
		UNIT_HIT,
		UNIT_STAY
	};

	enum UNIT_JUMP_STATE
	{
		UNIT_JUMP_START,
		UNIT_JUMP_UP,
		UNIT_JUMP_DOWN
	};

protected:
	UNIT_STATE _state;
	UNIT_JUMP_STATE _jumpState;
	CheckTimer* _jumpTimer;
	CheckTimer* _hitTimer;

	CheckTimer* _dialogTimer;
	float _time;
	bool _isDialog;
	std::string _dialog;

public:
	Unit(){}
	~Unit(){}

	UNIT_STATE getState(){ return _state; }
	UNIT_JUMP_STATE getJumpState(){ return _jumpState; }
	void setState(UNIT_STATE s){ _state = s; }
	void setJumpState(UNIT_JUMP_STATE s){ _jumpState = s; }

	virtual HRESULT initialize();
	virtual void update();
	virtual void release();
	virtual void render();

	virtual void jump(float);
	virtual void downJump();
	virtual void left(float);
	virtual void right(float);
	virtual void stay();
	virtual void attack();
	virtual void hit();

	virtual void dialog(std::string, float);
};

