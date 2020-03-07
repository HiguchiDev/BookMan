#pragma once
#include "Enemy.h"
class Kasya :
	public Enemy
{
public:
	Kasya(std::string fileName, std::shared_ptr<Position> position, std::shared_ptr<TurnController> turnController);
	~Kasya();
};

