#pragma once
#include "GameNode.h"
#include "StageObject.h"

typedef struct tagRectImage
{
	RECT r;
	Image* i;
}RectImage;

class Land : public GameNode
{
public:
private:
	Image* _floor;
	std::vector<RectImage> _vLand;

public:
	Land();
	~Land();

	HRESULT initialize(Image*, std::vector<RectImage>* = NULL);
	void release();
	void update();
	void render();

	const RECT* collisionLand(RECT);
	void collisionByStageObject(StageObject*);
	void collisionByUnit(Unit*);

	void collisionFloor(GameObject*);

	void addFloor(RectImage);
	void addFloors(Image* image, int sizeX, int sizeY, int startX, int startY, int num);
};

