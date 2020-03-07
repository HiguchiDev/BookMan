#pragma once
#include <string>
#include <list>
#include <vector>
#include "Obstacle.h"
#include "Character.h"
#include "Item.h"
#include <memory>
#include "Trap.h"

class SaveBook;
class Player;

class StageDataLoader
{
private:
	std::string _stageDataName; 
public:
	bool loadData(int floorIndex, std::shared_ptr<SaveBook> &saveBook, std::vector<std::shared_ptr<Obstacle> >& obstacles, std::vector<std::shared_ptr<Item> >& items, std::vector<std::shared_ptr<Trap> >& traps, std::vector<std::shared_ptr<Character> >& characters, std::shared_ptr<Character> &player, std::shared_ptr<Stairs> &stairs, std::shared_ptr<TurnController> turnController, std::shared_ptr<PlayerDatas> playerDatas);

	StageDataLoader(std::string stageDataName);
	~StageDataLoader();
};

