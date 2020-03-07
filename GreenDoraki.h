#pragma once
#include "Enemy.h"
class GreenDoraki :
	public Enemy
{
public:
	GreenDoraki(std::string fileName, std::shared_ptr<Position> position, std::shared_ptr<TurnController> turnController);
	~GreenDoraki();
};

