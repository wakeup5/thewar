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
	//Land 클래스로 옮겨야 함. 플레이어 바닥 충돌 처리
	if (player->getRect().bottom + player->getSpeedY() > STAGE_HEIGHT - LAND_HEIGHT)
	{
		player->setSpeedY(0);
		player->setY(STAGE_HEIGHT - LAND_HEIGHT - player->getHeight() / 2);
	}

	StageObject* campfire = OBJECTMANAGER->findObject<StageObject>(GUID_CAMPFIRE);
	//캠프파이어 바닥 충돌 처리
	if (campfire->getRect().bottom + campfire->getSpeedY() > STAGE_HEIGHT - LAND_HEIGHT)
	{
		campfire->setSpeedY(0);
		campfire->setY(STAGE_HEIGHT - LAND_HEIGHT - campfire->getHeight() / 2);
	}

	StageObject* fountain = OBJECTMANAGER->findObject<StageObject>(GUID_FOUNTAIN);
	//분수 바닥 충돌 처리
	if (fountain->getRect().bottom + fountain->getSpeedY() > STAGE_HEIGHT - LAND_HEIGHT)
	{
		fountain->setSpeedY(0);
		fountain->setY(STAGE_HEIGHT - LAND_HEIGHT - fountain->getHeight() / 2);
	}

	//층과 플레이어 충돌처리
	RECT* r = collisionLand(player->getRect());
	if (r != NULL && player->getJumpState() == Unit::UNIT_JUMP_DOWN)
	{
		player->setSpeedY(0);
		player->setY(r->top - player->getHeight() / 2);
	}

	//층과 캠프파이어 충돌처리
	r = collisionLand(campfire->getRect());
	if (r != NULL)
	{
		campfire->setSpeedY(0);
		campfire->setY(r->top - campfire->getHeight() / 2);
	}

	//층과 분수 충돌처리
	r = collisionLand(fountain->getRect());
	if (r != NULL)
	{
		fountain->setSpeedY(0);
		fountain->setY(r->top - fountain->getHeight() / 2);
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

RECT* Land::collisionLand(RECT oRect)
{
	vector<RectImage>::iterator viLand;
	RECT r;
	oRect.top = oRect.bottom - 10;
	oRect.bottom += 1;
	for (viLand = _vLand.begin(); viLand != _vLand.end(); viLand++)
	{
		if (IntersectRect(&r, &viLand->r, &oRect))
		{
			return &viLand->r;
		}
	}

	return NULL;
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