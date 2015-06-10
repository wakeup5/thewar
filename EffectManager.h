#pragma once
#include "SingletonBase.h"
class EffectManager :
	public SingletonBase < EffectManager >
{
private:
	typedef std::vector<SpriteImage*> VSpriteImage;
	typedef std::vector<SpriteImage*>::iterator VISpriteImage;

	VSpriteImage _vEffect;
	VISpriteImage _viEffect;
public:
	EffectManager();
	~EffectManager();

	HRESULT initialize();
	void release();
	void update();
	void render(HDC hdc);

	void addEffect(SpriteImage* spriteEffect);
};

