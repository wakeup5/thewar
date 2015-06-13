#pragma once
#include "Unit.h"
class Enemy : public Unit
{
private:
	SpriteImage* _moveImage;
	SpriteImage* _attackImage;

	CheckTimer* _actionTimer;
	int _actionNum;

	float _attackAngle;
public:
	Enemy();
	~Enemy();

	HRESULT initialize();
	void release();
	void update();
	void render();

	void attack();

	void imageFrameUpdate();
};

