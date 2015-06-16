#pragma once
#include "GameNode.h"
class Stage : public GameNode
{
private:
	StageObject* _campfire;
	StageObject* _fountain;

	BackGround* _bg;
	Land* _land;

	Player* _player;
	VEnemy* _vEnemy;

	int _needKillNum;
public:
	Stage();
	~Stage();

	HRESULT initialize(BackGround* bg, Land* land, StageObject* campfire, StageObject* fountain);
	void release();
	void update();
	void render();

	void setKillNum(int num){ _needKillNum = num; }
	int getKillNum(){ return _needKillNum; }
};

