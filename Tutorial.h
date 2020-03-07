#pragma once
#include "Scene.h"
#include "Stage.h"
#include <vector>
#include "FloorOfTheDungeon.h"
#include <memory>
#include <string>

class Item;
class StatesPoint;
class TurnController;
class Character;
class PlayerDatas;
class Key;
class SaveBook;
class Obstacle;
class Trap;

class Turorial :
	public Stage
{
private:
	std::vector<int> _tutorialOperation;
	std::vector<std::string> _tutorialMessage;

	bool _messageSend;
	bool _messageSend1;
	int _index = 0;
public:
	virtual void update();
	void initializeFloor();
	void actionBlackOuted();
	Turorial(std::shared_ptr<PlayerDatas> playerDatas, std::string stageName);
	~Turorial();

};