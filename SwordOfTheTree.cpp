#include "SwordOfTheTree.h"
#include <memory>
#include "HitBox.h"
#include "Position.h"
#include "Collision.h"
#include "Character.h"
#include "WeaponType.h"
#include "StatesPoint.h"

SwordOfTheTree::SwordOfTheTree(std::string name, WeaponType::Type TYPE)
{
	this->_TYPE = TYPE;

	this->_name = name;
	this->_statesPoint = std::make_shared<StatesPoint>();
	this->_statesPoint->load(this->_name);

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
	


	this->_durability = 40;
	this->_damege = this->_statesPoint->getStatesPoint(State::ATTACK);
}

SwordOfTheTree::~SwordOfTheTree()
{
}

std::string SwordOfTheTree::toString()
{
	return this->_name;
}

//std::vector< std::shared_ptr<HitBox>> Collision::_hitBoxs;

void SwordOfTheTree::attack(std::shared_ptr<Character> character, Direction::Directions DIRECTION)
{
	int hitBoxRow = character->getPos()->getRow() + this->_distanceOfRow[DIRECTION];
	int hitBoxColumn = character->getPos()->getColumn() + this->_distanceOfColumn[DIRECTION];
	int hitBoxHeight = character->getPos()->getHeight();

	std::shared_ptr<HitBox> hitBox = std::make_shared<HitBox>(std::make_shared<Position>(hitBoxRow, hitBoxColumn, hitBoxHeight), character->getType(), this->_damege);

	hitBox->initialize();
}