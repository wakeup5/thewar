#pragma once
#include <mmsystem.h>

#pragma comment (lib, "winmm.lib")

class Timer
{
private:
	bool _isHardware; //고성능 타이머 지원 되나?
	float _timeScale; //타이머 경과량 조절
	float _timeElapsed; //마지막 시간과 현재시간의 경과량
	__int64 _currentTime;
	__int64 _lastTime;
	__int64 _preiodFreqiency;

	unsigned long _frameRate;
	unsigned long _FPSFrameCount;
	float _FPSTimeElapsed;
	float _worldTime;

public:
	Timer();
	~Timer();

	HRESULT initialize(void);
	void tick(float lockFPS = 0.0f);
	unsigned long getFrameRate(char* str = NULL) const;
	//unsigned long getFrameCount() const { return _FPSFrameCount; }
	inline float getElapsedTime() const { return _timeElapsed; }
	inline float getWorldTime() const { return _worldTime; }
	inline float getWorldTimeMs() const { return _worldTime * 1000; }

};

