/** KeyManager
@file	KeyManager.h
@author	박진한(wlsgks5@naver.com)
@date	2015/05/14
@brief	키 입력을 관리.
*/
#pragma once
#include "SingletonBase.h"
#include <bitset>

#define KEYMAX 256

using namespace std;

class KeyManager : public SingletonBase < KeyManager >
{
private:
	bitset<KEYMAX> _keyDown;
	bitset<KEYMAX> _keyUp;
	//bitset<KEYMAX> _keyStay;
	bitset<KEYMAX> _keyToggle;

	bitset<KEYMAX> getKeyDown(){ return _keyDown; }
	bitset<KEYMAX> getKeyUp(){ return _keyUp; }
	//bitset<KEYMAX> getKeyStay(){ return _keyStay; }
	bitset<KEYMAX> getKeyToggle(){ return _keyToggle; }

	void setKeyDown(int key, bool state){ _keyDown.set(key, state); }
	void setKeyUp(int key, bool state){ _keyUp.set(key, state); }
	//void setKeyStay(int key, bool state){ _keyStay.set(key, state); }
	void setKeyToggle(int key, bool state){ _keyToggle.set(key, state); }

public:
	HRESULT initialize();
	void release();

	bool isOnceKeyDown(int key);
	bool isOnceKeyUp(int key);
	bool isStayKeyDown(int key);
	bool isToggleKey(int key);

	KeyManager();
	~KeyManager();
};

