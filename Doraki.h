#pragma once
#include "Enemy.h"
class Doraki :
	public Enemy
{
public:
	Doraki(std::string fileName, std::shared_ptr<Position> position, std::shared_ptr<TurnController> turnController);
	~Doraki();
};

