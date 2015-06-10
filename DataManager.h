#pragma once
#include "SingletonBase.h"
class DataManager : public SingletonBase < DataManager >
{
public:
	HRESULT initialize();
	void release();

	void save(const char* saveFileName, vector<string> vString);

	DataManager();
	~DataManager();
};

