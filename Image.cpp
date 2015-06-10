#include "stdafx.h"
#include "Image.h"

#pragma comment (lib, "msimg32.lib")

Image::Image() 
	:_imageInfo(NULL),
	_fileName(NULL),
	_trans(NULL),
	_transColor(RGB(0, 0, 0)),
	_blendImage(NULL)
{

}

Image::~Image()
{

}

/// �� ��Ʈ�� ����
HRESULT Image::initialize(int width, int height)
{
	if (_imageInfo != NULL) release();

	HDC hdc = GetDC(_hWnd);

	_imageInfo = new ImageInfo;
	_imageInfo->resID = 0;
	_imageInfo->hMemDC = CreateCompatibleDC(hdc);
	_imageInfo->hBit = (HBITMAP)CreateCompatibleBitmap(hdc, width, height);
	_imageInfo->hOBit = (HBITMAP)SelectObject(_imageInfo->hMemDC, _imageInfo->hBit);

	_fileName = NULL;

	_trans = FALSE;
	_transColor = RGB(0, 0, 0);

	_blendFunc.BlendFlags = 0;
	_blendFunc.AlphaFormat = 0;
	_blendFunc.BlendOp = AC_SRC_OVER;

	_blendImage = new ImageInfo;
	_blendImage->resID = 0;
	_blendImage->hMemDC = CreateCompatibleDC(hdc);
	_blendImage->hBit = (HBITMAP)CreateCompatibleBitmap(hdc, WIN_SIZE_X, WIN_SIZE_Y);
	_blendImage->hOBit = (HBITMAP)SelectObject(_blendImage->hMemDC, _blendImage->hBit);

	ReleaseDC(_hWnd, hdc);

	_width = width;
	_height = height;
	_centerX = width / 2;
	_centerY = height / 2;

	setBoundingBox();

	//�̹��� ���ҽ��� ��µ� �����ϸ�
	if (_imageInfo->hBit == 0)
	{
		release();
		return E_FAIL;
	}

	return S_OK;
}
/// �̹��� �ε� : ���� ��, �̹��� ��, �̹��� ����, ���ܿ���, ������ ��
HRESULT Image::initialize(const char* fileName, int width, int height, BOOL trans, COLORREF transColor)
{
	return initialize(fileName, width / 2, height / 2, width, height, trans, transColor);
}
/// �̹��� �ε� : ���� ��, �߽� ��ǥ x, �߽� ��ǥ y, �̹��� ��, �̹��� ����, ���ܿ���, ������ ��
HRESULT Image::initialize(const char* fileName, float centerX, float centerY, int width, int height, BOOL trans, COLORREF transColor)
{
	if (_imageInfo != NULL) release();

	HDC hdc = GetDC(_hWnd);

	_imageInfo = new ImageInfo;
	_imageInfo->resID = 0;
	_imageInfo->hMemDC = CreateCompatibleDC(hdc);
	_imageInfo->hBit = (HBITMAP)LoadImage(_hInstance, fileName, IMAGE_BITMAP, width, height, LR_LOADFROMFILE);
	_imageInfo->hOBit = (HBITMAP)SelectObject(_imageInfo->hMemDC, _imageInfo->hBit);

	_fileName = NULL;

	_trans = trans;
	_transColor = transColor;

	_blendFunc.BlendFlags = 0;
	_blendFunc.AlphaFormat = 0;
	_blendFunc.BlendOp = AC_SRC_OVER;

	_blendImage = new ImageInfo;
	_blendImage->resID = 0;
	_blendImage->hMemDC = CreateCompatibleDC(hdc);
	_blendImage->hBit = (HBITMAP)CreateCompatibleBitmap(hdc, WIN_SIZE_X, WIN_SIZE_Y);
	_blendImage->hOBit = (HBITMAP)SelectObject(_blendImage->hMemDC, _blendImage->hBit);

	ReleaseDC(_hWnd, hdc);

	_width = width;
	_height = height;
	_centerX = centerX;
	_centerY = centerY;

	setBoundingBox();

	//�̹��� ���ҽ��� ��µ� �����ϸ�
	if (_imageInfo->hBit == 0)
	{
		release();
		return E_FAIL;
	}

	return S_OK;
}

/// �̹��� �ڿ� ��ȯ
void Image::release(void)
{
	if (_imageInfo)
	{
		SelectObject(_imageInfo->hMemDC, _imageInfo->hOBit);
		DeleteObject(_imageInfo->hBit);
		DeleteDC(_imageInfo->hMemDC);

		SelectObject(_blendImage->hMemDC, _blendImage->hOBit);
		DeleteObject(_blendImage->hBit);
		DeleteDC(_blendImage->hMemDC);

		SAFE_DELETE(_imageInfo);
		SAFE_DELETE(_blendImage);
		SAFE_DELETE(_fileName);

		_trans = FALSE;
		_transColor = RGB(0, 0, 0);
	}

	std::vector<SpriteImage*>::iterator iter;
	for (iter = _vSpriteImage.begin(); iter != _vSpriteImage.end();)
	{
		SAFE_DELETE((*iter));
		iter = _vSpriteImage.erase(iter);
	}

	_vSpriteImage.clear();
}

