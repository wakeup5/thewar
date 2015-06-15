#pragma once
#include "GameNode.h"
#include "Enemy.h"
#include "Bullet.h"

typedef std::vector<Enemy*> VEnemy;
typedef std::vector<Enemy*>::iterator VIEnemy;

class EnemyManager : public GameNode
{
private:
	VEnemy* _vEnemy;
	VIEnemy _viEnemy;

	Bullet* _bullet;
public:
	EnemyManager();
	~EnemyManager();

	HRESULT initialize();
	void release();
	void update();
	void render();

	void addEnemy(float x, float y);

	int size(){ return _vEnemy->size(); }
};

