#pragma once
#include "FieldMaterial.h"
#include "PositionConverter.h"
#include <unordered_map>

class CharacterData;
class Position;
class Character;

class Trap : public FieldMaterial, public std::enable_shared_from_this<Trap>
{
private:
	PositionConverter _positionConverter;
	std::unordered_map<Direction::Directions, int> _distanceOfRow;
	std::unordered_map<Direction::Directions, int> _distanceOfColumn;
	bool _stop = false;
	Direction::Directions _DIRECTION_THROW = Direction::COUNT;
	bool _lodge = false;

public:
	void setLodge(bool lodge){ this->_lodge = lodge; };
	bool isLodge(){ return this->_lodge; };
	void throwTrap(Direction::Directions DIRECTION);
	bool isThrowStop();
	//virtual void action();
	void draw();
	static std::shared_ptr<Trap> createInstance(std::string trapName, std::shared_ptr<Position> position);
	void initializePosition();
	virtual void according(std::shared_ptr<CharacterData> characterData, std::shared_ptr<Character> character) = 0;
	void updateCollisionInformation(std::shared_ptr<Position> newPosition);
	Trap(std::string fileName, std::shared_ptr<Position> position);
	~Trap();
};

