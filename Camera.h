#pragma once
#include "SingletonBase.h"
class Camera : public SingletonBase < Camera >
{
private:
	Image* _cameraBuffer;
	float _x;
	float _y;
public:
	Camera();
	~Camera();

	HRESULT initialize();
	void release();
	HDC getCameraDC();
	void render(HDC);

	void setX(float x);
	void setY(float y);
	float getX();
	float getY();

	POINT getMousePoint();
	int getMouseX();
	int getMouseY();
};

