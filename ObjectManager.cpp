#include "stdafx.h"
#include "ObjectManager.h"


ObjectManager::ObjectManager()
{
}


ObjectManager::~ObjectManager()
{
}

HRESULT ObjectManager::initialize()
{
	return S_OK;
}

void ObjectManager::release()
{
	for (_miNode = _mNode.begin(); _miNode != _mNode.end();)
	{
		_miNode = _mNode.erase(_miNode);
	}

	_mNode.clear();
}

bool ObjectManager::removeObject(GUID id)
{
	MINode iter = _mNode.find(id);

	if (iter != _mNode.end())
	{
		_mNode.erase(iter);
		return true;
	}

	return false;
}