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
	_playerManager->getPlayer()->setPosition(STAGE_WIDTH / 2, 0);

	_enemyManager = new EnemyManager;
	_enemyManager->initialize();

	_ui = OBJECTMANAGER->findObject<UI>(GUID_UI);
	_ui->setView(false);

	_stageNum = 0;
	_isStageInit = false;
	_isCameraFromPlayer = true;
	_needKillNum = 0;

	_campfire = new StageObject;
	OBJECTMANAGER->addObject(GUID_CAMPFIRE, _campfire);

	_fountain = new StageObject;
	OBJECTMANAGER->addObject(GUID_FOUNTAIN, _fountain);

	_bg = new BackGround;
	_bg->initialize(true, false, IMAGEMANAGER->findImage("backMap"));


	//stage1();

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
	if (_isCameraFromPlayer)
	{
		//카메라 위치 스테이지 클래스로 옮겨야 함.
		float x = _playerManager->getPlayer()->getX() + (CAMERA->getMouseX() - _playerManager->getPlayer()->getX()) * 0.3;
		float y = _playerManager->getPlayer()->getY() + (CAMERA->getMouseY() - _playerManager->getPlayer()->getY()) * 0.3;

		CAMERA->setX(x);
		CAMERA->setY(y);
	}

	if (_stage != NULL)
	{
		_stage->update();

		_enemyManager->update();
		if (TIMEMANAGER->addTimer("enemy create timer")->checkTime(2000) && _enemyManager->size() <= _ui->getKillNum())
		{
			_enemyManager->addEnemy(STAGE_WIDTH, STAGE_HEIGHT - LAND_HEIGHT);
			_enemyManager->addEnemy(0, STAGE_HEIGHT - LAND_HEIGHT);
		}
	}

	_playerManager->update();

	if (!_isStageInit)
	{
		if (_stageNum == 0 && KEYMANAGER->isOnceKeyDown(VK_RETURN))
		{
			stage1();
		}

		if (_stageNum == 1)
		{
			stage2();
		}

		if (_stageNum == 2)
		{
			stage3();
		}

		if (_stageNum == 3)
		{
			stage4();
		}

		if (_stageNum == 4)
		{
			stage5();
		}
	}

	if (_isStageInit && _ui->getKillNum() <= 0)
	{
		_isStageInit = false;
		_stageNum++;
	}
}
void StageManager::render()
{
	if (_stage != NULL)
	{
		_stage->render();
	}

	if (!_isStageInit)
	{
		if (_stageNum == 0)
		{
			IMAGEMANAGER->findImage("intro 1")->render(CAMERA->getCameraDC());
		}
	}

	_playerManager->render();
	_enemyManager->render();
}

void StageManager::stage1()
{
	_land = new Land;
	_land->initialize(IMAGEMANAGER->findImage("ground"));
	_land->addFloors(IMAGEMANAGER->findImage("floor ground"), 16, 2, 200, STAGE_HEIGHT - 200, 75);
	_land->addFloors(IMAGEMANAGER->findImage("floor ground"), 16, 2, 200, STAGE_HEIGHT - 350, 75);
	_land->addFloors(IMAGEMANAGER->findImage("floor ground"), 16, 2, 400, STAGE_HEIGHT - 500, 50);
	_land->addFloors(IMAGEMANAGER->findImage("floor ground"), 16, 2, 600, STAGE_HEIGHT - 650, 25);

	_campfire->initialize(IMAGEMANAGER->findImage("campfire")->getSpriteImage(6, 1), STAGE_WIDTH / 2 - 50, 0, 40, 50);
	_fountain->initialize(IMAGEMANAGER->findImage("fountain")->getSpriteImage(3, 1), STAGE_WIDTH / 2 + 50, 0, 50, 66);

	_stage = new Stage;
	_stage->initialize(_bg, _land, _campfire, _fountain);

	_playerManager->getPlayer()->initialize();
	_playerManager->getPlayer()->setPosition(STAGE_WIDTH / 2, STAGE_HEIGHT - 300);
	_playerManager->getQueen()->initialize();
	_playerManager->getQueen()->setPosition(STAGE_WIDTH / 2, 0);
	_playerManager->getQueen()->setSpeed(0);

	_ui->setView(true);
	_ui->setKillNum(20);

	_isStageInit = true;
}

