#pragma once
#include "Scene.h"
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

class Stage :
	public Scene
{
protected:
	std::shared_ptr<TurnController> _turnController;
	std::shared_ptr<SaveBook> _saveBook;
	std::shared_ptr< FloorOfTheDungeon > _floorOfTheDungeons;
	std::string _stageName;
	std::shared_ptr<Character> _player;
	int _floorIndex;
	// 時間を初期化する(定期的にエフェクトを再生するため)
	int time = 0;
	int handle1;
	int effectHandle;
	int _stageClearHandle;
	int _time;
	int _stopTime;
	int _x, _y;
	int _stopX;

	int _gameOverHandle;
	int _time_gameOver;
	int _stopTime_gameOver;
	int _x_gameOver, _y_gameOver;
	int _stopX_gameOver;

public:
	bool isInitialized();
	void addStageMaterial(std::shared_ptr<Item> item);
	void addStageMaterial(std::shared_ptr<Trap> trap);
	void returnAction();
	void finalize();
	virtual void update();
	void initialize();
	Stage(std::shared_ptr<PlayerDatas> playerDatas, std::string stageName);
	~Stage();
protected:
	virtual void initializeFloor();
	virtual void actionBlackOuted();
};

