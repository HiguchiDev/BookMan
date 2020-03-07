#pragma once
#include "FloorOfTheDungeon.h"

class Trap;

class BossFloorOfTheDungeon :
	public FloorOfTheDungeon
{
private:
	std::shared_ptr<Character> _bossCharacter;
public:
	bool isFinish();
	void start();
	BossFloorOfTheDungeon(std::string floorFileName, std::shared_ptr<Stairs> stairs, std::vector< std::shared_ptr<Character> > enemys, std::shared_ptr< Character > player, std::vector< std::shared_ptr<Obstacle> > obstacles, std::vector< std::shared_ptr<Floor>> floors, std::vector<std::shared_ptr<Item>> items, std::vector<std::shared_ptr<Trap>> traps, std::shared_ptr<TurnController> turnController, std::shared_ptr<Character> bossCharacter);
	~BossFloorOfTheDungeon();
};

