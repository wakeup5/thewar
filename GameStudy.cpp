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

	return S_OK;
}

//해제
void GameStudy::release(void)
{
	GameNode::release();
	_playerManager->release();
}

//화면갱신
void GameStudy::update(void)
{
	GameNode::update();
	_playerManager->update();
}

//화면출력
void GameStudy::render()
{
	IMAGEMANAGER->render("mapImage", getMemDC());
	IMAGEMANAGER->render("backMap", getMemDC());

	_playerManager->render();

	TIMEMANAGER->render(getMemDC());
	GameNode::render();
}

void GameStudy::imageLoad()
{
	IMAGEMANAGER->addImage("mapImage", "resource/mapBlack.bmp", WIN_SIZE_X, WIN_SIZE_Y);
	IMAGEMANAGER->addImage("backMap", "resource/backmap.bmp", WIN_SIZE_X, WIN_SIZE_Y);

	IMAGEMANAGER->addImage("player move", "resource/player_move.bmp", 160, 80, TRUE, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("player stay", "resource/player_stay.bmp", 40, 80, TRUE, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("player arm", "resource/player_arm.bmp", 560, 40, TRUE, RGB(255, 0, 255));

	IMAGEMANAGER->addImage("water ball", "resource/water_ball.bmp", 200, 20, TRUE, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("water ball pop", "resource/water_ball_pop.bmp", 200, 50, TRUE, RGB(255, 0, 255));
}