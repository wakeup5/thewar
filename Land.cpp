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
	
}

bool Land::collisionLand(GameObject*)
{

	return false;
}