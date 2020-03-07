#include "MoveType_RotateConverter.h"
#include "MoveType.h"

MoveType_RotateConverter::MoveType_RotateConverter()
{
	//ƒJƒƒ‰‚ª“Œ‚ðŒü‚¢‚Ä‚¢‚éŽž
	this->_rotateMap[Direction::Directions::EAST][MoveType::MoveTypes::LEFT] = 90;
	this->_rotateMap[Direction::Directions::EAST][MoveType::MoveTypes::LEFTLOWER] = 45;
	this->_rotateMap[Direction::Directions::EAST][MoveType::MoveTypes::LEFTUPPER] = 135;

	this->_rotateMap[Direction::Directions::EAST][MoveType::MoveTypes::RIGHT] = -90;
	this->_rotateMap[Direction::Directions::EAST][MoveType::RIGHTLOWER] = -45;
	this->_rotateMap[Direction::Directions::EAST][MoveType::MoveTypes::RIGHTUPPER] = -135;

	this->_rotateMap[Direction::Directions::EAST][MoveType::MoveTypes::UP] = 180;
	this->_rotateMap[Direction::Directions::EAST][MoveType::MoveTypes::DOWN] = 0;

	//ƒJƒƒ‰‚ª¼‚ðŒü‚¢‚Ä‚¢‚éŽž
	this->_rotateMap[Direction::Directions::WEST][MoveType::MoveTypes::LEFT] = -90;
	this->_rotateMap[Direction::Directions::WEST][MoveType::MoveTypes::LEFTLOWER] = -135;
	this->_rotateMap[Direction::Directions::WEST][MoveType::MoveTypes::LEFTUPPER] = -45;

	this->_rotateMap[Direction::Directions::WEST][MoveType::MoveTypes::RIGHT] = 90;
	this->_rotateMap[Direction::Directions::WEST][MoveType::RIGHTLOWER] = 135;
	this->_rotateMap[Direction::Directions::WEST][MoveType::MoveTypes::RIGHTUPPER] = 45;

	this->_rotateMap[Direction::Directions::WEST][MoveType::MoveTypes::UP] = 0;
	this->_rotateMap[Direction::Directions::WEST][MoveType::MoveTypes::DOWN] = 180;


	//ƒJƒƒ‰‚ª–k‚ðŒü‚¢‚Ä‚¢‚éŽž
	this->_rotateMap[Direction::Directions::NORTH][MoveType::MoveTypes::LEFT] = 0;
	this->_rotateMap[Direction::Directions::NORTH][MoveType::MoveTypes::LEFTLOWER] = -45;
	this->_rotateMap[Direction::Directions::NORTH][MoveType::MoveTypes::LEFTUPPER] = 45;

	this->_rotateMap[Direction::Directions::NORTH][MoveType::MoveTypes::RIGHT] = 180;
	this->_rotateMap[Direction::Directions::NORTH][MoveType::RIGHTLOWER] = -135;
	this->_rotateMap[Direction::Directions::NORTH][MoveType::MoveTypes::RIGHTUPPER] = 135;

	this->_rotateMap[Direction::Directions::NORTH][MoveType::MoveTypes::UP] = 90;
	this->_rotateMap[Direction::Directions::NORTH][MoveType::MoveTypes::DOWN] = -90;


	this->_rotateMap[Direction::Directions::SOUTH][MoveType::MoveTypes::LEFT] = 180;

	this->_rotateMap[Direction::Directions::SOUTH][MoveType::LEFTLOWER] = 135;
	this->_rotateMap[Direction::Directions::SOUTH][MoveType::MoveTypes::LEFTUPPER] = -135;

	this->_rotateMap[Direction::Directions::SOUTH][MoveType::MoveTypes::RIGHT] = 0;
	this->_rotateMap[Direction::Directions::SOUTH][MoveType::RIGHTLOWER] = 45;
	this->_rotateMap[Direction::Directions::SOUTH][MoveType::MoveTypes::RIGHTUPPER] = -45;

	this->_rotateMap[Direction::Directions::SOUTH][MoveType::MoveTypes::UP] = -90;
	this->_rotateMap[Direction::Directions::SOUTH][MoveType::MoveTypes::DOWN] = 90;
}


MoveType_RotateConverter::~MoveType_RotateConverter()
{
}

float MoveType_RotateConverter::getRotate(Direction::Directions CAMERADIRECTION, MoveType::MoveTypes CHARACTERMOVETYPE)
{
	return this->_rotateMap[CAMERADIRECTION][CHARACTERMOVETYPE];
}