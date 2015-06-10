#pragma once
#include <mmsystem.h>

#pragma comment (lib, "winmm.lib")

class Timer
{
private:
	bool _isHardware; //���� Ÿ�̸� ���� �ǳ�?
	float _timeScale; //Ÿ�̸� ����� ����
	float _timeElapsed; //������ �ð��� ����ð��� �����
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

