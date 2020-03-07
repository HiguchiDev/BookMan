#pragma once
#include "Enemy.h"
class HanaAsyu :
	public Enemy
{
public:
	HanaAsyu(std::string fileName, std::shared_ptr<Position> position, std::shared_ptr<TurnController> turnController);
	~HanaAsyu();
};

