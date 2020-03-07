#pragma once
#include "Enemy.h"
class Suisya :
	public Enemy
{
public:
	Suisya(std::string fileName, std::shared_ptr<Position> position, std::shared_ptr<TurnController> turnController);
	~Suisya();
};

