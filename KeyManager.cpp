#include "stdafx.h"
#include "KeyManager.h"


KeyManager::KeyManager()
{
}


KeyManager::~KeyManager()
{
}

HRESULT KeyManager::initialize()
{
	for (int i = 0; i < KEYMAX; i++)
	{
		this->setKeyUp(i, false);
		this->setKeyDown(i, false);
	}

	return S_OK;
}

void KeyManager::release()
{

}

//Ű �ѹ� ������
bool KeyManager::isOnceKeyDown(int key)
{
	if (GetAsyncKeyState(key) & 0x8000)
	{
		if (!this->getKeyDown()[key])
		{
			this->setKeyDown(key, true);
			return true;
		}
	}
	else
	{
		this->setKeyDown(key, false);
	}

	return false;
}

//Ű�� ���ȴ� ��������
bool KeyManager::isOnceKeyUp(int key)
{
	if (GetAsyncKeyState(key) & 0x8000)
	{
		this->setKeyUp(key, true);
		return false;
	}
	else
	{
		if (this->getKeyUp()[key])
		{
			this->setKeyUp(key, false);
			return true;
		}
	}

	return false;
}

bool KeyManager::isStayKeyDown(int key)
{
	if (GetAsyncKeyState(key))
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool KeyManager::isToggleKey(int key)
{
	
	/*
	if (GetAsyncKeyState(key) & 0x8001)
	{
		return true;
	}
	else
	{
		return false;
	}
	*/
	
	if (isOnceKeyDown(key))
	{
		if (!this->getKeyToggle()[key])
		{
			this->setKeyToggle(key, true);
		}
		else
		{
			this->setKeyToggle(key, false);
		}
	}

	return this->getKeyToggle()[key];
	
}