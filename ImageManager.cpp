#include "stdafx.h"
#include "ImageManager.h"


ImageManager::ImageManager()
{
}


ImageManager::~ImageManager()
{
}

HRESULT ImageManager::initialize()
{
	return S_OK;
}

void ImageManager::release()
{
	removeAll();
}

Image* ImageManager::addImage(std::string key, int width, int height)
{
	Image *image = findImage(key);

	if (image != NULL)
	{
		return image;
	}

	image = new Image();

	if (FAILED(image->initialize(width, height)))
	{
		SAFE_DELETE(image);
		return NULL;
	}

	_imageMap.insert(std::make_pair(key, image));

	return image;
}

Image* ImageManager::addImage(std::string key, const char* fileName, int width, int height, BOOL trans, COLORREF transColor)
{
	Image *image = findImage(key);

	if (image != NULL)
	{
		return image;
	}

	image = new Image();

	if (FAILED(image->initialize(fileName, width, height, trans, transColor)))
	{
		SAFE_DELETE(image);
		return NULL;
	}

	_imageMap.insert(std::make_pair(key, image));

	return image;
}

Image* ImageManager::addImage(std::string key, const char* fileName, float centerX, float centerY, int width, int height, BOOL trans, COLORREF transColor)
{
	Image *image = findImage(key);

	if (image != NULL)
	{
		return image;
	}

	image = new Image();

	if (FAILED(image->initialize(fileName, centerX, centerY, width, height, trans, transColor)))
	{
		SAFE_DELETE(image);
		return NULL;
	}

	_imageMap.insert(std::make_pair(key, image));

	return image;
}

SpriteImage* ImageManager::addSpriteImage(std::string key, const char* fileName, int width, int height, int frameColumn, int frameRow, BOOL trans, COLORREF transColor)
{
	Image* image = addImage(key, fileName, width, height, trans, transColor);
	SpriteImage* spriteImage;
	if (image == NULL)
	{
		return NULL;
	}

	spriteImage = image->getSpriteImage(frameColumn, frameRow);
	return spriteImage;
}

SpriteImage* ImageManager::addSpriteImage(std::string key, const char* fileName, float centerX, float centerY, int width, int height, int frameColumn, int frameRow, BOOL trans, COLORREF transColor)
{
	Image* image = addImage(key, fileName, width, height, trans, transColor);
	SpriteImage* spriteImage;
	if (image == NULL)
	{
		return NULL;
	}

	spriteImage = image->getSpriteImage(centerX, centerY, frameColumn, frameRow);
	return spriteImage;
}

Image* ImageManager::findImage(std::string key)
{
	ImageMapIter imageIter = _imageMap.find(key);

	if (imageIter != _imageMap.end())
	{
		return imageIter->second;
	}

	return NULL;
}

bool ImageManager::removeImage(std::string key)
{
	ImageMapIter imageIter = _imageMap.find(key);

	if (imageIter != _imageMap.end())
	{
		imageIter->second->release();
		SAFE_DELETE(imageIter->second);
		_imageMap.erase(imageIter);
		return true;
	}

	return false;
}

bool ImageManager::removeAll()
{
	if (!_imageMap.empty())
	{
		for (auto iter = _imageMap.begin(); iter != _imageMap.end();)
		{
			if (iter->second != NULL)
			{
				iter->second->release();
				SAFE_DELETE(iter->second);
				iter = _imageMap.erase(iter);
			}
			else
			{
				iter++;
			}
		}
		_imageMap.clear();  
		return true;
	}

	return false;
}

void ImageManager::render(std::string key, HDC hdc, BYTE alpha)
{
	Image *image = findImage(key);

	if (image)
	{
		image->render(hdc, alpha);
	}
}
void ImageManager::render(std::string key, HDC hdc, float destX, float destY, BYTE alpha)
{
	Image *image = findImage(key);

	if (image)
	{
		image->render(hdc, destX, destY, alpha);
	}
}

void ImageManager::render(std::string key, HDC hdc, int sourX, int sourY, int width, int height, BYTE alpha)
{
	Image *image = findImage(key);

	if (image)
	{
		image->render(hdc, sourX, sourY, width, height, alpha);
	}
}
void ImageManager::render(std::string key, HDC hdc, float destX, float destY, int sourX, int sourY, int width, int height, BYTE alpha)
{
	Image *image = findImage(key);

	if (image)
	{
		image->render(hdc, destX, destY, sourX, sourY, width, height, alpha);
	}
}