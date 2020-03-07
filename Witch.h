#pragma once
#include "Enemy.h"
class Witch :
	public Enemy
{

public:
	Witch(std::string fileName, std::shared_ptr<Position> position, std::shared_ptr<TurnController> turnController);
	~Witch();
};

