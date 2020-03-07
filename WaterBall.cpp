#include "WaterBall.h"

#include "Effect.h"
#include "EffectUpdater.h"
#include "Character.h"
#include "HitBox.h"

WaterBall::WaterBall(std::string name)
{
	this->_effect = std::make_shared<Effect>("WaterBall.efk");
	EffectUpdater::getInstance()->add(this->_effect);

	this->_TYPE = WeaponType::CANE;

	this->_name = name;
	this->_statesPoint = std::make_shared<StatesPoint>();
	this->_statesPoint->load(this->_name);

	this->_distanceOfRow[Direction::Directions::EAST] = 0;
	this->_distanceOfColumn[Direction::Directions::EAST] = 2;

	this->_distanceOfRow[Direction::Directions::WEST] = 0;
	this->_distanceOfColumn[Direction::Directions::WEST] = -2;

	this->_distanceOfRow[Direction::Directions::NORTH] = -2;
	this->_distanceOfColumn[Direction::Directions::NORTH] = 0;

	this->_distanceOfRow[Direction::Directions::SOUTH] = 2;
	this->_distanceOfColumn[Direction::Directions::SOUTH] = 0;

	this->_distanceOfRow[Direction::Directions::EASTNORTH] = -2;
	this->_distanceOfColumn[Direction::Directions::EASTNORTH] = 2;

	this->_distanceOfRow[Direction::Directions::WESTNORTH] = -2;
	this->_distanceOfColumn[Direction::Directions::WESTNORTH] = -2;

	this->_distanceOfRow[Direction::Directions::EASTSOUTH] = 2;
	this->_distanceOfColumn[Direction::Directions::EASTSOUTH] = 2;

	this->_distanceOfRow[Direction::Directions::WESTSOUTH] = 2;
	this->_distanceOfColumn[Direction::Directions::WESTSOUTH] = -2;

	this->_damege = this->_statesPoint->getStatesPoint(State::ATTACK);
}


WaterBall::~WaterBall()
{
}

std::string WaterBall::toString()
{
	return this->_name;
}

void WaterBall::attack(std::shared_ptr<Character> character, Direction::Directions DIRECTION)
{
	PositionConverter pc;

	std::shared_ptr<HitBox> hitBox;

	for (int i = 0; i < 3; i++){
		for (int j = 0; j < 3; j++){
			int hitBoxRow = (character->getPos()->getRow() + this->_distanceOfRow[DIRECTION]) - (i - 1);
			int hitBoxColumn = (character->getPos()->getColumn() + this->_distanceOfColumn[DIRECTION]) - (j - 1);
			int hitBoxHeight = character->getPos()->getHeight();

			hitBox = std::make_shared<HitBox>(std::make_shared<Position>(hitBoxRow, hitBoxColumn, hitBoxHeight), character->getType(), this->_damege);

			hitBox->initialize();

			if (i == 1 && j == 1){
				VECTOR pos = pc.get3DPosition(std::make_shared<Position>(character->getPos()->getRow() + this->_distanceOfRow[DIRECTION], character->getPos()->getColumn() + this->_distanceOfColumn[DIRECTION], 1));

				pos.y -= 20;
				this->_effect->setPos(pos);
				this->_effect->start(character->getDirection());
				EffectUpdater::getInstance()->add(this->_effect);
			}
		}
	}
}