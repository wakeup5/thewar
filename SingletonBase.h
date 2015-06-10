/**	SingletonBase.h
@file	SingletonBase.h
@author	박진한(wlsgks5@naver.com)
@date	2015/05/13
@brief	싱글턴패턴을 사용하기 위한 클래스 작성
*/
#pragma once

/**
@class	SingletonBase < T >
@date	2015/05/13
*/
template < class T >
class SingletonBase
{
protected:
	static T* singleton;			///< 인스턴스 저장 정적 변수

	SingletonBase(void) {}
	~SingletonBase(void) {}

public:
	static T* getSingleton(void);	///< 인스턴스 반환
	void releaseSingleton(void);	///< 인스턴스 해제
};

template < class T >
T* SingletonBase < T >::singleton = NULL;

/** getSingleton
인스턴스 반환. 미 생성시 생성후 반환
@return	typename T* 인스턴스 반환.
*/
template < class T>
T* SingletonBase < T >::getSingleton(void)
{
	if (singleton == NULL) singleton = new T;
	return singleton;
}

/** releaseSingleton
인스턴스 메모리 해제. 해제되어 있지 않으면 해제.
*/
template < class T >
void SingletonBase < T >::releaseSingleton(void)
{
	if (singleton != NULL)
	{
		delete singleton;
		singleton = NULL;
	}
}