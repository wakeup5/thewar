#pragma once
#include "Player.h"

class UI
{
private:
	Player* _player;
	Image* _waterBar;

	bool _render;
public:
	UI();
	~UI();

	HRESULT initialize();
	void release();
	void update();
	void render(HDC bufferDC);

	void setView(bool t){ _render = t; }
};

