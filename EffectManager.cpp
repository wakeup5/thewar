#include "stdafx.h"
#include "EffectManager.h"


EffectManager::EffectManager()
{
}


EffectManager::~EffectManager()
{
}

HRESULT EffectManager::initialize()
{
	return S_OK;
}
void EffectManager::release()
{
	for (_viEffect = _vEffect.begin(); _viEffect != _vEffect.end(); _viEffect++)
	{
		_viEffect = _vEffect.erase(_viEffect);
	}

	_vEffect.clear();
}
void EffectManager::update()
{
	for (_viEffect = _vEffect.begin(); _viEffect != _vEffect.end();)
	{
		(*_viEffect)->nextFrame(20);
		if ((*_viEffect)->getFrameX() >= (*_viEffect)->getMaxFrameX() && (*_viEffect)->getFrameY() >= (*_viEffect)->getMaxFrameY())
		{
			(*_viEffect)->release();
			_viEffect = _vEffect.erase(_viEffect);
		}
		else
		{
			_viEffect++;
		}
	}
}
void EffectManager::render(HDC hdc)
{
	for (_viEffect = _vEffect.begin(); _viEffect != _vEffect.end(); _viEffect++)
	{
		(*_viEffect)->render(hdc);
	}
}

void EffectManager::addEffect(SpriteImage* spriteEffect)
{
	if (spriteEffect != NULL) _vEffect.push_back(spriteEffect);
}