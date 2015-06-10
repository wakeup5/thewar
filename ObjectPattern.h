#include "GameObject.h"
#include "stdafx.h"

#pragma once
class ObjectPattern
{
private:
	ObjectPattern();
	~ObjectPattern();

public:
	typedef enum OBJECT_PATTERN
	{
		PATTERN_MOVE_LEFT	= 0x00000001,
		PATTERN_MOVE_UP		= 0x00000002,
		PATTERN_MOVE_RIGHT	= 0x00000004,
		PATTERN_MOVE_DOWN	= 0x00000008,
		PATTERN_MOVE_POINT	= 0x10000000,
		PATTERN_STAY		= 0x00000000
	} PATTERN;

	static bool movePattern(GameObject* object, PATTERN pattern, int* destX = NULL, int* destY = NULL)
	{
		if (object == NULL) return false;

		if (destX == NULL) destX = new int(object->getX());
		if (destY == NULL) destY = new int(object->getY());

		switch (pattern)
		{
		case PATTERN_MOVE_LEFT:
			if (destX != NULL && *destX > object->getX())
			{
				return true;
			}
			else
			{
				//printf("%d, ", object->getX());
				object->setX(object->getX() - object->getSpeed());
				return false;
			}
		case PATTERN_MOVE_RIGHT:
			if (destX != NULL && *destX < object->getX())
			{
				return true;
			}
			else
			{
				object->setX(object->getX() + object->getSpeed());
				return false;
			}
		case PATTERN_MOVE_UP:
			if (destY != NULL && *destY > object->getY())
			{
				return true;
			}
			else
			{
				object->setY(object->getY() - object->getSpeed());
				return false;
			}
		case PATTERN_MOVE_DOWN:
			if (destY != NULL && *destY < object->getY())
			{
				return true;
			}
			else
			{
				object->setY(object->getY() + object->getSpeed());
				return false;
			}
		}

		return false;
	}
};

typedef ObjectPattern Pattern;
