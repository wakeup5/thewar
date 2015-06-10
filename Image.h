/**
@file   Image.h
@author ������(wlsgks5@naver.com)
@date   2015/05/26
*/
#pragma once
#include "SpriteImage.h"
/**
@class	Image
@author	������(wlsgks5@naver.com)
@date	2015/05/26
@brief	�̹����� �̹����� ��ġ, ũ��, �������� ���� Ŭ����
*/
class SpriteImage;
class Image
{
protected:
	/// �̹��� �ε� Ÿ��
	enum IMAGE_LOAD_KIND
	{
		LOAD_RESOURCES = 0, //���ҽ� �ε�
		LOAD_FILE,			//���Ϸε�
		LOAD_EMPTY,			//�ƹ��͵� ���� �̹���
		LOAD_END			//�̳ѹ��� �� Ȥ�� ����
	};

	/// �̹����� ���� �� �޸� DC ����ü
	typedef struct tagImageInfo
	{
		DWORD resID;
		HDC hMemDC;
		HBITMAP hBit;
		HBITMAP hOBit;

		tagImageInfo()
		{
			resID = 0;
			hMemDC = NULL;
			hBit = NULL;
			hOBit = NULL;
		};

	}ImageInfo;

	/// �̹��� ��
	int _width;
	/// �̹��� ����
	int _height;
	
	/// �̹��� �߽� ��ǥ x
	float _centerX;
	/// �̹��� �߽� ��ǥ y
	float _centerY;

	/// �̹����� ��ġ�� ũ��
	RECT _imageScale;

	/// �̹����� ������ DC
	ImageInfo *_imageInfo;
	/// �̹��� ���� ���, ���ϸ�
	CHAR* _fileName;
	/// ������ ������ �ִ����� ����
	bool _trans;
	/// ������ ����
	COLORREF _transColor;

	/// ���� ���� ��
	BLENDFUNCTION _blendFunc;
	/// ���� �̹����� ������ �޸�DC
	ImageInfo *_blendImage;

	std::vector<SpriteImage*> _vSpriteImage;

	virtual void setBoundingBox()
	{
		_imageScale = makeRectCenter(_centerX, _centerY, _width, _height);
	}

	/// ���� ���� ���
	void alphaRender(HDC hdc, float destX, float destY, int sourX, int sourY, int width, int height, BYTE alpha);
public:
	Image();
	~Image();
	/// �� ��Ʈ�� ����
	HRESULT initialize(int width, int height);
	/// �̹��� �ε� : ���� ��, �̹��� ��, �̹��� ����, ���ܿ���, ������ ��
	HRESULT initialize(const char* fileName, int width, int height, BOOL trans = FALSE, COLORREF transColor = RGB(0, 0, 0));
	/// �̹��� �ε� : ���� ��, �߽� ��ǥ x, �߽� ��ǥ y, �̹��� ��, �̹��� ����, ���ܿ���, ������ ��
	HRESULT initialize(const char* fileName, float centerX, float centerY, int width, int height, BOOL trans = FALSE, COLORREF transColor = RGB(0, 0, 0));

	/// �̹��� �ڿ� ��ȯ
	void release(void);

	SpriteImage* getSpriteImage(int frameCol, int frameRow);
	SpriteImage* getSpriteImage(float centerX, float centerY, int frameCol, int frameRow);

	void removeSpriteImage(SpriteImage*);

	//����Ű �� ����
	void setTransColor(BOOL trans, COLORREF transColor);

	/// �Ϲ� ������
	virtual void render(HDC hdc, BYTE alpha = 255);
	/// �Ϲ� ������ : �����̹����� ��� ���� ��ǥ x, y, �߶� ��, �߶� ����
	void render(HDC hdc, int sourX, int sourY, int width, int height, BYTE alpha = 255);

	/// �̹��� ��ü�� �߽� ��ǥ�� �����ϰ� ���ϴ� ��ǥ�� �׸� �� �ִ�.
	/// ��ġ ������ : ȭ�鿡 �׸� ��ġ x, y
	virtual void render(HDC hdc, float destX, float destY, BYTE alpha = 255);
	/// ��ġ ������ : ȭ�鿡 �׸� ��ġ x, y, �����̹����� ��� ���� ��ǥ x, y, �߶� ��, �߶� ����
	void render(HDC hdc, float destX, float destY, int sourX, int sourY, int width, int height, BYTE alpha = 255);

	/// DC���
	inline HDC getMemDC(){ return _imageInfo->hMemDC; }

	/// �߽� ��ǥ x ����
	inline void setX(float x){ _centerX = x; setBoundingBox(); }
	/// �߽� ��ǥ x ��ȯ
	inline float getX(){ return _centerX; }

	/// �߽� ��ǥ y ����
	inline void setY(float y){ _centerY = y; setBoundingBox(); }
	/// �߽� ��ǥ y ��ȯ
	inline float getY(){ return _centerY; }

	/// �߽� ��ǥ x, y ����
	inline void setCenter(float x, float y){ _centerX = x; _centerY = y; setBoundingBox(); }

	/// ���� �ػ� ��ȯ
	inline int getWidth(){ return _width; }

	/// ���� �ػ� ��ȯ
	inline int getHeight(){ return _height; }

	/// �ٿ�� �ڽ� ��ȯ
	inline RECT boundingBox(){ return _imageScale; }

};

