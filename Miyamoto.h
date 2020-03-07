#pragma once
#include "Enemy.h"
class Miyamoto :
	public Enemy
{
public:
	Miyamoto(std::string fileName, std::shared_ptr<Position> position, std::shared_ptr<TurnController> turnController);;
	~Miyamoto();
};

