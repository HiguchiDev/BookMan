#pragma once
#include "Enemy.h"
class KingsuraimuRed :
	public Enemy
{
public:
	KingsuraimuRed(std::string fileName, std::shared_ptr<Position> position, std::shared_ptr<TurnController> turnController);
	~KingsuraimuRed();
};

