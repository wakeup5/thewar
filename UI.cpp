#include "stdafx.h"
#include "UI.h"


UI::UI()
{
}


UI::~UI()
{
}

HRESULT UI::initialize()
{
	_player = OBJECTMANAGER->findObject<Player>(GUID_PLAYER);

	return S_OK;
}
void UI::release()
{

}
void UI::update()
{

}
void UI::render(HDC bufferDC)
{
	//체온 체크 크기 50, 50
	float hp = _player->getHp();

	HBRUSH b, ob;
	HPEN p, op;
	b = CreateSolidBrush(RGB(255 * hp - 1, 0, 256 - 255 * hp));
	ob = (HBRUSH)SelectObject(bufferDC, b);
	p = CreatePen(PS_SOLID, 3, RGB(100 + 155 * hp, 50, 155 - 155 * hp));
	op = (HPEN)SelectObject(bufferDC, p);
	drawEllipseCenter(bufferDC, WIN_SIZE_X / 2, 40, 70, 70);
	SelectObject(bufferDC, ob);
	DeleteObject(b);
	SelectObject(bufferDC, op);
	DeleteObject(p);

	SetBkMode(bufferDC, TRANSPARENT);
	SetTextColor(bufferDC, RGB(255, 255, 255));
	
	TCHAR str[128];
	sprintf_s(str, "%2.1f", 34 + 2.9 * hp);
	TextOut(bufferDC, WIN_SIZE_X / 2 - 13, 31, str, strlen(str));

	//물 보유량 체크

	//무기 선택 체크
}