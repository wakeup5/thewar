#include "stdafx.h"
#include "Land.h"


Land::Land()
{
}


Land::~Land()
{
}

HRESULT Land::initialize(Image* ground, std::vector<RectImage>* vLand)
{
	if (vLand != NULL) _vLand.insert(_vLand.end(), vLand->begin(), vLand->end());

	_floor = ground;

	return S_OK;
}
void Land::release()
{
	_vLand.clear();
}
void Land::update()
{
	Player* player = OBJECTMANAGER->findObject<Player>(GUID_PLAYER);
	StageObject* campfire = OBJECTMANAGER->findObject<StageObject>(GUID_CAMPFIRE);
	StageObject* fountain = OBJECTMANAGER->findObject<StageObject>(GUID_FOUNTAIN);
	VEnemy* vEnemy = OBJECTMANAGER->findObject<VEnemy>(GUID_ENEMYS);

	collisionFloor(player);
	collisionByUnit(player);

	collisionFloor(campfire);
	collisionByStageObject(campfire);
	collisionFloor(fountain);
	collisionByStageObject(fountain);

	for (VIEnemy viEnemy = vEnemy->begin(); viEnemy != vEnemy->end(); viEnemy++)
	{
		collisionFloor(*viEnemy);
		collisionByUnit(*viEnemy);
	}
}
void Land::render()
{
	float temp = 0;
	do
	{
		_floor->render(CAMERA->getCameraDC(), temp, STAGE_HEIGHT - LAND_HEIGHT);
	} while ((temp += _floor->getWidth()) < STAGE_WIDTH);

	vector<RectImage>::iterator viLand;
	for (viLand = _vLand.begin(); viLand != _vLand.end(); viLand++)
	{
		viLand->i->render(CAMERA->getCameraDC(), viLand->r.left, viLand->r.top);
	}
}

const RECT* Land::collisionLand(RECT oRect)
{
	vector<RectImage>::iterator viLand;
	RECT r;
	oRect.top = oRect.bottom - 10;
	oRect.bottom += 1;

	for (int i = 0; i < _vLand.size(); i++)
	{
		if (IntersectRect(&r, &_vLand[i].r, &oRect))
		{
			return &_vLand[i].r;
		}
	}
	/*
	for (viLand = _vLand.begin(); viLand != _vLand.end(); viLand++)
	{
		if (IntersectRect(&r, &viLand->r, &oRect))
		{
			return &viLand->r;
		}
	}
	*/

	return NULL;
}

void Land::collisionByStageObject(StageObject* object)
{
	const RECT* r = collisionLand(object->getRect());
	if (r != NULL)
	{
		object->setSpeedY(0);
		object->setY(r->top - object->getHeight() / 2);
	}
}

void Land::collisionByUnit(Unit* unit)
{
	const RECT* r = collisionLand(unit->getRect());
	if (r != NULL && unit->getJumpState() == Unit::UNIT_JUMP_DOWN)
	{
		unit->setSpeedY(0);
		unit->setY(r->top - unit->getHeight() / 2);
	}
}

void Land::collisionFloor(GameObject* object)
{
	if (object->getRect().bottom + object->getSpeedY() > STAGE_HEIGHT - LAND_HEIGHT)
	{
		object->setSpeedY(0);
		object->setY(STAGE_HEIGHT - LAND_HEIGHT - object->getHeight() / 2);
	}
}

void Land::addFloor(RectImage ri)
{
	_vLand.push_back(ri);
}

void Land::addFloors(Image* image, int sizeX, int sizeY, int startX, int startY, int num)
{
	for (int i = 0; i < num; i++)
	{
		addFloor(RectImage{ makeRect(startX + i * sizeX, startY, sizeX, sizeY), image });
	}
}