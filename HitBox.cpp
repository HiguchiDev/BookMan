#include "HitBox.h"
#include "StatesPoint.h"
#include "Collision.h"
#include "Position.h"
#include "ScreenMaterial.h"
#include "PositionConverter.h"
#include "DamageDisplay.h"
#include "Character.h"
#include "HitBoxUpdater.h"

HitBox::HitBox(std::shared_ptr<Position> position, CharacterType::CharacterTypes CHARACTERTYPE, int damage) : FieldMaterial("hitBox.mqo", position)
{
	this->_CHARACTERTYPE = CHARACTERTYPE;

	this->_statesDamegePoint = std::make_shared<StatesPoint>();
	this->_statesDamegePoint->upDateStatesPoint(State::HITPOINT, 30);
	this->_position = position;

	this->_damage = damage;
}


HitBox::~HitBox()
{
}

CharacterType::CharacterTypes HitBox::getCharacterType()
{
	return this->_CHARACTERTYPE;
}

void HitBox::initializePosition()
{
	Collision::getInstance()->add(shared_from_this(), this->_position);
	HitBoxUpdater::getInstance()->add(shared_from_this());
	this->_position->updateHeight(1, shared_from_this());

}

void HitBox::action()
{
	PositionConverter converter;

	this->_screenMaterial->setPosition(converter.get3DPosition(this->_position));

	this->_screenMaterial->draw();
	
}

void HitBox::causeDamageToCharacter(std::shared_ptr<CharacterData> characterData, std::shared_ptr<Character> character)
{
	int damage = this->_damage - characterData->getStatesPoint()->getStatesPoint(State::DEFENSE);

	
	if (damage <= 0){
		damage = 1;
	}

	characterData->getStatesPoint()->upDateStatesPoint(State::States::HITPOINT, characterData->getStatesPoint()->getStatesPoint(State::States::HITPOINT) - damage);
	

	DamageDisplay::getInstance()->add(character->getPos(), damage);
}

void HitBox::updateCollisionInformation(std::shared_ptr<Position> position){
//	Collision::update(shared_from_this(), this->_position);
}

