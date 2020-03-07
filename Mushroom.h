#pragma once
#include "Enemy.h"
class Mushroom :
	public Enemy
{
public:
	Mushroom(std::string fileName, std::shared_ptr<Position> position, std::shared_ptr<TurnController> turnController);
	~Mushroom();
};

