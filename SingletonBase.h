/**	SingletonBase.h
@file	SingletonBase.h
@author	������(wlsgks5@naver.com)
@date	2015/05/13
@brief	�̱��������� ����ϱ� ���� Ŭ���� �ۼ�
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
	static T* singleton;			///< �ν��Ͻ� ���� ���� ����

	SingletonBase(void) {}
	~SingletonBase(void) {}

public:
	static T* getSingleton(void);	///< �ν��Ͻ� ��ȯ
	void releaseSingleton(void);	///< �ν��Ͻ� ����
};

template < class T >
T* SingletonBase < T >::singleton = NULL;

/** getSingleton
�ν��Ͻ� ��ȯ. �� ������ ������ ��ȯ
@return	typename T* �ν��Ͻ� ��ȯ.
*/
template < class T>
T* SingletonBase < T >::getSingleton(void)
{
	if (singleton == NULL) singleton = new T;
	return singleton;
}

/** releaseSingleton
�ν��Ͻ� �޸� ����. �����Ǿ� ���� ������ ����.
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