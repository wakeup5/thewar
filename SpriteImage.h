#pragma once
#include "Image.h"
#include "TimeManager.h"

class Image;
class SpriteImage
{
private:
	Image* _image;

	float _centerX;
	float _centerY;

	int _currentFrameCol;
	int _currentFrameRow;
	int _maxFrameCol;
	int _maxFrameRow;
	int _frameWidth;
	int _frameHeight;

	int _frameNum;

	int _time = 0;
	CheckTimer* _timer;

	RECT _imageScale;

	void setBoundingBox()
	{
		_imageScale = makeRectCenter(_centerX, _centerY, _frameWidth, _frameHeight);
	}
public:
	SpriteImage();
	virtual ~SpriteImage();

	//프레임 관련
	//폭 높이와 행열 갯수
	HRESULT initialize(Image* image, int frameColumn, int frameRow);
	HRESULT initialize(Image* image, float centerX, float centerY, int frameColumn, int frameRow);

	//프레임 렌더
	virtual void render(HDC hdc, BYTE alpha = 255);
	virtual void render(HDC hdc, float destX, float destY, BYTE alpha = 255);

	void setImage(Image* image){ _image = image; }
	Image* getImage(){ return _image; }
	virtual void release();

	RECT getRect(){ setBoundingBox(); return _imageScale; }

	inline void setFrameX(int frameX)
	{
		if (frameX > _maxFrameCol) _currentFrameCol = _maxFrameCol;
		else if (frameX < 0) _currentFrameCol = 0;
		else _currentFrameCol = frameX;
	}
	inline void setFrameY(int frameY)
	{
		if (frameY > _maxFrameRow) _currentFrameRow = _maxFrameRow;
		else if (frameY < 0) _currentFrameRow = 0;
		else _currentFrameRow = frameY;
	}

	void setCenter(float x, float y){ _centerX = x; _centerY = y; }
	void setX(float x){ _centerX = x; }
	void setY(float y){ _centerY = y; }

	POINT getCenter(){ return POINT{ _centerX, _centerY }; }
	float getX(){ return _centerX; }
	float getY(){ return _centerY; }

	inline int getMaxFrameX(){ return _maxFrameCol; }
	inline int getMaxFrameY(){ return _maxFrameRow; }

	inline int getFrameX(){ return _currentFrameCol; }
	inline int getFrameY(){ return _currentFrameRow; }

	inline int getFrameWidth(){ return _frameWidth; }
	inline int getFrameHeight(){ return _frameHeight; }

	void nextFrameX();
	void nextFrameY();
	void prevFrameX();
	void prevFrameY();

	void nextFrame();
	void prevFrame();

	void nextFrameX(float mSecond);
	void nextFrameY(float mSecond);
	void prevFrameX(float mSecond);
	void prevFrameY(float mSecond);

	void nextFrame(float mSecond);
	void prevFrame(float mSecond);
};

