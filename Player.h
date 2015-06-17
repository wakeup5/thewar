#pragma once
#include "GameNode.h"
#include "Unit.h"

class Player : public Unit
{
public:
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

	void setHp(float hp)
	{ 
		_hp = hp; 
		if (_hp > 1.0f) _hp = 1.0f;
		if (_hp < 0.0f) _hp = 0.0f;
	}
	void setWater(float water)
	{
		_water = water; 
		if (_water > 1.0f) _water = 1.0f; 
		if (_water < 0.0f) _water = 0.0f;
	}
	void setWeapon(int weapon){ _selectWeapon = weapon; }

	float getHp(){ return _hp; }
	float getWater(){ return _water; }
	int getWeapon(){ return _selectWeapon; }
};

