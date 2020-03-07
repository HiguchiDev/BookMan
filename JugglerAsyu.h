#pragma once
#include "Enemy.h"
class JugglerAsyu :
	public Enemy
{
public:
	JugglerAsyu(std::string fileName, std::shared_ptr<Position> position, std::shared_ptr<TurnController> turnController);
	~JugglerAsyu();
};

