#pragma once
#include "Player.h"

class UI
{
private:
	Player* _player;
	Image* _waterBar;

	bool _render;
	int _killNum;
public:
	UI();
	~UI();

	HRESULT initialize();
	void release();
	void update();
	void render(HDC bufferDC);

	void setView(bool t){ _render = t; }

	void setKillNum(int num){ _killNum = num; }
	int getKillNum(){ return _killNum; }
};

