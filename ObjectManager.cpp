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
		//_miNode->second->release();
		//SAFE_DELETE(_miNode->second);
		_miNode = _mNode.erase(_miNode);
	}

	_mNode.clear();
}

GameNode* ObjectManager::addObject(GUID id, GameNode* node)
{
	if (node)
	{
		_mNode.insert(std::make_pair(id, node));
	}

	return node;
}
/*
GameNode* ObjectManager::findObject(GUID id)
{
	MINode iter = _mNode.find(id);

	if (iter != _mNode.end())
	{
		return iter->second;
	}

	return NULL;
}
*/

bool ObjectManager::removeObject(GUID id)
{
	MINode iter = _mNode.find(id);

	if (iter != _mNode.end())
	{
		//iter->second->release();
		//SAFE_DELETE(iter->second);
		_mNode.erase(iter);
		return true;
	}

	return false;
}