#pragma once
#include "GameNode.h"
class BackGround :
	public GameNode
{
private:
	Image* _image;

	bool _isHorizontal;
	bool _isVertical;

	float _x;
	float _y;
public:
	BackGround();
	~BackGround();

	HRESULT initialize(bool isH, bool isV, Image* image);
	void release();
	void update();
	void render();
};

