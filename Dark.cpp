#include "Dark.h"
#include "Character.h"
#include "HitBox.h"
#include "PlayerDirectionGetter.h"
#include "MessgeBox.h"
#include "EffectUpdater.h"
#include "Effect.h"

Dark::Dark(std::string name)
{
	this->_effect = std::make_shared<Effect>("Dark.efk");

	this->_TYPE = WeaponType::CANE;

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

	this->_damege = this->_statesPoint->getStatesPoint(State::ATTACK);
}


Dark::~Dark()
{
}

std::string Dark::toString()
{
	return this->_name;
}

void Dark::attack(std::shared_ptr<Character> character, Direction::Directions DIRECTION)
{
	//if (character->getCharacterData()->getStatesPoint()->getStatesPoint(State::MAGICPOINT) >= 9){
	PositionConverter pc;


	std::shared_ptr<HitBox> hitBox;

	int startRow = character->getPos()->getRow() - 1;
	int startColumn = character->getPos()->getColumn() - 1;

	for (int i = 0; i < 3; i++){
		for (int j = 0; j < 3; j++){
			int hitBoxRow = startRow + i;
			int hitBoxColumn = startColumn + j;
			int hitBoxHeight = character->getPos()->getHeight();

			hitBox = std::make_shared<HitBox>(std::make_shared<Position>(hitBoxRow, hitBoxColumn, hitBoxHeight), character->getType(), this->_damege);

			hitBox->initialize();
		}

	}

	VECTOR pos = pc.get3DPosition(std::make_shared<Position>(character->getPos()->getRow(), character->getPos()->getColumn(), 1));

	pos.y -= 20;
	//this->_effect = std::make_shared<Effect>("Dark.efk");
	this->_effect->setPos(pos);
	this->_effect->start(character->getDirection());
	EffectUpdater::getInstance()->add(this->_effect);

	//	character->getCharacterData()->getStatesPoint()->upDateStatesPoint(State::MAGICPOINT, character->getCharacterData()->getStatesPoint()->getStatesPoint(State::MAGICPOINT) - 9);
	//}
}