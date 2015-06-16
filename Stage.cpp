#include "stdafx.h"
#include "Stage.h"


Stage::Stage()
{
}


Stage::~Stage()
{
}

HRESULT Stage::initialize(BackGround* bg, Land* land, StageObject* campfire, StageObject* fountain)
{
	_bg = bg;
	_land = land;
	_campfire = campfire;
	_fountain = fountain;

	_player = OBJECTMANAGER->findObject<Player>(GUID_PLAYER);
	_vEnemy = OBJECTMANAGER->findObject<VEnemy>(GUID_ENEMYS);

	_needKillNum = 0;

	return S_OK;
}
void Stage::release()
{

}
void Stage::update()
{
	_bg->update();
	_land->update();

	_campfire->activate(GRAVITY_ACCEL);
	if (IntersectRect(&makeRect(0, 0, 0, 0), &_campfire->getRect(), &_player->getRect()) &&
		TIMEMANAGER->addTimer("player campfire hp")->checkTime(200))
	{
		_player->setHp(_player->getHp() + 0.05);
	}

	_fountain->activate(GRAVITY_ACCEL);
	if (IntersectRect(&makeRect(0, 0, 0, 0), &_fountain->getRect(), &_player->getRect()) &&
		TIMEMANAGER->addTimer("player fountain water")->checkTime(200))
	{
		_player->setWater(_player->getWater() + 0.02);
		if (_player->getHp() > 0.2)
		{
			_player->setHp(_player->getHp() - 0.005);
		}
	}
}
void Stage::render()
{
	_bg->render();
	_land->render();
	_campfire->render(CAMERA->getCameraDC(), 100);
	_fountain->render(CAMERA->getCameraDC(), 100);
}