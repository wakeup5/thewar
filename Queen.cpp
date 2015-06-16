#include "stdafx.h"
#include "Queen.h"


Queen::Queen()
{
}


Queen::~Queen()
{
}

HRESULT Queen::initialize()
{
	Unit::initialize();

	_image = IMAGEMANAGER->findImage("queen")->getSpriteImage(4, 1);
	GameObject::initialize(-100, 0, 40, 40);
	
	_hp = 1.0f;

	return S_OK;
}
void Queen::update()
{
	_image->nextFrameX(200);
	_image->setCenter(getX(), getY());

	//유닛 업데이트
	Unit::update();

	//오브젝트 값에 따라 움직임
	activate(GRAVITY_ACCEL);
}
void Queen::release()
{

}
void Queen::render()
{
	Unit::render();
	_image->render(CAMERA->getCameraDC());
}

void Queen::hit()
{
 	if (_hp > 0.7)
	{
		if (RANDOM->getInt(2) == 0)
		{
			dialog("앗! 물이", 1000);
		}
		else
		{
			dialog("누구에게 쏘는거라 생각하시는 건가요?", 1000);
		}
	}
	else if (_hp > 0.4)
	{
		if (RANDOM->getInt(2) == 0)
		{
			dialog("앗! 차가워", 1000);
		}
		else
		{
			dialog("그만 하세요!", 1000);
		}	
	}
	else if (_hp > 0)
	{
		if (RANDOM->getInt(2) == 0)
		{

			dialog("그만..", 1000);
		}
		else
		{
			dialog("으으..", 1000);
		}
	}
	else
	{
		dialog("으으.. 추워", 5000);
	}
}