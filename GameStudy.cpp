#include "stdafx.h"
#include "GameStudy.h"

using namespace std;

//초기화
HRESULT GameStudy::initialize(void)
{
	GameNode::initialize(true);

	imageLoad();

	_playerManager = new PlayerManager;
	_playerManager->initialize();

	_ui = new UI;
	_ui->initialize();

	_bg = new BackGround;
	_bg->initialize(true, false, IMAGEMANAGER->findImage("backMap"));

	//ShowCursor(false);

	return S_OK;
}

//해제
void GameStudy::release(void)
{
	GameNode::release();
	_playerManager->release();
	_ui->release();
	_bg->release();
}

//화면갱신
void GameStudy::update(void)
{
	GameNode::update();

	_playerManager->update();
	_ui->update();
	_bg->update();

	EFFECTMANAGER->update();
}

//화면출력
void GameStudy::render()
{
	IMAGEMANAGER->render("mapImage", CAMERA->getCameraDC());

	_bg->render();
	_playerManager->render();

	EFFECTMANAGER->render(CAMERA->getCameraDC());
	CAMERA->render(getMemDC());
	IMAGEMANAGER->render("aim", getMemDC(), _mousePoint.x - 25, _mousePoint.y - 25);
	TIMEMANAGER->render(getMemDC());
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

}