void StageManager::stage2()
{
	SAFE_DELETE(_land);
	SAFE_DELETE(_stage);

	_land = new Land;
	_land->initialize(IMAGEMANAGER->findImage("ground"));
	_land->addFloors(IMAGEMANAGER->findImage("floor ground"), 16, 2, 200, STAGE_HEIGHT - 200, 25);
	_land->addFloors(IMAGEMANAGER->findImage("floor ground"), 16, 2, 200, STAGE_HEIGHT - 350, 25);
	_land->addFloors(IMAGEMANAGER->findImage("floor ground"), 16, 2, 200, STAGE_HEIGHT - 500, 25);
	_land->addFloors(IMAGEMANAGER->findImage("floor ground"), 16, 2, 200, STAGE_HEIGHT - 650, 75);
	_land->addFloors(IMAGEMANAGER->findImage("floor ground"), 16, 2, 1000, STAGE_HEIGHT - 200, 25);
	_land->addFloors(IMAGEMANAGER->findImage("floor ground"), 16, 2, 1000, STAGE_HEIGHT - 350, 25);
	_land->addFloors(IMAGEMANAGER->findImage("floor ground"), 16, 2, 1000, STAGE_HEIGHT - 500, 25);

	_campfire->initialize(IMAGEMANAGER->findImage("campfire")->getSpriteImage(6, 1), STAGE_WIDTH / 2 - 50, 0, 40, 50);
	_fountain->initialize(IMAGEMANAGER->findImage("fountain")->getSpriteImage(3, 1), STAGE_WIDTH / 2 + 50, 0, 50, 66);

	_stage = new Stage;
	_stage->initialize(_bg, _land, _campfire, _fountain);

	_playerManager->getPlayer()->initialize();
	_playerManager->getPlayer()->setPosition(STAGE_WIDTH / 2, STAGE_HEIGHT - 300);
	_playerManager->getQueen()->initialize();
	_playerManager->getQueen()->setPosition(STAGE_WIDTH / 2, 0);
	_playerManager->getQueen()->setSpeed(0);

	_ui->setView(true);
	_ui->setKillNum(30);

	_isStageInit = true;
}

void StageManager::stage3()
{
	SAFE_DELETE(_land);
	SAFE_DELETE(_stage);

	_land = new Land;
	_land->initialize(IMAGEMANAGER->findImage("ground"));
	_land->addFloors(IMAGEMANAGER->findImage("floor ground"), 16, 2, 200, STAGE_HEIGHT - 200, 25);
	_land->addFloors(IMAGEMANAGER->findImage("floor ground"), 16, 2, 200, STAGE_HEIGHT - 350, 25);
	_land->addFloors(IMAGEMANAGER->findImage("floor ground"), 16, 2, 200, STAGE_HEIGHT - 500, 25);
	_land->addFloors(IMAGEMANAGER->findImage("floor ground"), 16, 2, 200, STAGE_HEIGHT - 650, 75);
	_land->addFloors(IMAGEMANAGER->findImage("floor ground"), 16, 2, 1000, STAGE_HEIGHT - 200, 25);
	_land->addFloors(IMAGEMANAGER->findImage("floor ground"), 16, 2, 1000, STAGE_HEIGHT - 350, 25);
	_land->addFloors(IMAGEMANAGER->findImage("floor ground"), 16, 2, 1000, STAGE_HEIGHT - 500, 25);

	_campfire->initialize(IMAGEMANAGER->findImage("campfire")->getSpriteImage(6, 1), STAGE_WIDTH / 2 - 50, 0, 40, 50);
	_fountain->initialize(IMAGEMANAGER->findImage("fountain")->getSpriteImage(3, 1), STAGE_WIDTH / 2 + 50, 0, 50, 66);

	_stage = new Stage;
	_stage->initialize(_bg, _land, _campfire, _fountain);

	_playerManager->getPlayer()->initialize();
	_playerManager->getPlayer()->setPosition(STAGE_WIDTH / 2, STAGE_HEIGHT - 300);
	_playerManager->getQueen()->initialize();
	_playerManager->getQueen()->setPosition(STAGE_WIDTH / 2, 0);
	_playerManager->getQueen()->setSpeed(0);

	_ui->setView(true);
	_ui->setKillNum(40);

	_isStageInit = true;
}

