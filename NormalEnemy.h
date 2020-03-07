#pragma once
#include "Enemy.h"

class NormalEnemy :
	public Enemy
{
private:
	std::string _characterName2;
public:
	std::string getName(){ return _characterName2; };
	NormalEnemy(std::string characterName, std::string characterFileName, std::shared_ptr<Position> position, std::shared_ptr<TurnController> turnController);
	~NormalEnemy();
};

