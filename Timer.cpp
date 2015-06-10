#include "stdafx.h"
#include "Timer.h"



Timer::Timer()
{
}


Timer::~Timer()
{
}

HRESULT Timer::initialize(void)
{
	//고성능 타이머 지원 여부 체크
	if (QueryPerformanceFrequency((LARGE_INTEGER*)&_preiodFreqiency))
	{
		_isHardware = true;
		QueryPerformanceCounter((LARGE_INTEGER*)&_lastTime);

		_timeScale = 1.0f / _preiodFreqiency;
	}
	else
	{
		_isHardware = false;
		_lastTime = timeGetTime();

		_timeScale = 0.001f;
	}

	_frameRate = 0;
	_FPSFrameCount = 0;
	_FPSTimeElapsed = 0.0f;
	_worldTime = 0.0f;

	return S_OK;
}
void Timer::tick(float lockFPS)
{
	if (_isHardware)
	{
		QueryPerformanceCounter((LARGE_INTEGER*)&_currentTime);
	}
	else
	{
		_currentTime = timeGetTime();
	}

	_timeElapsed = (_currentTime - _lastTime) * _timeScale;

	if (lockFPS > 0.0f)
	{
		while (_timeElapsed < (1.0f / lockFPS))
		{
			if (_isHardware)
			{
				QueryPerformanceCounter((LARGE_INTEGER*)&_currentTime);
			}
			else
			{
				_currentTime = timeGetTime();
			}

			_timeElapsed = (_currentTime - _lastTime) * _timeScale;
		}
	}

	_lastTime = _currentTime;

	_FPSFrameCount++;

	_FPSTimeElapsed += _timeElapsed;

	_worldTime += _timeElapsed;

	if (_FPSTimeElapsed > 1.0f)
	{
		_frameRate = _FPSFrameCount;
		_FPSFrameCount = 0;
		_FPSTimeElapsed = 0.0f;
	}
}
unsigned long Timer::getFrameRate(char* str) const
{
	if (str != NULL)
	{
		wsprintf(str, "FPS : %d", _frameRate);
	}

	return _frameRate;
}