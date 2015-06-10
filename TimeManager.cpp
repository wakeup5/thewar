#include "stdafx.h"
#include "TimeManager.h"


TimeManager::TimeManager()
{
}


TimeManager::~TimeManager()
{
}

HRESULT TimeManager::initialize()
{
	_timer = new Timer;
	_timer->initialize();

	return S_OK;
}
void TimeManager::release()
{
	if (_timer != NULL)
	{
		//_timer->release();
		SAFE_DELETE(_timer);
	}

	for (_miCT = _mCT.begin(); _miCT != _mCT.end();)
	{
		_miCT = _mCT.erase(_miCT);
	}

	_mCT.clear();

}
void TimeManager::update(float lock)
{
	if(_timer != NULL) _timer->tick(lock);
}
void TimeManager::render(HDC hdc)
{
	char str[128];
	std::string strFrame;

	SetBkMode(hdc, TRANSPARENT);
	SetTextColor(hdc, RGB(255, 255, 255));

#ifdef _DEBUG
	if(_timer != NULL)
	{
		sprintf_s(str, "Frame per Second : %d", _timer->getFrameRate());
		TextOut(hdc, 10, 10, str, strlen(str));

		sprintf_s(str, "World Time : %f", _timer->getWorldTime());
		TextOut(hdc, 10, 30, str, strlen(str));

		sprintf_s(str, "Elapsed Time : %f", _timer->getElapsedTime());
		TextOut(hdc, 10, 50, str, strlen(str));
	}
#else
	if (_timer != NULL)
	{
		sprintf_s(str, "Frame per Second : %f", _timer->getFrameRate());
		TextOut(hdc, 10, 10, str, strlen(str));
	}
#endif
}

TimeManager::CheckTimer* TimeManager::addTimer(std::string key)
{
	static int i = 0;
	std::string k = key;
	TimeManager::CheckTimer* timer = NULL;

	if (k.empty())
	{
		k = "my standard timer " + to_string(i++);
	}
	else
	{
		timer = findTimer(k);
	}

	if (timer == NULL)
	{
		timer = new TimeManager::CheckTimer;
		_mCT.insert(std::make_pair(k, timer));
	}

	return timer;
}
TimeManager::CheckTimer* TimeManager::findTimer(std::string key)
{
	MICheckTimer iter = _mCT.find(key);
	TimeManager::CheckTimer* timer = NULL;

	if (iter != _mCT.end())
	{
		timer = iter->second;
	}
	
	return timer;
}
bool TimeManager::checkTime(std::string key, float time)
{
	TimeManager::CheckTimer* timer = findTimer(key);

	if (timer == NULL)
	{
		return false;
	}

	return timer->checkTime(time);
}
bool TimeManager::checkFPS(std::string key, int fps)
{
	TimeManager::CheckTimer* timer = findTimer(key);

	if (timer == NULL)
	{
		return false;
	}

	return timer->checkFPS(fps);
}