#pragma once
#include "Unit.h"
class Enemy : public Unit
{
protected:
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

	virtual HRESULT initialize();
	void release();
	void update();
	void render();

	void stay();
	virtual void attack();
	virtual void hit();

	void imageFrameUpdate();

	void setHp(float hp){ _hp = hp; }
	float getHp(){ return _hp; }
};

class EnemyBoss : public Enemy
{
public:
	EnemyBoss(){}
	~EnemyBoss(){}
	virtual HRESULT initialize();
	void hit();
	void attack();
};
