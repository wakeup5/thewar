#pragma once
#include "SingletonBase.h"
#include "GameNode.h"

class ObjectManager : public SingletonBase < ObjectManager >
{
private:
	struct GUIDComparer
	{
		bool operator()(const GUID & Left, const GUID & Right) const
		{
			return memcmp(&Left, &Right, sizeof(Right)) < 0;
		}
	};

	typedef std::map<GUID, GameNode*, GUIDComparer> MNode;
	typedef std::map<GUID, GameNode*, GUIDComparer>::iterator MINode;

	MNode _mNode;
	MINode _miNode;

public:
	ObjectManager();
	~ObjectManager();

	HRESULT initialize();
	void release();
	
	bool removeObject(GUID id);
	GameNode* addObject(GUID id, GameNode * node);

	template <typename T>
	T* findObject(GUID id)
	{
		MINode iter = _mNode.find(id);

		if (iter != _mNode.end())
		{
			return static_cast<T*>(iter->second);
		}

		return NULL;
	}
};

