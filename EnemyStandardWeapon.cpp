#include "EnemyStandardWeapon.h"
#include <memory>
#include "HitBox.h"
#include "Position.h"
#include "Collision.h"
#include "Character.h"
#include "WeaponType.h"

EnemyStandardWeapon::EnemyStandardWeapon(int damage)
{
	this->_TYPE = WeaponType::SWORD;

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

	this->_damege = damage;
}


EnemyStandardWeapon::~EnemyStandardWeapon()
{
}

std::string EnemyStandardWeapon::toString()
{
	return "EnemyStandardWeapon";
}

void EnemyStandardWeapon::attack(std::shared_ptr<Character> character, Direction::Directions DIRECTION)
{
	int hitBoxRow = character->getPos()->getRow() + this->_distanceOfRow[DIRECTION];
	int hitBoxColumn = character->getPos()->getColumn() + this->_distanceOfColumn[DIRECTION];
	int hitBoxHeight = character->getPos()->getHeight();

	std::shared_ptr<HitBox> hitBox = std::make_shared<HitBox>(std::make_shared<Position>(hitBoxRow, hitBoxColumn, hitBoxHeight), character->getType(), this->_damege);

	hitBox->initialize();
}