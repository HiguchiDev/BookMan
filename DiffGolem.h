#pragma once
#include "Enemy.h"
class DiffGolem :
	public Enemy
{
public:
	DiffGolem(std::string fileName, std::shared_ptr<Position> position, std::shared_ptr<TurnController> turnController);
	~DiffGolem();
};

