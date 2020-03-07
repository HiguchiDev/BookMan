#pragma once
#include "Enemy.h"
class Kingsuraimu :
	public Enemy
{
public:
	Kingsuraimu(std::string fileName, std::shared_ptr<Position> position, std::shared_ptr<TurnController> turnController);
	~Kingsuraimu();
};

