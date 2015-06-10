/**	RandomFunction
@file	RandomFunction.h
@author	������(wlsgks5@naver.com)
@date	2015/05/13
@brief	�������� ���� ���� ���� Ŭ���� �ۼ�
*/
#pragma once

#include "SingletonBase.h"

/**
@class	RandomFunction : SingletonBase < RandomFunction >
@date	2015/05/13
*/
class RandomFunction : public SingletonBase < RandomFunction >
{
public:
	RandomFunction()
	{
		srand((unsigned int)time(NULL));
	}

	~RandomFunction()
	{

	}

	int getInt(int num = 10)
	{
		return rand() % num;
	}

	int getIntTo(int from, int to)
	{
		return rand() % (to - from + 1) + from;
	}

	//����1
	float getFloat()
	{
		return static_cast <float> (rand()) / (static_cast <float> (RAND_MAX));// 0 ~ 1.0
	}

	float getFloat(float num)
	{
		return static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / num)); // 0 ~ num
	}

	float getFloatTo(float from, float to)
	{
		return from + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (to - from))); // to ~ from
	}
};