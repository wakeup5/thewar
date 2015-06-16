#pragma once
#include "GameNode.h"
#include "Stage.h"

class StageManager :
	public GameNode
{
private:
	UI* _ui;
	PlayerManager* _playerManager;
	EnemyManager* _enemyManager;

	Stage* _stage;
	int _stageNum;
	bool _isStageInit;

	bool _isCameraFromPlayer;

	StageObject* _campfire;
	StageObject* _fountain;

	BackGround* _bg;
	Land* _land;
public:
	StageManager();
	~StageManager();

	HRESULT initialize();
	void release();
	void update();
	void render();

	void stage1();
};

