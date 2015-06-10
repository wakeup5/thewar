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

/// 빈 비트맵 생성
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

	//이미지 리소스를 얻는데 실패하면
	if (_imageInfo->hBit == 0)
	{
		release();
		return E_FAIL;
	}

	return S_OK;
}
/// 이미지 로드 : 파일 명, 이미지 폭, 이미지 높이, 제외여부, 제외할 색
HRESULT Image::initialize(const char* fileName, int width, int height, BOOL trans, COLORREF transColor)
{
	return initialize(fileName, width / 2, height / 2, width, height, trans, transColor);
}
/// 이미지 로드 : 파일 명, 중심 좌표 x, 중심 좌표 y, 이미지 폭, 이미지 높이, 제외여부, 제외할 색
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

	//이미지 리소스를 얻는데 실패하면
	if (_imageInfo->hBit == 0)
	{
		release();
		return E_FAIL;
	}

	return S_OK;
}

/// 이미지 자원 반환
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
		//주소값 비교?
		if (sprite == *iter)
		{
			SAFE_DELETE((*iter));
			_vSpriteImage.erase(iter);
			break;
		}
	}
}

//투명키 값 설정
void Image::setTransColor(BOOL trans, COLORREF transColor)
{
	_trans = trans;
	_transColor = transColor;
}

/// 일반 렌더링
void Image::render(HDC hdc, BYTE alpha)
{
	render(hdc, _centerX - _width / 2, _centerY - _height / 2, 0, 0, _width, _height, alpha);
}
/// 일반 렌더링 : 원본이미지의 상단 좌측 좌표 x, y, 잘라낼 폭, 잘라낼 높이
void Image::render(HDC hdc, int sourX, int sourY, int width, int height, BYTE alpha)
{
	render(hdc, _centerX - width / 2, _centerY - height / 2, sourX, sourY, width, height, alpha);
}

/// 이미지 객체의 중심 좌표를 무시하고 원하는 좌표에 그릴 수 있다.
/// 위치 렌더링 : 화면에 그릴 위치 x, y
void Image::render(HDC hdc, float destX, float destY, BYTE alpha)
{
	render(hdc, destX, destY, 0, 0, _width, _height, alpha);
}
/// 위치 렌더링 : 화면에 그릴 위치 x, y, 원본이미지의 상단 좌측 좌표 x, y, 잘라낼 폭, 잘라낼 높이
void Image::render(HDC hdc, float destX, float destY, int sourX, int sourY, int width, int height, BYTE alpha)
{
	//투명도가 있으면
	if (alpha != 255)
	{
		alphaRender(hdc, destX, destY, sourX, sourY, width, height, alpha);
		return;
	}

	//투명도가 없으면
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

	//투명처리를 할 경우
	if (_trans)
	{
		//알파블렌더에 문제가 있는듯. 화면 밖을 복사 하려면 안나옴.
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

		//이미지 위치와 크기만큼 배경 DC의 그림을 가져와 blendImage에 복사.
		BitBlt(_blendImage->hMemDC, destX, destY, width, height, hdc, destX, destY, SRCCOPY);

		//blendImage에 이미지를 복사
		GdiTransparentBlt(_blendImage->hMemDC, destX, destY, width, height, _imageInfo->hMemDC, sourX, sourY, width, height, _transColor);

		//투명도를 지정하여 배경DC에 이미지를 범위만큼 복사.
		AlphaBlend(hdc, destX, destY, width, height, _blendImage->hMemDC, destX, destY, width, height, _blendFunc);

	}
	//하지 않을 경우
	else
	{
		AlphaBlend(hdc, destX, destY, width, height, _blendImage->hMemDC, sourX, sourY, width, height, _blendFunc);
	}
}