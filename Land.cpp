#include "stdafx.h"
#include "Land.h"


Land::Land()
{
}


Land::~Land()
{
}

HRESULT Land::initialize(std::vector<RECT> vLand)
{
	_vLand = vLand;

	_floor = IMAGEMANAGER->findImage("floor");

	return S_OK;
}
void Land::release()
{
	_vLand.clear();
}
void Land::update()
{

}
void Land::render()
{
	float temp = 0;
	do
	{
		_floor->render(CAMERA->getCameraDC(), temp, STAGE_HEIGHT - LAND_HEIGHT);
	} while ((temp += _floor->getWidth()) < STAGE_WIDTH);
}

bool Land::collisionLand(GameObject*)
{

	return false;
}