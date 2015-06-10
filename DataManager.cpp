#include "stdafx.h"
#include "DataManager.h"


DataManager::DataManager()
{

}


DataManager::~DataManager()
{

}

HRESULT DataManager::initialize()
{
	return S_OK;
}
void DataManager::release()
{

}

void DataManager::save(const char* saveFileName, vector<string> vString)
{
	HANDLE file;
	char str[256];
	DWORD write;

	file = CreateFile("a.save", GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);

	WriteFile(file, str, 256, &write, NULL);

	CloseHandle(file);
}