#include "Trap.h"
#include "CharacterData.h"
#include "Spring.h"
#include "Collision.h"
#include "Needle.h"
#include "ScreenMaterial.h"
#include "PositionConverter.h"
#include "Position.h"

Trap::Trap(std::string fileName, std::shared_ptr<Position> position) : FieldMaterial(fileName, position)
{
	this->_visible = false;
	this->_distanceOfRow[Direction::Directions::EAST] = 0;
	this->_distanceOfColumn[Direction::Directions::EAST] = 1;

	this->_distanceOfRow[Direction::Directions::WEST] = 0;
	this->_distanceOfColumn[Direction::Directions::WEST] = -1;

	this->_distanceOfRow[Direction::Directions::NORTH] = -1;
	this->_distanceOfColumn[Direction::Directions::NORTH] = 0;

	this->_distanceOfRow[Direction::Directions::SOUTH] = 1;
	this->_distanceOfColumn[Direction::Directions::SOUTH] = 0;

	this->_distanceOfRow[Direction::Directions::EASTNORTH] = -1;
	this->_distanceOfColumn[Direction::Directions::EASTNORTH] = 1;

	this->_distanceOfRow[Direction::Directions::WESTNORTH] = -1;
	this->_distanceOfColumn[Direction::Directions::WESTNORTH] = -1;

	this->_distanceOfRow[Direction::Directions::EASTSOUTH] = 1;
	this->_distanceOfColumn[Direction::Directions::EASTSOUTH] = 1;

	this->_distanceOfRow[Direction::Directions::WESTSOUTH] = 1;
	this->_distanceOfColumn[Direction::Directions::WESTSOUTH] = -1;
}


Trap::~Trap()
{
}

void Trap::initializePosition()
{
	Collision::getInstance()->add(shared_from_this(), this->_position);
}

void Trap::draw()
{
	this->_screenMaterial->animation(this->_positionConverter.get3DPosition(this->_position), 15.0f);

	if (this->_visible){
		this->_screenMaterial->draw();
	}
}

void Trap::throwTrap(Direction::Directions DIRECTION)
{
	//std::shared_ptr<Position> newPos;
	if (this->_DIRECTION_THROW == Direction::COUNT){
		this->_DIRECTION_THROW = DIRECTION;
	}
	
	if (!this->_stop){
		if (this->_screenMaterial->isAnimationFinish()){

			this->_position->update(this->_position->getRow() + this->_distanceOfRow[this->_DIRECTION_THROW], this->_position->getColumn() + this->_distanceOfColumn[this->_DIRECTION_THROW], 1, shared_from_this());


		}

		if (!Collision::getInstance()->isMovable(shared_from_this(), std::make_shared<Position>(this->_position->getRow(), this->_position->getColumn(), 1))){
			this->_stop = true;
			this->initialize();
		}
		else if (!Collision::getInstance()->isMovable(shared_from_this(), std::make_shared<Position>(this->_position->getRow() + this->_distanceOfRow[this->_DIRECTION_THROW], this->_position->getColumn() + this->_distanceOfColumn[this->_DIRECTION_THROW], 1))){
			this->_stop = true;
			this->initialize();
			this->_position->update(this->_position->getRow() + this->_distanceOfRow[this->_DIRECTION_THROW], this->_position->getColumn() + this->_distanceOfColumn[this->_DIRECTION_THROW], 1, shared_from_this());
		}
	}

	this->_visible = true;
}

bool Trap::isThrowStop()
{
	return this->_stop;
}

std::shared_ptr<Trap> Trap::createInstance(std::string trapName, std::shared_ptr<Position> position)
{
	if (trapName == "Spring"){
		return std::make_shared<Spring>("Spring.pmd", position);
	}
	else if (trapName == "Needle"){
		return std::make_shared<Needle>("Needle.pmd", position);
	}
	else{
		return nullptr;
	}
}

void Trap::updateCollisionInformation(std::shared_ptr<Position> newPosition)
{
}
/*
void Trap::according(std::shared_ptr<CharacterData> character)
{

}
*/