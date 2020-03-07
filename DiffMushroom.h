#pragma once
#include "Enemy.h"
class DiffMushroom :
	public Enemy
{
public:
	DiffMushroom(std::string fileName, std::shared_ptr<Position> position, std::shared_ptr<TurnController> turnController);
	~DiffMushroom();
};

