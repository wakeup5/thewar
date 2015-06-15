#pragma once
#include "GameNode.h"
#include "PlayerManager.h"
#include "EnemyManager.h"
#include "UI.h"
#include "BackGround.h"
#include "Land.h"
#include "StageObject.h"
#include "StageManager.h"

class GameStudy : public GameNode
{
private:
	UI* _ui;
	StageManager* _stageManager;
public:
	GameStudy(){}
	virtual ~GameStudy(){}

	virtual HRESULT initialize(void);
	virtual void release(void);
	virtual void update(void);
	virtual void render(void);

	void imageLoad();

};
