#include "stdafx.h"
#include "StageManager.h"


StageManager::StageManager()
{

}


StageManager::~StageManager()
{
}

HRESULT StageManager::initialize()
{
	//플레이어 매니저, 백그라운드, 지형 객체는 스테이지 객체에 있어야 함.
	_playerManager = new PlayerManager;
	_playerManager->initialize();

	_enemyManager = new EnemyManager;
	_enemyManager->initialize();

	stage1();

	return S_OK;
}
void StageManager::release()
{
	SAFE_RELEASE(_playerManager);
	SAFE_RELEASE(_enemyManager);

	SAFE_DELETE(_bg);
	SAFE_DELETE(_land);
	SAFE_DELETE(_campfire);
	SAFE_DELETE(_fountain);
	SAFE_DELETE(_stage);
}
void StageManager::update()
{
	if (_stage != NULL) _stage->update();

	_playerManager->update();
	_enemyManager->update();

	if (TIMEMANAGER->addTimer("enemy create timer")->checkTime(2000) && _enemyManager->size() < 20)
	{
		_enemyManager->addEnemy(STAGE_WIDTH, STAGE_HEIGHT - LAND_HEIGHT);
		_enemyManager->addEnemy(0, STAGE_HEIGHT - LAND_HEIGHT);
	}
}
void StageManager::render()
{
	if (_stage != NULL) _stage->render();

	_playerManager->render();
	_enemyManager->render();
}

void StageManager::stage1()
{
	_bg = new BackGround;
	_bg->initialize(true, false, IMAGEMANAGER->findImage("backMap"));

	_land = new Land;
	_land->initialize(IMAGEMANAGER->findImage("ground"));
	_land->addFloors(IMAGEMANAGER->findImage("floor ground"), 16, 2, 200, STAGE_HEIGHT - 200, 75);
	_land->addFloors(IMAGEMANAGER->findImage("floor ground"), 16, 2, 200, STAGE_HEIGHT - 350, 75);
	_land->addFloors(IMAGEMANAGER->findImage("floor ground"), 16, 2, 400, STAGE_HEIGHT - 500, 50);
	_land->addFloors(IMAGEMANAGER->findImage("floor ground"), 16, 2, 600, STAGE_HEIGHT - 650, 25);

	_campfire = new StageObject;
	_campfire->initialize(IMAGEMANAGER->findImage("campfire")->getSpriteImage(6, 1), STAGE_WIDTH / 2 - 50, 0, 40, 50);
	OBJECTMANAGER->addObject(GUID_CAMPFIRE, _campfire);

	_fountain = new StageObject;
	_fountain->initialize(IMAGEMANAGER->findImage("fountain")->getSpriteImage(3, 1), STAGE_WIDTH / 2 + 50, 0, 50, 66);
	OBJECTMANAGER->addObject(GUID_FOUNTAIN, _fountain);

	_stage = new Stage;
	_stage->initialize(_bg, _land, _campfire, _fountain);
}