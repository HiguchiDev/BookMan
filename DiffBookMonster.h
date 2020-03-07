#pragma once
#include "Enemy.h"
class DiffBookMonster :
	public Enemy
{
public:
	DiffBookMonster(std::string fileName, std::shared_ptr<Position> position, std::shared_ptr<TurnController> turnController);
	~DiffBookMonster();
};

