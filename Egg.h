#pragma once
#include "Enemy.h"
class Egg :
	public Enemy
{
public:
	Egg(std::string fileName, std::shared_ptr<Position> position, std::shared_ptr<TurnController> turnController);
	~Egg();
};

