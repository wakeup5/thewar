#include "stdafx.h"
#include "GameStudy.h"

using namespace std;

//초기화
HRESULT GameStudy::initialize(void)
{
	GameNode::initialize(true);

	imageLoad();

	//플레이어 매니저, 백그라운드, 지형 객체는 스테이지 객체에 있어야 함.
	_playerManager = new PlayerManager;
	_playerManager->initialize();
	_bg = new BackGround;
	_bg->initialize(true, false, IMAGEMANAGER->findImage("backMap"));

	_land = new Land;
	_land->initialize(IMAGEMANAGER->findImage("ground"));
	_land->addFloors(IMAGEMANAGER->findImage("floor ground"), 16, 2, 200, STAGE_HEIGHT - 200, 80);
	_land->addFloors(IMAGEMANAGER->findImage("floor ground"), 16, 2, 500, STAGE_HEIGHT - 350, 40);
	_land->addFloors(IMAGEMANAGER->findImage("floor ground"), 16, 2, 800, STAGE_HEIGHT - 500, 10);
	_land->addFloors(IMAGEMANAGER->findImage("floor ground"), 16, 2, 100, STAGE_HEIGHT - 600, 100);
		
	_campfire = new StageObject;
	_campfire->initialize(IMAGEMANAGER->findImage("campfire")->getSpriteImage(6, 1), 100, 500, 40, 50);
	OBJECTMANAGER->addObject(GUID_CAMPFIRE, _campfire);

	_fountain = new StageObject;
	_fountain->initialize(IMAGEMANAGER->findImage("fountain")->getSpriteImage(3, 1), 140, 500, 50, 66);
	OBJECTMANAGER->addObject(GUID_FOUNTAIN, _fountain);

	_ui = new UI;
	_ui->initialize();
	//ShowCursor(false);

	_enemy = new Enemy;
	_enemy->initialize();

	return S_OK;
}

//해제
void GameStudy::release(void)
{
	GameNode::release();
	_ui->release();

	_playerManager->release();
	_bg->release();
	_land->release();


}

//화면갱신
void GameStudy::update(void)
{
	GameNode::update();

	_playerManager->update();
	_ui->update();
	_bg->update();
	_land->update();

	_enemy->update();

	_campfire->activate(GRAVITY_ACCEL);
	Player* player = OBJECTMANAGER->findObject<Player>(GUID_PLAYER);
	if (IntersectRect(&makeRect(0, 0, 0, 0), &_campfire->getRect(), &player->getRect()) &&
		TIMEMANAGER->addTimer("player campfire hp")->checkTime(200))
	{
		player->setHp(player->getHp() + 0.05);
	}

	_fountain->activate(GRAVITY_ACCEL);
	if (IntersectRect(&makeRect(0, 0, 0, 0), &_fountain->getRect(), &player->getRect()) &&
		TIMEMANAGER->addTimer("player fountain water")->checkTime(200))
	{
		player->setWater(player->getWater() + 0.005);
		if (player->getHp() > 0.2)
		{
			player->setHp(player->getHp() - 0.05);
		}
	}

	EFFECTMANAGER->update();
}

//화면출력
void GameStudy::render()
{
	IMAGEMANAGER->render("mapImage", CAMERA->getCameraDC());

	_bg->render();
	_land->render();
	_campfire->render(CAMERA->getCameraDC(), 100);
	_fountain->render(CAMERA->getCameraDC(), 100);
	_playerManager->render();

	_enemy->render();

	//이펙트 출력
	EFFECTMANAGER->render(CAMERA->getCameraDC());
	//카메라dc 출력
	CAMERA->render(getMemDC());
	//마우스 조준 이미지출력
	IMAGEMANAGER->render("aim", getMemDC(), _mousePoint.x - 25, _mousePoint.y - 25);
	//프레임 등 정보 출력
	TIMEMANAGER->render(getMemDC());
	//ui출력
	_ui->render(getMemDC());
	GameNode::render();
}

void GameStudy::imageLoad()
{
	IMAGEMANAGER->addImage("mapImage", "resource/backMap.bmp", STAGE_WIDTH, STAGE_HEIGHT);
	IMAGEMANAGER->addImage("backMap", "resource/background.bmp", 256, 1000);

	IMAGEMANAGER->addImage("player move", "resource/player_move.bmp", 160, 80, TRUE, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("player stay", "resource/player_stay.bmp", 40, 80, TRUE, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("player arm", "resource/player_arm.bmp", 560, 40, TRUE, RGB(255, 0, 255));

	IMAGEMANAGER->addImage("water ball", "resource/water_ball.bmp", 200, 20, TRUE, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("water ball pop", "resource/water_ball_pop.bmp", 200, 50, TRUE, RGB(255, 0, 255));

	IMAGEMANAGER->addImage("aim", "resource/aim.bmp", 50, 50, TRUE, RGB(255, 0, 255));
	
	IMAGEMANAGER->addImage("water bar", "resource/water_bar.bmp", 200, 10);
	IMAGEMANAGER->addImage("water bar back", "resource/water_bar_back.bmp", 204, 14, TRUE, RGB(255, 0, 255));

	IMAGEMANAGER->addImage("icon weapon pistol", "resource/pistol.bmp", 48, 48, TRUE, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("icon weapon smg", "resource/smg.bmp", 48, 48, TRUE, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("icon weapon sniper", "resource/sniper.bmp", 48, 48, TRUE, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("icon weapon bomb", "resource/bomb.bmp", 48, 48, TRUE, RGB(255, 0, 255));

	IMAGEMANAGER->addImage("ground", "resource/ground.bmp", 512, 100);
	IMAGEMANAGER->addImage("floor ground", "resource/floor_ground.bmp", 16, 16);

	IMAGEMANAGER->addImage("campfire", "resource/campfire.bmp", 240, 50, TRUE, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("fountain", "resource/fountain.bmp", 150, 66, TRUE, RGB(255, 0, 255)); 
	
	IMAGEMANAGER->addImage("enemy move", "resource/enemy_move.bmp", 160, 150, TRUE, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("enemy shoot", "resource/enemy_shoot.bmp", 400, 100, TRUE, RGB(255, 0, 255));
}