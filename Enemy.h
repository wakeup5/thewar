#pragma once
#include "Unit.h"
class Enemy : public Unit
{
private:
	SpriteImage* _moveImage;
	SpriteImage* _attackImage;

	CheckTimer* _actionTimer;
	CheckTimer* _fireTimer;

	int _actionNum;

	float _attackAngle;

	float _hp;

	Bullet* _bullet;
public:
	Enemy();
	~Enemy();

	HRESULT initialize();
	void release();
	void update();
	void render();

	void stay();
	void attack();
	void hit();

	void imageFrameUpdate();

	void setHp(float hp){ _hp = hp; }
	float getHp(){ return _hp; }
};

