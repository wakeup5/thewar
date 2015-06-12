#include "stdafx.h"
#include "StageObject.h"


StageObject::StageObject()
{
}


StageObject::~StageObject()
{
}

HRESULT StageObject::initialize(SpriteImage* image, float x, float y, int width, int height)
{
	_image = image;
	GameObject::initialize(x, y, width, height);

	return S_OK;
}
void StageObject::render(HDC dc, float frameTime)
{
	_image->nextFrame(frameTime);
	_image->setCenter(getX(), getY());
	_image->render(dc);
}