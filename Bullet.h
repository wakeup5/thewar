#pragma once
#include "GameNode.h"

class Bullet : public GameNode
{
public:
	class BulletObject : public GameObject
	{
	private:
		SpriteImage* _image;
		float _frameSpeed;

		float _startX;
		float _startY;

		float _damage;
	public:
		BulletObject(){}
		~BulletObject(){}

		HRESULT initialize(float x, float y, float angleR, float speed, SpriteImage* spriteImage, float frameSpeed);
		void release();
		void update();
		void render();

		float getStartX(){ return _startX; }
		float getStartY(){ return _startY; }

		void setDamage(float d){ _damage = d; }
		float getDamage(){ return _damage; }
	};

	typedef std::list<BulletObject*> LBullet;
	typedef std::list<BulletObject*>::iterator LIBullet;
private:
	LBullet _lBullet;
	LIBullet _liBullet;

	float _range;
public:
	Bullet(){}
	~Bullet(){}

	HRESULT initialize(float range);
	void release();
	void update();
	void render();

	void fire(float x, float y, float angleR, float speed, SpriteImage* spriteImage, float damage);

	LBullet* getBullet(){ return &_lBullet; }
};

typedef Bullet::BulletObject OBullet;