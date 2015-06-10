#pragma once
#include "SingletonBase.h"
#include "Timer.h"

class TimeManager :	public SingletonBase < TimeManager >
{
public:
	class CheckTimer
	{
	private:
		float _lastTime;
		int _lastFPS;
	public:
		CheckTimer(){ _lastTime = 0.0f; _lastFPS = 0; }
		~CheckTimer(){}

		bool checkTime(float elapsedTime)
		{
			float worldTime = TimeManager::getSingleton()->getWorldTimeMs();
			if (elapsedTime + _lastTime <= worldTime)
			{
				_lastTime = worldTime;
				return true;
			}

			return false;
		}

		bool checkFPS(int elapsedFPS)
		{
			float FPSCount = TimeManager::getSingleton()->getWorldTime() / TimeManager::getSingleton()->getElapsedTime();
			if (elapsedFPS + _lastFPS <= FPSCount)
			{
				_lastFPS = FPSCount;
				return true;
			}

			return false;
		}
	};

private:
	Timer* _timer;

	typedef std::map<std::string, CheckTimer*> MCheckTimer;
	typedef std::map<std::string, CheckTimer*>::iterator MICheckTimer;

	MCheckTimer _mCT;
	MICheckTimer _miCT;

public:
	HRESULT initialize();
	void release();
	void update(float lock = 0.0f);
	void render(HDC hdc);

	CheckTimer* addTimer(std::string = "");
	CheckTimer* findTimer(std::string);
	bool checkTime(std::string, float time);
	bool checkFPS(std::string, int fps);

	inline float getWorldTime() const { return _timer->getWorldTime(); }
	inline float getWorldTimeMs() const { return _timer->getWorldTimeMs(); }
	inline float getElapsedTime() { return _timer->getElapsedTime(); }

	TimeManager();
	~TimeManager();
};

typedef TimeManager::CheckTimer CheckTimer;