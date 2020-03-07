#include "Direction_AngleConverter.h"


Direction_AngleConverter::Direction_AngleConverter()
{
	this->_map[Direction::Directions::EAST] = 90.0f;
	this->_map[Direction::Directions::WEST] = 270.0f;
	this->_map[Direction::Directions::NORTH] = 0;
	this->_map[Direction::Directions::SOUTH] = 180.0f;
	this->_map[Direction::Directions::EASTNORTH] = 45.0f;
	this->_map[Direction::Directions::EASTSOUTH] = 135.0f;
	this->_map[Direction::Directions::WESTNORTH] = 315.0f;
	this->_map[Direction::Directions::WESTSOUTH] = 225.0f;
}


Direction_AngleConverter::~Direction_AngleConverter()
{
}

float Direction_AngleConverter::getAngle(Direction::Directions DIRECTION)
{
	return this->_map[DIRECTION];
}