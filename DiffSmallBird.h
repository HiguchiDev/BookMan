#pragma once
#include "Enemy.h"
class DiffSmallBird :
	public Enemy
{
public:
	DiffSmallBird(std::string fileName, std::shared_ptr<Position> position, std::shared_ptr<TurnController> turnController);
	~DiffSmallBird();
};

