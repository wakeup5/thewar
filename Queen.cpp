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

	//���� ������Ʈ
	Unit::update();

	//������Ʈ ���� ���� ������
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
			dialog("��! ����", 1000);
		}
		else
		{
			dialog("�������� ��°Ŷ� �����Ͻô� �ǰ���?", 1000);
		}
	}
	else if (_hp > 0.4)
	{
		if (RANDOM->getInt(2) == 0)
		{
			dialog("��! ������", 1000);
		}
		else
		{
			dialog("�׸� �ϼ���!", 1000);
		}	
	}
	else if (_hp > 0)
	{
		if (RANDOM->getInt(2) == 0)
		{

			dialog("�׸�..", 1000);
		}
		else
		{
			dialog("����..", 1000);
		}
	}
	else
	{
		dialog("����.. �߿�", 5000);
	}
}