#pragma once
#include "Enemy.h"
class Ice :
	public Enemy
{
public:
	Ice(std::string fileName, std::shared_ptr<Position> position, std::shared_ptr<TurnController> turnController);
	~Ice();
};

