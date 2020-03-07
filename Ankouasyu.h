#pragma once
#include "Enemy.h"
class Ankouasyu :
	public Enemy
{
public:
	Ankouasyu(std::string fileName, std::shared_ptr<Position> position, std::shared_ptr<TurnController> turnController);
	~Ankouasyu();
};

