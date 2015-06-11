#include "stdafx.h"
#include "BackGround.h"


BackGround::BackGround()
{
}


BackGround::~BackGround()
{
}

HRESULT BackGround::initialize(bool isH, bool isV, Image* image)
{
	_isHorizontal = isH;
	_isVertical = isV;

	_image = image;

	return S_OK;
}
void BackGround::release()
{

}
void BackGround::update()
{
	_x = CAMERA->getX() * 0.5;
	_y = -CAMERA->getY() * 0.6 + WIN_SIZE_Y / 2;
}
void BackGround::render()
{
	if (_isHorizontal)
	{
		float temp = -(int)_x % (int)_image->getWidth();
		float bgNum = ceil((float)WIN_SIZE_X / (float)_image->getWidth()) + 1;
		
		for (int i = 0; i < bgNum; i++)
		{
			_image->render(CAMERA->getCameraDC(), (CAMERA->getX() - WIN_SIZE_X / 2) + (temp + _image->getWidth() * i), -_y);
		}
		printf("%f \n", temp);
	}
}