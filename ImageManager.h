/**
@file	ImageManager.h
@author	박진한(wlsgks5@naver.com)
@date	2015/05/29
*/
#pragma once
#include "SingletonBase.h"
#include <map>
#include <string>
#include "Image.h"
#include "SpriteImage.h"

/**
@class	ImageManager : SingletonBase
@author	박진한(wlsgks5@naver.com)
@date	2015/05/29
@breif	이미지, 스프라이트 이미지들을 관리하기 위한 클래스
*/
class ImageManager : public SingletonBase < ImageManager >
{
public:
	typedef std::map<std::string, Image*> ImageMap;
	typedef std::map<std::string, Image*>::iterator ImageMapIter;
	//typedef std::map<std::string, SpriteImage*> SpriteImageMap;
	//typedef std::map<std::string, SpriteImage*>::iterator SpriteImageMapIter;

private:
	ImageMap _imageMap;
	ImageMapIter _imageMapIter;
	//SpriteImageMap _imageMap;
	//SpriteImageMapIter _imageMapIter;

public:
	ImageManager();
	~ImageManager();

	HRESULT initialize();
	void release();

	Image* addImage(std::string key, int width, int height);
	Image* addImage(std::string key, const char* fileName, int width, int height, BOOL trans = FALSE, COLORREF transColor = RGB(0, 0, 0));
	Image* addImage(std::string key, const char* fileName, float centerX, float centerY, int width, int height, BOOL trans = FALSE, COLORREF transColor = RGB(0, 0, 0));
	SpriteImage* addSpriteImage(std::string key, const char* fileName, int width, int height, int frameColumn, int frameRow, BOOL trans = FALSE, COLORREF transColor = RGB(0, 0, 0));
	SpriteImage* addSpriteImage(std::string key, const char* fileName, float centerX, float centerY, int width, int height, int frameColumn, int frameRow, BOOL trans = FALSE, COLORREF transColor = RGB(0, 0, 0));

	void render(std::string key, HDC hdc, BYTE alpha = 255);
	void render(std::string key, HDC hdc, float destX, float destY, BYTE alpha = 255);

	void render(std::string key, HDC hdc, int sourX, int sourY, int width, int height, BYTE alpha = 255);
	void render(std::string key, HDC hdc, float destX, float destY, int sourX, int sourY, int width, int height, BYTE alpha = 255);

	Image* findImage(std::string key);

	bool removeImage(std::string key);
	bool removeAll();

};