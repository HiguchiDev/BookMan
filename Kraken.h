#pragma once
#include "Enemy.h"
class Kraken :
	public Enemy
{
public:
	Kraken(std::string fileName, std::shared_ptr<Position> position, std::shared_ptr<TurnController> turnController);
	~Kraken();
};

