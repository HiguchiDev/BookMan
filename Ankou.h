#pragma once
#include "Enemy.h"
class Ankou :
	public Enemy
{
public:
	Ankou(std::string fileName, std::shared_ptr<Position> position, std::shared_ptr<TurnController> turnController);
	~Ankou();
};

