#pragma once
#include "Enemy.h"
class DiffEgg :
	public Enemy
{
public:
	DiffEgg(std::string fileName, std::shared_ptr<Position> position, std::shared_ptr<TurnController> turnController);
	~DiffEgg();
};

