#pragma once
#include "Enemy.h"
class Golem :
	public Enemy
{
public:
	Golem(std::string fileName, std::shared_ptr<Position> position, std::shared_ptr<TurnController> turnController);
	~Golem();
};

