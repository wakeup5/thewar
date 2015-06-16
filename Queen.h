#pragma once
#include "Unit.h"
class Queen : public Unit
{
private:
	SpriteImage* _image;
	float _hp;
public:
	Queen();
	~Queen();

	virtual HRESULT initialize();
	virtual void update();
	virtual void release();
	virtual void render();

	void setHp(float hp){ _hp = hp; }
	float getHp(){ return _hp; }

	void hit();
};

