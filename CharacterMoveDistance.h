#pragma once
#include "Direction.h"
#include <unordered_map>
#include <vector>
#include "FieldType.h"
#include "MoveType.h"
#include <memory>

class Position;
class CharacterMoveDistance
{
private:
	std::unordered_map<Direction::Directions, std::unordered_map<MoveType::MoveTypes, std::unordered_map<FieldType::FieldTypes, int>>> _distanceMap;
public:
	int getRowDistance(Direction::Directions CAMERADIRECTION, MoveType::MoveTypes CHARACTERMOVETYPE);
	int getColumnDistance(Direction::Directions CAMERADIRECTION, MoveType::MoveTypes CHARACTERMOVETYPE);
	int getHeightDistance(Direction::Directions CAMERADIRECTION, MoveType::MoveTypes CHARACTERMOVETYPE);
	CharacterMoveDistance();
	~CharacterMoveDistance();
};

