#pragma once
#include <vector>
#include <memory>

class Character;
class Obstacle;
class Floor;
class TurnController;
class LoadScreen;
class Stairs;
class Item;
class Trap;

class FloorOfTheDungeon
{
protected:
	int _floorHandleCount = 0;
	int _floorHandle;
	std::vector< std::shared_ptr<Character> > _enemys;
	std::shared_ptr< Character > _player;
	std::shared_ptr< TurnController > _turnController;
	std::vector< std::shared_ptr<Obstacle>> _obstacles;
	std::vector< std::shared_ptr<Floor>> _floors;
	std::vector<std::shared_ptr<Item>> _items;
	std::vector<std::shared_ptr<Trap>> _traps;
	std::shared_ptr<Stairs> _stairs;
	bool _finish;

	bool _next;
	int _transparency;
	int _value;
	bool _allInitialized;
	int _messageHandle;
public:
	void addStageMaterial(std::shared_ptr<Trap> trap);
	void addStageMaterial(std::shared_ptr<Item> item);
	static const int _ONESTAGEFLOORLENGTH = 40;
	void initialize();
	virtual bool isFinish();
	void finalize();
	bool isInitialized();
	bool isNext(){ return this->_next; };
	virtual void start();
	void start(int key, std::string message);
	FloorOfTheDungeon(std::string floorFileName, std::shared_ptr<Stairs> stairs, std::vector< std::shared_ptr<Character> > enemys, std::shared_ptr< Character > player, std::vector< std::shared_ptr<Obstacle> > obstacles, std::vector< std::shared_ptr<Floor>> floors, std::vector<std::shared_ptr<Item>> items, std::vector<std::shared_ptr<Trap>> traps, std::shared_ptr<TurnController> turnController);
	~FloorOfTheDungeon();
};

