#pragma once
#include "GameNode.h"

class Missile :	public GameNode
{
public:
	class MissileObject : public GameObject
	{
	public:
		SpriteImage* image;
		SpriteImage* boostImage;

		float startX;
		float startY;

		bool isFire;

		MissileObject(){}
		~MissileObject(){}
	};

	typedef std::vector<MissileObject> VPMissile;
	typedef std::vector<MissileObject>::iterator VIPMissile;

private:
	std::vector<MissileObject> _missileVector;
	std::vector<MissileObject>::iterator _missileVectorIter;

	int _max;
	float _range;

	Image* _missileImage;
	Image* _boostImage;
public:
	Missile();
	~Missile();

	virtual HRESULT initialize(int max, float range);
	virtual void release();
	virtual void update();
	virtual void render();

	virtual void move();
	virtual void draw();
	virtual void fire(float startX, float startY);

	VPMissile* getMissiles(){ return &_missileVector; }
};

