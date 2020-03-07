#pragma once
#include "Enemy.h"
class Water :
	public Enemy
{
public:
	Water(std::string fileName, std::shared_ptr<Position> position, std::shared_ptr<TurnController> turnController);
	~Water();
};

