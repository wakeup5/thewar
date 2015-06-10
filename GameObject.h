#pragma once
class GameObject : public GameNode
{
protected:
	float _centerX;
	float _centerY;

	int _width;
	int _height;

	float _speedX;
	float _speedY;

	float _angleD;
	float _angleR;

	float _speed;

	RECT _rect;

public:
	GameObject();
	~GameObject();

	void initialize(float centerX, float centerY, int width = 0, int height = 0, float angleD = 0.0f, float speed = 0.0f);

	void setPosition(POINT p) { _centerX = p.x, _centerY = p.y; updateRect(); }
	void setPosition(float x, float y) { _centerX = x, _centerY = y; updateRect(); }
	POINT getPosition(){ return POINT{ _centerX, _centerY }; }

	void setX(float x){ _centerX = x; updateRect(); }
	void setY(float y){ _centerY = y; updateRect(); }
	float getY(){ return _centerY; }
	float getX(){ return _centerX; }

	void setWidth(int width){ _width = width; updateRect(); }
	void setHeight(int height){ _height = height; updateRect(); }
	void setSize(int width, int height){ _width = width; _height = height; updateRect(); }

	int getWidth(){ return _width; }
	int getHeight(){ return _height; }
	void updateRect(){ _rect = makeRectCenter(_centerX, _centerY, _width, _height); }
	RECT getRect(){ return _rect; }
	RECT getUpdateRect() { updateRect(); return _rect; }

	void setAngleD(float angleD);
	float getAngleD();

	void setAngleR(float angleR);
	float getAngleR();

	void setSpeedX(float speedX);
	float getSpeedX();

	void setSpeedY(float speedY);
	float getSpeedY();

	void setSpeed(float speed);
	float getSpeed();

	void activate();
};

