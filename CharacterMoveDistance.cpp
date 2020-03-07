#include "CharacterMoveDistance.h"


CharacterMoveDistance::CharacterMoveDistance()
{
	//カメラが東を向いている時
	this->_distanceMap[Direction::Directions::EAST] = std::unordered_map < MoveType::MoveTypes, std::unordered_map< FieldType::FieldTypes, int >>();
	
	this->_distanceMap[Direction::Directions::EAST][MoveType::MoveTypes::LEFT][FieldType::FieldTypes::ROW] = -1;
	this->_distanceMap[Direction::Directions::EAST][MoveType::MoveTypes::LEFT][FieldType::FieldTypes::COLUMN] = 0;
	this->_distanceMap[Direction::Directions::EAST][MoveType::MoveTypes::LEFT][FieldType::FieldTypes::HEIGHT] = 0;

	this->_distanceMap[Direction::Directions::EAST][MoveType::MoveTypes::LEFTLOWER][FieldType::FieldTypes::ROW] = -1;
	this->_distanceMap[Direction::Directions::EAST][MoveType::MoveTypes::LEFTLOWER][FieldType::FieldTypes::COLUMN] = -1;
	this->_distanceMap[Direction::Directions::EAST][MoveType::MoveTypes::LEFTLOWER][FieldType::FieldTypes::HEIGHT] = 0;

	this->_distanceMap[Direction::Directions::EAST][MoveType::MoveTypes::LEFTUPPER][FieldType::FieldTypes::ROW] = -1;
	this->_distanceMap[Direction::Directions::EAST][MoveType::MoveTypes::LEFTUPPER][FieldType::FieldTypes::COLUMN] = 1;
	this->_distanceMap[Direction::Directions::EAST][MoveType::MoveTypes::LEFTUPPER][FieldType::FieldTypes::HEIGHT] = 0;

	this->_distanceMap[Direction::Directions::EAST][MoveType::MoveTypes::RIGHTLOWER][FieldType::FieldTypes::ROW] = 1;
	this->_distanceMap[Direction::Directions::EAST][MoveType::MoveTypes::RIGHTLOWER][FieldType::FieldTypes::COLUMN] = -1;
	this->_distanceMap[Direction::Directions::EAST][MoveType::MoveTypes::RIGHTLOWER][FieldType::FieldTypes::HEIGHT] = 0;

	this->_distanceMap[Direction::Directions::EAST][MoveType::MoveTypes::RIGHTUPPER][FieldType::FieldTypes::ROW] = 1;
	this->_distanceMap[Direction::Directions::EAST][MoveType::MoveTypes::RIGHTUPPER][FieldType::FieldTypes::COLUMN] = 1;
	this->_distanceMap[Direction::Directions::EAST][MoveType::MoveTypes::RIGHTUPPER][FieldType::FieldTypes::HEIGHT] = 0;

	this->_distanceMap[Direction::Directions::EAST][MoveType::MoveTypes::RIGHT][FieldType::FieldTypes::ROW] = 1;
	this->_distanceMap[Direction::Directions::EAST][MoveType::MoveTypes::RIGHT][FieldType::FieldTypes::COLUMN] = 0;
	this->_distanceMap[Direction::Directions::EAST][MoveType::MoveTypes::RIGHT][FieldType::FieldTypes::HEIGHT] = 0;

	this->_distanceMap[Direction::Directions::EAST][MoveType::MoveTypes::UP][FieldType::FieldTypes::ROW] = 0;
	this->_distanceMap[Direction::Directions::EAST][MoveType::MoveTypes::UP][FieldType::FieldTypes::COLUMN] = 1;
	this->_distanceMap[Direction::Directions::EAST][MoveType::MoveTypes::UP][FieldType::FieldTypes::HEIGHT] = 0;

	this->_distanceMap[Direction::Directions::EAST][MoveType::MoveTypes::DOWN][FieldType::FieldTypes::ROW] = 0;
	this->_distanceMap[Direction::Directions::EAST][MoveType::MoveTypes::DOWN][FieldType::FieldTypes::COLUMN] = -1;
	this->_distanceMap[Direction::Directions::EAST][MoveType::MoveTypes::DOWN][FieldType::FieldTypes::HEIGHT] = 0;


	//カメラが西を向いている時
	this->_distanceMap[Direction::Directions::WEST] = std::unordered_map < MoveType::MoveTypes, std::unordered_map< FieldType::FieldTypes, int >>();

	this->_distanceMap[Direction::Directions::WEST][MoveType::MoveTypes::LEFT][FieldType::FieldTypes::ROW] = 1;
	this->_distanceMap[Direction::Directions::WEST][MoveType::MoveTypes::LEFT][FieldType::FieldTypes::COLUMN] = 0;
	this->_distanceMap[Direction::Directions::WEST][MoveType::MoveTypes::LEFT][FieldType::FieldTypes::HEIGHT] = 0;

	this->_distanceMap[Direction::Directions::WEST][MoveType::MoveTypes::LEFTLOWER][FieldType::FieldTypes::ROW] = 1;
	this->_distanceMap[Direction::Directions::WEST][MoveType::MoveTypes::LEFTLOWER][FieldType::FieldTypes::COLUMN] = 1;
	this->_distanceMap[Direction::Directions::WEST][MoveType::MoveTypes::LEFTLOWER][FieldType::FieldTypes::HEIGHT] = 0;

	this->_distanceMap[Direction::Directions::WEST][MoveType::MoveTypes::LEFTUPPER][FieldType::FieldTypes::ROW] = 1;
	this->_distanceMap[Direction::Directions::WEST][MoveType::MoveTypes::LEFTUPPER][FieldType::FieldTypes::COLUMN] = -1;
	this->_distanceMap[Direction::Directions::WEST][MoveType::MoveTypes::LEFTUPPER][FieldType::FieldTypes::HEIGHT] = 0;

	this->_distanceMap[Direction::Directions::WEST][MoveType::MoveTypes::RIGHTLOWER][FieldType::FieldTypes::ROW] = -1;
	this->_distanceMap[Direction::Directions::WEST][MoveType::MoveTypes::RIGHTLOWER][FieldType::FieldTypes::COLUMN] = 1;
	this->_distanceMap[Direction::Directions::WEST][MoveType::MoveTypes::RIGHTLOWER][FieldType::FieldTypes::HEIGHT] = 0;

	this->_distanceMap[Direction::Directions::WEST][MoveType::MoveTypes::RIGHTUPPER][FieldType::FieldTypes::ROW] = -1;
	this->_distanceMap[Direction::Directions::WEST][MoveType::MoveTypes::RIGHTUPPER][FieldType::FieldTypes::COLUMN] = -1;
	this->_distanceMap[Direction::Directions::WEST][MoveType::MoveTypes::RIGHTUPPER][FieldType::FieldTypes::HEIGHT] = 0;

	this->_distanceMap[Direction::Directions::WEST][MoveType::MoveTypes::RIGHT][FieldType::FieldTypes::ROW] = -1;
	this->_distanceMap[Direction::Directions::WEST][MoveType::MoveTypes::RIGHT][FieldType::FieldTypes::COLUMN] = 0;
	this->_distanceMap[Direction::Directions::WEST][MoveType::MoveTypes::RIGHT][FieldType::FieldTypes::HEIGHT] = 0;

	this->_distanceMap[Direction::Directions::WEST][MoveType::MoveTypes::UP][FieldType::FieldTypes::ROW] = 0;
	this->_distanceMap[Direction::Directions::WEST][MoveType::MoveTypes::UP][FieldType::FieldTypes::COLUMN] = -1;
	this->_distanceMap[Direction::Directions::WEST][MoveType::MoveTypes::UP][FieldType::FieldTypes::HEIGHT] = 0;

	this->_distanceMap[Direction::Directions::WEST][MoveType::MoveTypes::DOWN][FieldType::FieldTypes::ROW] = 0;
	this->_distanceMap[Direction::Directions::WEST][MoveType::MoveTypes::DOWN][FieldType::FieldTypes::COLUMN] = 1;
	this->_distanceMap[Direction::Directions::WEST][MoveType::MoveTypes::DOWN][FieldType::FieldTypes::HEIGHT] = 0;


	//カメラが北を向いている時
	this->_distanceMap[Direction::Directions::NORTH] = std::unordered_map < MoveType::MoveTypes, std::unordered_map< FieldType::FieldTypes, int >>();

	this->_distanceMap[Direction::Directions::NORTH][MoveType::MoveTypes::LEFT][FieldType::FieldTypes::ROW] = 0;
	this->_distanceMap[Direction::Directions::NORTH][MoveType::MoveTypes::LEFT][FieldType::FieldTypes::COLUMN] = -1;
	this->_distanceMap[Direction::Directions::NORTH][MoveType::MoveTypes::LEFT][FieldType::FieldTypes::HEIGHT] = 0;

	this->_distanceMap[Direction::Directions::NORTH][MoveType::MoveTypes::LEFTLOWER][FieldType::FieldTypes::ROW] = 1;
	this->_distanceMap[Direction::Directions::NORTH][MoveType::MoveTypes::LEFTLOWER][FieldType::FieldTypes::COLUMN] = -1;
	this->_distanceMap[Direction::Directions::NORTH][MoveType::MoveTypes::LEFTLOWER][FieldType::FieldTypes::HEIGHT] = 0;

	this->_distanceMap[Direction::Directions::NORTH][MoveType::MoveTypes::LEFTUPPER][FieldType::FieldTypes::ROW] = -1;
	this->_distanceMap[Direction::Directions::NORTH][MoveType::MoveTypes::LEFTUPPER][FieldType::FieldTypes::COLUMN] = -1;
	this->_distanceMap[Direction::Directions::NORTH][MoveType::MoveTypes::LEFTUPPER][FieldType::FieldTypes::HEIGHT] = 0;

	this->_distanceMap[Direction::Directions::NORTH][MoveType::MoveTypes::RIGHTLOWER][FieldType::FieldTypes::ROW] = 1;
	this->_distanceMap[Direction::Directions::NORTH][MoveType::MoveTypes::RIGHTLOWER][FieldType::FieldTypes::COLUMN] = 1;
	this->_distanceMap[Direction::Directions::NORTH][MoveType::MoveTypes::RIGHTLOWER][FieldType::FieldTypes::HEIGHT] = 0;

	this->_distanceMap[Direction::Directions::NORTH][MoveType::MoveTypes::RIGHTUPPER][FieldType::FieldTypes::ROW] = -1;
	this->_distanceMap[Direction::Directions::NORTH][MoveType::MoveTypes::RIGHTUPPER][FieldType::FieldTypes::COLUMN] = 1;
	this->_distanceMap[Direction::Directions::NORTH][MoveType::MoveTypes::RIGHTUPPER][FieldType::FieldTypes::HEIGHT] = 0;

	this->_distanceMap[Direction::Directions::NORTH][MoveType::MoveTypes::RIGHT][FieldType::FieldTypes::ROW] = 0;
	this->_distanceMap[Direction::Directions::NORTH][MoveType::MoveTypes::RIGHT][FieldType::FieldTypes::COLUMN] = 1;
	this->_distanceMap[Direction::Directions::NORTH][MoveType::MoveTypes::RIGHT][FieldType::FieldTypes::HEIGHT] = 0;

	this->_distanceMap[Direction::Directions::NORTH][MoveType::MoveTypes::UP][FieldType::FieldTypes::ROW] = -1;
	this->_distanceMap[Direction::Directions::NORTH][MoveType::MoveTypes::UP][FieldType::FieldTypes::COLUMN] = 0;
	this->_distanceMap[Direction::Directions::NORTH][MoveType::MoveTypes::UP][FieldType::FieldTypes::HEIGHT] = 0;

	this->_distanceMap[Direction::Directions::NORTH][MoveType::MoveTypes::DOWN][FieldType::FieldTypes::ROW] = 1;
	this->_distanceMap[Direction::Directions::NORTH][MoveType::MoveTypes::DOWN][FieldType::FieldTypes::COLUMN] = 0;
	this->_distanceMap[Direction::Directions::NORTH][MoveType::MoveTypes::DOWN][FieldType::FieldTypes::HEIGHT] = 0;


	//カメラが南を向いている時
	this->_distanceMap[Direction::Directions::SOUTH] = std::unordered_map < MoveType::MoveTypes, std::unordered_map< FieldType::FieldTypes, int >>();

	this->_distanceMap[Direction::Directions::SOUTH][MoveType::MoveTypes::LEFT][FieldType::FieldTypes::ROW] = 0;
	this->_distanceMap[Direction::Directions::SOUTH][MoveType::MoveTypes::LEFT][FieldType::FieldTypes::COLUMN] = 1;
	this->_distanceMap[Direction::Directions::SOUTH][MoveType::MoveTypes::LEFT][FieldType::FieldTypes::HEIGHT] = 0;

	this->_distanceMap[Direction::Directions::SOUTH][MoveType::MoveTypes::LEFTLOWER][FieldType::FieldTypes::ROW] = -1;
	this->_distanceMap[Direction::Directions::SOUTH][MoveType::MoveTypes::LEFTLOWER][FieldType::FieldTypes::COLUMN] = 1;
	this->_distanceMap[Direction::Directions::SOUTH][MoveType::MoveTypes::LEFTLOWER][FieldType::FieldTypes::HEIGHT] = 0;

	this->_distanceMap[Direction::Directions::SOUTH][MoveType::MoveTypes::LEFTUPPER][FieldType::FieldTypes::ROW] = 1;
	this->_distanceMap[Direction::Directions::SOUTH][MoveType::MoveTypes::LEFTUPPER][FieldType::FieldTypes::COLUMN] = 1;
	this->_distanceMap[Direction::Directions::SOUTH][MoveType::MoveTypes::LEFTUPPER][FieldType::FieldTypes::HEIGHT] = 0;

	this->_distanceMap[Direction::Directions::SOUTH][MoveType::MoveTypes::RIGHTLOWER][FieldType::FieldTypes::ROW] = -1;
	this->_distanceMap[Direction::Directions::SOUTH][MoveType::MoveTypes::RIGHTLOWER][FieldType::FieldTypes::COLUMN] = -1;
	this->_distanceMap[Direction::Directions::SOUTH][MoveType::MoveTypes::RIGHTLOWER][FieldType::FieldTypes::HEIGHT] = 0;

	this->_distanceMap[Direction::Directions::SOUTH][MoveType::MoveTypes::RIGHTUPPER][FieldType::FieldTypes::ROW] = 1;
	this->_distanceMap[Direction::Directions::SOUTH][MoveType::MoveTypes::RIGHTUPPER][FieldType::FieldTypes::COLUMN] = -1;
	this->_distanceMap[Direction::Directions::SOUTH][MoveType::MoveTypes::RIGHTUPPER][FieldType::FieldTypes::HEIGHT] = 0;

	this->_distanceMap[Direction::Directions::SOUTH][MoveType::MoveTypes::RIGHT][FieldType::FieldTypes::ROW] = 0;
	this->_distanceMap[Direction::Directions::SOUTH][MoveType::MoveTypes::RIGHT][FieldType::FieldTypes::COLUMN] = -1;
	this->_distanceMap[Direction::Directions::SOUTH][MoveType::MoveTypes::RIGHT][FieldType::FieldTypes::HEIGHT] = 0;

	this->_distanceMap[Direction::Directions::SOUTH][MoveType::MoveTypes::UP][FieldType::FieldTypes::ROW] = 1;
	this->_distanceMap[Direction::Directions::SOUTH][MoveType::MoveTypes::UP][FieldType::FieldTypes::COLUMN] = 0;
	this->_distanceMap[Direction::Directions::SOUTH][MoveType::MoveTypes::UP][FieldType::FieldTypes::HEIGHT] = 0;

	this->_distanceMap[Direction::Directions::SOUTH][MoveType::MoveTypes::DOWN][FieldType::FieldTypes::ROW] = -1;
	this->_distanceMap[Direction::Directions::SOUTH][MoveType::MoveTypes::DOWN][FieldType::FieldTypes::COLUMN] = 0;
	this->_distanceMap[Direction::Directions::SOUTH][MoveType::MoveTypes::DOWN][FieldType::FieldTypes::HEIGHT] = 0;
}


CharacterMoveDistance::~CharacterMoveDistance()
{
}

int CharacterMoveDistance::getRowDistance(Direction::Directions CAMERADIRECTION, MoveType::MoveTypes CHARACTERMOVETYPE)
{
	return this->_distanceMap[CAMERADIRECTION][CHARACTERMOVETYPE][FieldType::FieldTypes::ROW];
}

int CharacterMoveDistance::getColumnDistance(Direction::Directions CAMERADIRECTION, MoveType::MoveTypes CHARACTERMOVETYPE)
{
	return this->_distanceMap[CAMERADIRECTION][CHARACTERMOVETYPE][FieldType::FieldTypes::COLUMN];
}

int CharacterMoveDistance::getHeightDistance(Direction::Directions CAMERADIRECTION, MoveType::MoveTypes CHARACTERMOVETYPE)
{
	return this->_distanceMap[CAMERADIRECTION][CHARACTERMOVETYPE][FieldType::FieldTypes::HEIGHT];
}