void StageManager::stage4()
{
	SAFE_DELETE(_land);
	SAFE_DELETE(_stage);

	_land = new Land;
	_land->initialize(IMAGEMANAGER->findImage("ground"));
	_land->addFloors(IMAGEMANAGER->findImage("floor ground"), 16, 2, 200, STAGE_HEIGHT - 200, 25);
	_land->addFloors(IMAGEMANAGER->findImage("floor ground"), 16, 2, 200, STAGE_HEIGHT - 350, 25);
	_land->addFloors(IMAGEMANAGER->findImage("floor ground"), 16, 2, 200, STAGE_HEIGHT - 500, 25);
	_land->addFloors(IMAGEMANAGER->findImage("floor ground"), 16, 2, 200, STAGE_HEIGHT - 650, 75);
	_land->addFloors(IMAGEMANAGER->findImage("floor ground"), 16, 2, 1000, STAGE_HEIGHT - 200, 25);
	_land->addFloors(IMAGEMANAGER->findImage("floor ground"), 16, 2, 1000, STAGE_HEIGHT - 350, 25);
	_land->addFloors(IMAGEMANAGER->findImage("floor ground"), 16, 2, 1000, STAGE_HEIGHT - 500, 25);

	_campfire->initialize(IMAGEMANAGER->findImage("campfire")->getSpriteImage(6, 1), STAGE_WIDTH / 2 - 50, 0, 40, 50);
	_fountain->initialize(IMAGEMANAGER->findImage("fountain")->getSpriteImage(3, 1), STAGE_WIDTH / 2 + 50, 0, 50, 66);

	_stage = new Stage;
	_stage->initialize(_bg, _land, _campfire, _fountain);

	_playerManager->getPlayer()->initialize();
	_playerManager->getPlayer()->setPosition(STAGE_WIDTH / 2, STAGE_HEIGHT - 300);
	_playerManager->getQueen()->initialize();
	_playerManager->getQueen()->setPosition(STAGE_WIDTH / 2, 0);
	_playerManager->getQueen()->setSpeed(0);

	_ui->setView(true);
	_ui->setKillNum(50);

	_isStageInit = true;
}

void StageManager::stage5()
{
	SAFE_DELETE(_land);
	SAFE_DELETE(_stage);

	_land = new Land;
	_land->initialize(IMAGEMANAGER->findImage("ground"));
	_land->addFloors(IMAGEMANAGER->findImage("floor ground"), 16, 2, 200, STAGE_HEIGHT - 200, 25);
	_land->addFloors(IMAGEMANAGER->findImage("floor ground"), 16, 2, 200, STAGE_HEIGHT - 350, 25);
	_land->addFloors(IMAGEMANAGER->findImage("floor ground"), 16, 2, 200, STAGE_HEIGHT - 500, 25);
	_land->addFloors(IMAGEMANAGER->findImage("floor ground"), 16, 2, 200, STAGE_HEIGHT - 650, 75);
	_land->addFloors(IMAGEMANAGER->findImage("floor ground"), 16, 2, 1000, STAGE_HEIGHT - 200, 25);
	_land->addFloors(IMAGEMANAGER->findImage("floor ground"), 16, 2, 1000, STAGE_HEIGHT - 350, 25);
	_land->addFloors(IMAGEMANAGER->findImage("floor ground"), 16, 2, 1000, STAGE_HEIGHT - 500, 25);

	_campfire->initialize(IMAGEMANAGER->findImage("campfire")->getSpriteImage(6, 1), STAGE_WIDTH / 2 - 50, 0, 40, 50);
	_fountain->initialize(IMAGEMANAGER->findImage("fountain")->getSpriteImage(3, 1), STAGE_WIDTH / 2 + 50, 0, 50, 66);

	_stage = new Stage;
	_stage->initialize(_bg, _land, _campfire, _fountain);

	_playerManager->getPlayer()->initialize();
	_playerManager->getPlayer()->setPosition(STAGE_WIDTH / 2, STAGE_HEIGHT - 300);
	_playerManager->getQueen()->initialize();
	_playerManager->getQueen()->setPosition(STAGE_WIDTH / 2, 0);
	_playerManager->getQueen()->setSpeed(0);

	_ui->setView(true);
	_ui->setKillNum(60);

	_isStageInit = true;
}