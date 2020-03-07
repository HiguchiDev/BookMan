#pragma once
#include "Enemy.h"
class DiffSmallAnimal :
	public Enemy
{
public:
	DiffSmallAnimal(std::string fileName, std::shared_ptr<Position> position, std::shared_ptr<TurnController> turnController);
	~DiffSmallAnimal();
};

