#pragma once
#include "GameNode.h"
#include "PlayerManager.h"
#include "UI.h"
#include "BackGround.h"
#include "Land.h"
#include "StageObject.h"
#include "Enemy.h"

class GameStudy : public GameNode
{
private:
	UI* _ui;
	PlayerManager* _playerManager;
	StageObject* _campfire;
	StageObject* _fountain;

	BackGround* _bg;
	Land* _land;

	Enemy* _enemy;
public:
	GameStudy(){}
	virtual ~GameStudy(){}

	virtual HRESULT initialize(void);
	virtual void release(void);
	virtual void update(void);
	virtual void render(void);

	void imageLoad();

};
