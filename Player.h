#pragma once
#include "GameNode.h"
class Player : public GameObject
{
public:
	enum PLAYER_STATE
	{
		PLAYER_STATE_LEFT,
		PLAYER_STATE_RIGHT,
		PLAYER_STATE_STAY,
		PLAYER_STATE_JUMP
	};
private:
	SpriteImage* _moveImage;
	SpriteImage* _stayImage;
	SpriteImage* _armImage;

	PLAYER_STATE _playerState;

	float _hp;//퍼센테이지로 구현.

public:
	Player();
	~Player();

	HRESULT initialize();
	void release();
	void update();
	void render();
};

