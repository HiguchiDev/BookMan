#pragma once
#include "Enemy.h"
class Hana :
	public Enemy
{
public:
	Hana(std::string fileName, std::shared_ptr<Position> position, std::shared_ptr<TurnController> turnController);
	~Hana();
};

