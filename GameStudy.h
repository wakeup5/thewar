#pragma once
#include "GameNode.h"
#include "PlayerManager.h"
#include "UI.h"
#include "BackGround.h"

class GameStudy : public GameNode
{
private:
	PlayerManager* _playerManager;
	UI* _ui;
	BackGround* _bg;
public:
	GameStudy(){}
	virtual ~GameStudy(){}

	virtual HRESULT initialize(void);
	virtual void release(void);
	virtual void update(void);
	virtual void render(void);

	void imageLoad();

};
