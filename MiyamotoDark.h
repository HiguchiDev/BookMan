#pragma once
#include "Enemy.h"
class MiyamotoDark :
	public Enemy
{
public:
	MiyamotoDark(std::string fileName, std::shared_ptr<Position> position, std::shared_ptr<TurnController> turnController);
	~MiyamotoDark();
};

