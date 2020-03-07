#pragma once
#include "FieldMaterial.h"
#include "Action.h"
#include "Position.h"
#include "Direction.h"
#include "CharacterType.h"
#include "PositionConverter.h"
#include "Direction_AngleConverter.h"

class Motion;
class StatesPoint;
class HitBox;
class TurnController;
class Item;
class CharacterData;
class PlayerDatas;
class Weapon;
class Trap;

class Character
	: public FieldMaterial, public std::enable_shared_from_this<Character>
{
protected:
	std::shared_ptr<CharacterData> _characterDatas;
	float _animationSpeed;
	bool _turnFinish;
	Action::Actions _ACTION;
	Direction::Directions _DIRECTION;
	void initializePosition();
	std::shared_ptr<TurnController> _turnController;
	std::shared_ptr<Motion> _motion;
	PositionConverter _positionConverter;
	CharacterType::CharacterTypes _TYPE;
	Direction_AngleConverter _angleConverter;
	std::shared_ptr<Weapon> _weapon;
	bool _boss = false;
	std::string _characterName;

public:
	virtual void throwTrap(std::shared_ptr<Trap> trap){};
	bool isBoss(){ return this->_boss; };
	virtual std::string getName(){ return _characterName; };
	virtual bool beExamined(){ return false; };
	virtual void actionOfCollision(std::shared_ptr<Character> character);
	virtual void actionOfCollision(std::shared_ptr<HitBox> hitBox);
	virtual void actionOfCollision(std::shared_ptr<Trap> trap);
	CharacterType::CharacterTypes getType();
	virtual void initialize();
	virtual std::shared_ptr<CharacterData> getCharacterData();
	void draw();
	virtual bool isFree(){ return true; };
	virtual bool isFinish();
	void turnReset();
	Direction::Directions getDirection();
	virtual void update();
	virtual void action() = 0;
	virtual void action(int key){ this->action(); };
	static std::shared_ptr<Character> createCharacter(std::string fileName, std::shared_ptr<Position> position, std::shared_ptr<TurnController> turnController, std::shared_ptr<PlayerDatas> playerDate);
	static std::shared_ptr<Character> createCharacter(std::string fileName, std::shared_ptr<Position> position, std::shared_ptr<TurnController> turnController);
	void updateCollisionInformation(std::shared_ptr<Position> newPosition);
	Character(std::string fileName, std::shared_ptr<Position> position, std::shared_ptr<TurnController> turnController);
	~Character();
};

