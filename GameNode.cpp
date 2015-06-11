#include "stdafx.h"
#include "GameNode.h"


GameNode::GameNode()
{

}


GameNode::~GameNode()
{

}
Image* GameNode::_backBuffer;

//초기화
HRESULT GameNode::initialize(bool managerInit)
{
	_managerInit = managerInit;
	_hdc = GetDC(_hWnd);
	
	if (managerInit)
	{
		//SetTimer(_hWnd, 0, 10, NULL);		//타이머 셋팅

		KEYMANAGER->initialize();					//키매니져 셋팅
		IMAGEMANAGER->initialize();				//이미지 매니져 셋팅
		_backBuffer = IMAGEMANAGER->addImage("backBuffer", STAGE_WIDTH, STAGE_HEIGHT);

		TIMEMANAGER->initialize();

		OBJECTMANAGER->initialize();
		EFFECTMANAGER->initialize();
		CAMERA->initialize();
	}

	return S_OK;
}

//해제
void GameNode::release(void)
{
	//_backBuffer->release();
	//SAFE_DELETE(_backBuffer);

	//KillTimer(_hWnd, 0);

	KEYMANAGER->release();
	KEYMANAGER->releaseSingleton();

	EFFECTMANAGER->release();
	EFFECTMANAGER->releaseSingleton();

	IMAGEMANAGER->release();
	IMAGEMANAGER->releaseSingleton();

	TIMEMANAGER->release();
	TIMEMANAGER->releaseSingleton();

	OBJECTMANAGER->release();
	OBJECTMANAGER->releaseSingleton();

	CAMERA->release();
	CAMERA->releaseSingleton();
}

//화면갱신
void GameNode::update(void)
{
	//화면 갱신
	//InvalidateRect(_hWnd, NULL, false);
}

//화면출력
void GameNode::render()
{
	
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
