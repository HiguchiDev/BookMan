#pragma once
#include "Enemy.h"

class Juggler :
	public Enemy
{

public:

	Juggler(std::string fileName, std::shared_ptr<Position> position, std::shared_ptr<TurnController> turnController);
	~Juggler();
};

