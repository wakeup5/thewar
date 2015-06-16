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
	_render = false;
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
	if (!_render) return;
	//물 보유량 체크
	float water = _player->getWater();
	IMAGEMANAGER->render("water bar back", bufferDC, WIN_SIZE_X / 2 - 102, 11);
	IMAGEMANAGER->render("water bar", bufferDC, WIN_SIZE_X / 2 - 100, 13, 0, 0, 200 * water, 10);

	//체온 체크 크기 50, 50
	float hp = _player->getHp();

	HBRUSH b, ob;
	HPEN p, op;
	b = CreateSolidBrush(RGB(255 * hp - 1, 0, 256 - 255 * hp));
	ob = (HBRUSH)SelectObject(bufferDC, b);
	p = CreatePen(PS_SOLID, 3, RGB(100 + 155 * hp, 50, 155 - 155 * hp));
	op = (HPEN)SelectObject(bufferDC, p);

	drawEllipseCenter(bufferDC, WIN_SIZE_X / 2, 45, 50, 50);

	SelectObject(bufferDC, ob);
	DeleteObject(b);
	SelectObject(bufferDC, op);
	DeleteObject(p);

	SetBkMode(bufferDC, TRANSPARENT);
	SetTextColor(bufferDC, RGB(255, 255, 255));
	
	TCHAR str[128];
	sprintf_s(str, "%2.1f", 34 + 2.9 * hp);
	TextOut(bufferDC, WIN_SIZE_X / 2 - 13, 36, str, strlen(str));

	//무기 선택 체크
	int weapon = _player->getWeapon();
	IMAGEMANAGER->render("icon weapon pistol", bufferDC, WIN_SIZE_X - 200, 2, (weapon == Player::PLAYER_WEAPON_PISTOL) ? 255 : 100);
	IMAGEMANAGER->render("icon weapon smg", bufferDC, WIN_SIZE_X - 150, 2, (weapon == Player::PLAYER_WEAPON_SMG) ? 255 : 100);
	IMAGEMANAGER->render("icon weapon sniper", bufferDC, WIN_SIZE_X - 100, 2, (weapon == Player::PLAYER_WEAPON_SNIPER) ? 255 : 100);
	IMAGEMANAGER->render("icon weapon bomb", bufferDC, WIN_SIZE_X - 50, 2, (weapon == Player::PLAYER_WEAPON_WATERBOMB) ? 255 : 100);

	//킬수
	sprintf_s(str, "남은 수 : %3d", _killNum);
	TextOut(bufferDC, WIN_SIZE_X - 120, 66, str, strlen(str));
}