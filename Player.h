#pragma once
#include "GameNode.h"
class Player : public GameObject
{
public:
	enum PLAYER_STATE
	{
		PLAYER_STATE_LEFT,
		PLAYER_STATE_RIGHT,
		PLAYER_STATE_STAY
	};

	enum PLAYER_JUMP_STATE
	{
		PLAYER_JUMP_STATE_START,
		PLAYER_JUMP_STATE_UP,
		PLAYER_JUMP_STATE_DOWN,
		PLAYER_JUMP_STATE_STAY
	};

	enum PLAYER_WEAPON
	{
		PLAYER_WEAPON_PISTOL = 1,
		PLAYER_WEAPON_SMG,
		PLAYER_WEAPON_SNIPER,
		PLAYER_WEAPON_WATERBOMB
	};
private:
	SpriteImage* _moveImage;
	SpriteImage* _stayImage;
	SpriteImage* _armImage;

	PLAYER_STATE _playerState;
	PLAYER_JUMP_STATE _playerJumpState;
	int _jumpStartTime;


	float _hp;//퍼센테이지로 구현.
	float _water; //역시 퍼센테이지로
	int _selectWeapon;

public:
	Player();
	~Player();

	HRESULT initialize();
	void release();
	void update();
	void render();

	void moveUpdate();
	void selectWeaponUpdate();
	void collisionUpdate();
	void imageFrameUpdate();

	void setHp(float hp){ _hp = hp; if (_hp > 1.0f) _hp = 1.0f; }
	void setWater(float water){ _water = water; if (_water > 1.0f) _water = 1.0f; }
	void setWeapon(int weapon){ _selectWeapon = weapon; }

	float getHp(){ return _hp; }
	float getWater(){ return _water; }
	int getWeapon(){ return _selectWeapon; }

	void setState(PLAYER_STATE s){ _playerState = s; }
	PLAYER_STATE getState(){ return _playerState; }

	void setJumpState(PLAYER_JUMP_STATE s){ _playerJumpState = s; }
	PLAYER_JUMP_STATE getJumpState(){ return _playerJumpState; }
};

