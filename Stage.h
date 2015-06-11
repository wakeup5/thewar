#pragma once
#include "GameNode.h"
class Stage : public GameNode
{
public:
	Stage();
	~Stage();

	HRESULT initialize(){ return S_OK; }
	void release(){}
	void update(){}
	void render(){}
};

