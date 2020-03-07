#pragma once
#include "Enemy.h"
class SmallBird :
	public Enemy
{
public:
	SmallBird(std::string fileName, std::shared_ptr<Position> position, std::shared_ptr<TurnController> turnController);
	~SmallBird();
};

