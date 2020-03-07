#pragma once
#include "Obstacle.h"
#include <string>
#include <vector>

class Item;
class Motion;

class TreasureChest :
	public Obstacle
{
private:
	std::shared_ptr<Motion> _motion;
	//std::string _itemName;
	std::shared_ptr<Item> _item;
	bool _open = false;
public:
	void action();
	std::shared_ptr<Item> getChangedItem();
	bool beExamined();
	TreasureChest(std::string fileName, std::shared_ptr<Position> position, std::shared_ptr<Item> item);
	~TreasureChest();
};

