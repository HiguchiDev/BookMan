#pragma once
#include <map>
#include "Direction.h"
#include "DxLib.h"

class Direction_AngleConverter
{
private:
	std::map<Direction::Directions, float> _map;
public:
	float getAngle(Direction::Directions DIRECTION);

	Direction_AngleConverter();
	~Direction_AngleConverter();
};

