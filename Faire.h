#pragma once
#include "Enemy.h"
class Faire :
	public Enemy
{
public:
	Faire(std::string fileName, std::shared_ptr<Position> position, std::shared_ptr<TurnController> turnController);
	~Faire();
};

