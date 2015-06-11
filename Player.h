#pragma once
#include "GameNode.h"
class Player : public GameObject
{
public:
	enum PLAYER_STATE
	{
		PLAYER_STATE_LEFT,
		PLAYER_STATE_RIGHT,
		PLAYER_STATE_STAY,
		PLAYER_STATE_JUMP
	};
private:
	SpriteImage* _moveImage;
	SpriteImage* _stayImage;
	SpriteImage* _armImage;

	PLAYER_STATE _playerState;

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

	void setHp(float hp){ _hp = hp; }
	void setWater(float water){ _water = water; }
	void setWeapon(int weapon){ _selectWeapon = weapon; }

	float getHp(){ return _hp; }
	float getWater(){ return _water; }
	int getWeapon(){ return _selectWeapon; }
};

