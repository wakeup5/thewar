#pragma once
#include "GameNode.h"
#include "Player.h"
#include "Bullet.h"

class PlayerManager : public GameNode
{
private:
	Player* _player;
	Bullet* _bullet;
public:
	PlayerManager();
	~PlayerManager();
	
	HRESULT initialize();
	void release();
	void update();
	void render();

	void playerFireUpdate();
	void collisionEnemyBullet();
};

