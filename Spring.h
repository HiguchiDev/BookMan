#pragma once
#include "Trap.h"
#include <memory>
#include <string>

class Position;
class Character;

class Spring
	: public Trap
{
public:
	void according(std::shared_ptr<CharacterData> characterData, std::shared_ptr<Character> character);
	Spring(std::string fileName, std::shared_ptr<Position> position);
	~Spring();
};

