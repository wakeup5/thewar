#pragma once
#include "GameObject.h"
class StageObject : public GameObject
{
private:
	SpriteImage* _image;
public:
	StageObject();
	~StageObject();

	HRESULT initialize(SpriteImage* image, float x, float y, int width, int height);
	void render(HDC, float);
};

