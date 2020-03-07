#pragma once
#include "Trap.h"
#include <memory>
#include <string>

class Position;
class Character;

class Needle
	: public Trap
{
public:
	void according(std::shared_ptr<CharacterData> characterData, std::shared_ptr<Character> character);
	Needle(std::string fileName, std::shared_ptr<Position> position);
	~Needle();
};