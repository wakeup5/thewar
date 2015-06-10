/**
@file   Image.h
@author 박진한(wlsgks5@naver.com)
@date   2015/05/26
*/
#pragma once
#include "SpriteImage.h"
/**
@class	Image
@author	박진한(wlsgks5@naver.com)
@date	2015/05/26
@brief	이미지와 이미지의 위치, 크기, 투명도값을 가진 클래스
*/
class SpriteImage;
class Image
{
protected:
	/// 이미지 로드 타입
	enum IMAGE_LOAD_KIND
	{
		LOAD_RESOURCES = 0, //리소스 로드
		LOAD_FILE,			//파일로드
		LOAD_EMPTY,			//아무것도 없는 이미지
		LOAD_END			//이넘문의 끝 혹은 길이
	};

	/// 이미지를 저장 할 메모리 DC 구조체
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

	/// 이미지 폭
	int _width;
	/// 이미지 높이
	int _height;
	
	/// 이미지 중심 좌표 x
	float _centerX;
	/// 이미지 중심 좌표 y
	float _centerY;

	/// 이미지가 위치한 크기
	RECT _imageScale;

	/// 이미지를 저장할 DC
	ImageInfo *_imageInfo;
	/// 이미지 파일 경로, 파일명
	CHAR* _fileName;
	/// 제외할 색상이 있는지의 여부
	bool _trans;
	/// 제외할 색상
	COLORREF _transColor;

	/// 투명도 설정 값
	BLENDFUNCTION _blendFunc;
	/// 투명 이미지를 적용할 메모리DC
	ImageInfo *_blendImage;

	std::vector<SpriteImage*> _vSpriteImage;

	virtual void setBoundingBox()
	{
		_imageScale = makeRectCenter(_centerX, _centerY, _width, _height);
	}

	/// 투명 조절 출력
	void alphaRender(HDC hdc, float destX, float destY, int sourX, int sourY, int width, int height, BYTE alpha);
public:
	Image();
	~Image();
	/// 빈 비트맵 생성
	HRESULT initialize(int width, int height);
	/// 이미지 로드 : 파일 명, 이미지 폭, 이미지 높이, 제외여부, 제외할 색
	HRESULT initialize(const char* fileName, int width, int height, BOOL trans = FALSE, COLORREF transColor = RGB(0, 0, 0));
	/// 이미지 로드 : 파일 명, 중심 좌표 x, 중심 좌표 y, 이미지 폭, 이미지 높이, 제외여부, 제외할 색
	HRESULT initialize(const char* fileName, float centerX, float centerY, int width, int height, BOOL trans = FALSE, COLORREF transColor = RGB(0, 0, 0));

	/// 이미지 자원 반환
	void release(void);

	SpriteImage* getSpriteImage(int frameCol, int frameRow);
	SpriteImage* getSpriteImage(float centerX, float centerY, int frameCol, int frameRow);

	void removeSpriteImage(SpriteImage*);

	//투명키 값 설정
	void setTransColor(BOOL trans, COLORREF transColor);

	/// 일반 렌더링
	virtual void render(HDC hdc, BYTE alpha = 255);
	/// 일반 렌더링 : 원본이미지의 상단 좌측 좌표 x, y, 잘라낼 폭, 잘라낼 높이
	void render(HDC hdc, int sourX, int sourY, int width, int height, BYTE alpha = 255);

	/// 이미지 객체의 중심 좌표를 무시하고 원하는 좌표에 그릴 수 있다.
	/// 위치 렌더링 : 화면에 그릴 위치 x, y
	virtual void render(HDC hdc, float destX, float destY, BYTE alpha = 255);
	/// 위치 렌더링 : 화면에 그릴 위치 x, y, 원본이미지의 상단 좌측 좌표 x, y, 잘라낼 폭, 잘라낼 높이
	void render(HDC hdc, float destX, float destY, int sourX, int sourY, int width, int height, BYTE alpha = 255);

	/// DC얻기
	inline HDC getMemDC(){ return _imageInfo->hMemDC; }

	/// 중심 좌표 x 설정
	inline void setX(float x){ _centerX = x; setBoundingBox(); }
	/// 중심 좌표 x 반환
	inline float getX(){ return _centerX; }

	/// 중심 좌표 y 설정
	inline void setY(float y){ _centerY = y; setBoundingBox(); }
	/// 중심 좌표 y 반환
	inline float getY(){ return _centerY; }

	/// 중심 좌표 x, y 설정
	inline void setCenter(float x, float y){ _centerX = x; _centerY = y; setBoundingBox(); }

	/// 가로 해상도 반환
	inline int getWidth(){ return _width; }

	/// 세로 해상도 반환
	inline int getHeight(){ return _height; }

	/// 바운딩 박스 반환
	inline RECT boundingBox(){ return _imageScale; }

};