SpriteImage* Image::getSpriteImage(int frameCol, int frameRow)
{
	SpriteImage* sprite = new SpriteImage();

	sprite->initialize(this, frameCol, frameRow);

	_vSpriteImage.push_back(sprite);

	return sprite;
}

SpriteImage* Image::getSpriteImage(float centerX, float centerY, int frameCol, int frameRow)
{
	SpriteImage* sprite = new SpriteImage();

	sprite->initialize(this, centerX, centerY, frameCol, frameRow);

	_vSpriteImage.push_back(sprite);

	return sprite;
}

void Image::removeSpriteImage(SpriteImage* sprite)
{
	std::vector<SpriteImage*>::iterator iter;
	for (iter = _vSpriteImage.begin(); iter != _vSpriteImage.end(); iter++)
	{
		//�ּҰ� ��?
		if (sprite == *iter)
		{
			SAFE_DELETE((*iter));
			_vSpriteImage.erase(iter);
			break;
		}
	}
}

//����Ű �� ����
void Image::setTransColor(BOOL trans, COLORREF transColor)
{
	_trans = trans;
	_transColor = transColor;
}

/// �Ϲ� ������
void Image::render(HDC hdc, BYTE alpha)
{
	render(hdc, _centerX - _width / 2, _centerY - _height / 2, 0, 0, _width, _height, alpha);
}
/// �Ϲ� ������ : �����̹����� ��� ���� ��ǥ x, y, �߶� ��, �߶� ����
void Image::render(HDC hdc, int sourX, int sourY, int width, int height, BYTE alpha)
{
	render(hdc, _centerX - width / 2, _centerY - height / 2, sourX, sourY, width, height, alpha);
}

/// �̹��� ��ü�� �߽� ��ǥ�� �����ϰ� ���ϴ� ��ǥ�� �׸� �� �ִ�.
/// ��ġ ������ : ȭ�鿡 �׸� ��ġ x, y
void Image::render(HDC hdc, float destX, float destY, BYTE alpha)
{
	render(hdc, destX, destY, 0, 0, _width, _height, alpha);
}
/// ��ġ ������ : ȭ�鿡 �׸� ��ġ x, y, �����̹����� ��� ���� ��ǥ x, y, �߶� ��, �߶� ����
void Image::render(HDC hdc, float destX, float destY, int sourX, int sourY, int width, int height, BYTE alpha)
{
	//������ ������
	if (alpha != 255)
	{
		alphaRender(hdc, destX, destY, sourX, sourY, width, height, alpha);
		return;
	}

	//������ ������
	if (_trans)
	{
		//GdiTransparentBlt(_imageInfo->hMemDC, sourX, sourX, width, height, _imageInfo->hMemDC, sourX, sourY, width, height, _transColor);
		GdiTransparentBlt(hdc, destX, destY, width, height, _imageInfo->hMemDC, sourX, sourY, width, height, _transColor);
		//GdiTransparentBlt(hdc, destX, destY, width, height, _imageInfo->hMemDC, sourX, sourY, width, height, _transColor);
	}
	else
	{
		BitBlt(hdc, destX, destY, width, height, _imageInfo->hMemDC, sourX, sourY, SRCCOPY);
	}

}

void Image::alphaRender(HDC hdc, float destX, float destY, int sourX, int sourY, int width, int height, BYTE alpha)
{
	_blendFunc.SourceConstantAlpha = alpha;

	//����ó���� �� ���
	if (_trans)
	{
		//���ĺ����� ������ �ִµ�. ȭ�� ���� ���� �Ϸ��� �ȳ���.
		if (destX + width > WIN_SIZE_X) width = WIN_SIZE_X - destX;
		if (destY + height > WIN_SIZE_Y) height = WIN_SIZE_Y - destY;
		if (destX < 0)
		{
			sourX -= destX;
			width += destX;
			destX = 0;
		}
		if (destY < 0)
		{
			sourY -= destY;
			height += destY;
			destY = 0;
		}

		//�̹��� ��ġ�� ũ�⸸ŭ ��� DC�� �׸��� ������ blendImage�� ����.
		BitBlt(_blendImage->hMemDC, destX, destY, width, height, hdc, destX, destY, SRCCOPY);

		//blendImage�� �̹����� ����
		GdiTransparentBlt(_blendImage->hMemDC, destX, destY, width, height, _imageInfo->hMemDC, sourX, sourY, width, height, _transColor);

		//������ �����Ͽ� ���DC�� �̹����� ������ŭ ����.
		AlphaBlend(hdc, destX, destY, width, height, _blendImage->hMemDC, destX, destY, width, height, _blendFunc);

	}
	//���� ���� ���
	else
	{
		AlphaBlend(hdc, destX, destY, width, height, _blendImage->hMemDC, sourX, sourY, width, height, _blendFunc);
	}
}