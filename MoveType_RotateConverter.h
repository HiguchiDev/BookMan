#pragma once
#include "MoveType.h"
#include "Direction.h"
#include <unordered_map>

class MoveType_RotateConverter
{
private:
	std::unordered_map < Direction::Directions, std::unordered_map<MoveType::MoveTypes, float> > _rotateMap;
public:
	float getRotate(Direction::Directions CAMERADIRECTION, MoveType::MoveTypes CHARACTERMOVETYPE);
	MoveType_RotateConverter();
	~MoveType_RotateConverter();
};

