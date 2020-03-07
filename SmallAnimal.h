#pragma once
#include "Enemy.h"
class SmallAnimal :
	public Enemy
{
public:
	SmallAnimal(std::string fileName, std::shared_ptr<Position> position, std::shared_ptr<TurnController> turnController);
	~SmallAnimal();
};

