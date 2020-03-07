#pragma once
#include "Enemy.h"
class TutorialEnemy :
	public Enemy
{
public:

	TutorialEnemy(std::string fileName, std::shared_ptr<Position> position, std::shared_ptr<TurnController> turnController);
	~TutorialEnemy();
};

