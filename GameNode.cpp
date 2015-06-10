#include "stdafx.h"
#include "GameNode.h"


GameNode::GameNode()
{

}


GameNode::~GameNode()
{

}
Image* GameNode::_backBuffer;

//�ʱ�ȭ
HRESULT GameNode::initialize(bool managerInit)
{
	_managerInit = managerInit;
	_hdc = GetDC(_hWnd);
	
	if (managerInit)
	{
		//SetTimer(_hWnd, 0, 10, NULL);		//Ÿ�̸� ����

		KEYMANAGER->initialize();					//Ű�Ŵ��� ����
		IMAGEMANAGER->initialize();				//�̹��� �Ŵ��� ����
		GameNode::_backBuffer = IMAGEMANAGER->addImage("backBuffer", WIN_SIZE_X, WIN_SIZE_Y);

		TIMEMANAGER->initialize();

		OBJECTMANAGER->initialize();
		EFFECTMANAGER->initialize();
	}

	return S_OK;
}

//����
void GameNode::release(void)
{
	//_backBuffer->release();
	//SAFE_DELETE(_backBuffer);

	//KillTimer(_hWnd, 0);

	KEYMANAGER->release();
	KEYMANAGER->releaseSingleton();

	IMAGEMANAGER->release();
	IMAGEMANAGER->releaseSingleton();

	TIMEMANAGER->release();
	TIMEMANAGER->releaseSingleton();

	OBJECTMANAGER->release();
	OBJECTMANAGER->releaseSingleton();

	EFFECTMANAGER->release();
	EFFECTMANAGER->releaseSingleton();
}

//ȭ�鰻��
void GameNode::update(void)
{
	//ȭ�� ����
	//InvalidateRect(_hWnd, NULL, false);
	EFFECTMANAGER->update();
}

//ȭ�����
void GameNode::render()
{
	EFFECTMANAGER->render(getMemDC());
	_backBuffer->render(getHDC());
}

LRESULT GameNode::mainProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	switch (iMessage)
	{
	case WM_CREATE:
		_mousePoint = makePoint(WIN_SIZE_X / 2, WIN_SIZE_Y / 2);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	case WM_MOUSEMOVE:
		_mousePoint = makeMousePoint(lParam);
		break;
	case WM_KEYDOWN:
		switch (wParam)
		{
		case VK_ESCAPE:
			PostMessage(hWnd, WM_DESTROY, 0, 0);
			break;
		}
		break; 
	}

	return DefWindowProc(hWnd, iMessage, wParam, lParam);
}

