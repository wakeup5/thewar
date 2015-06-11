#pragma once
#include "GameNode.h"
class Land : public GameNode
{
private:
	Image* _floor;
	std::vector<RECT> _vLand;

public:
	Land();
	~Land();

	HRESULT initialize(std::vector<RECT>);
	void release();
	void update();
	void render();

	bool collisionLand(GameObject*);
};

