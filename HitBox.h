#pragma once
#include "FieldMaterial.h"
#include "CharacterType.h"
#include <memory>
#include "CharacterData.h"

class StatesPoint;
class Position;
class Character;

class HitBox
	: public FieldMaterial, public std::enable_shared_from_this<HitBox>
{
private:
	virtual void initializePosition();
	std::shared_ptr<StatesPoint> _statesDamegePoint;
	CharacterType::CharacterTypes _CHARACTERTYPE;
	int _damage;
public:
	void action();
	void causeDamageToCharacter(std::shared_ptr<CharacterData> characterData, std::shared_ptr<Character> character);
	virtual void updateCollisionInformation(std::shared_ptr<Position> position);
	CharacterType::CharacterTypes getCharacterType();
	int getDamege(){ return this->_damage; };

	HitBox(std::shared_ptr<Position> position, CharacterType::CharacterTypes CHARACTERTYPE, int amage);
	~HitBox();
};

