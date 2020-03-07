#include "Thunder.h"
#include "Character.h"
#include "HitBox.h"
#include "PlayerDirectionGetter.h"
#include "MessgeBox.h"
#include "Effect.h"
#include "EffectUpdater.h"

Thunder::Thunder(std::string name)
{
	for (int i = 0; i < 3; i++){
		this->_effects.push_back(std::make_shared<Effect>("Thunder.efk"));
	}

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


Thunder::~Thunder()
{
}

std::string Thunder::toString()
{
	return this->_name;
}

void Thunder::attack(std::shared_ptr<Character> character, Direction::Directions DIRECTION)
{
	PositionConverter pc;

	std::shared_ptr<HitBox> hitBox;


	int i, j;
	int thuderNum = 0;

	for (int k = 0; k < 3; k++){
		i = GetRand(2);
		j = GetRand(2);
		int hitBoxRow = (character->getPos()->getRow() + this->_distanceOfRow[DIRECTION]) - (i - 1);
		int hitBoxColumn = (character->getPos()->getColumn() + this->_distanceOfColumn[DIRECTION]) - (j - 1);
		int hitBoxHeight = character->getPos()->getHeight();
		hitBox = std::make_shared<HitBox>(std::make_shared<Position>(hitBoxRow, hitBoxColumn, hitBoxHeight), character->getType(), this->_damege);

		hitBox->initialize();

		VECTOR pos = pc.get3DPosition(std::make_shared<Position>((character->getPos()->getRow() + this->_distanceOfRow[DIRECTION]) - (i - 1), (character->getPos()->getColumn() + this->_distanceOfColumn[DIRECTION]) - (j - 1), 1));

		pos.y -= 20;
		this->_effects[k]->setPos(pos);
		this->_effects[k]->start(character->getDirection());
		EffectUpdater::getInstance()->add(this->_effects[k]);
	}
}


//	character->getCharacterData()->getStatesPoint()->upDateStatesPoint(State::MAGICPOINT, character->getCharacterData()->getStatesPoint()->getStatesPoint(State::MAGICPOINT) - 9);
//}}