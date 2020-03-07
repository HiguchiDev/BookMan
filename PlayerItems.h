#pragma once
#include <vector>
#include <memory>
class ItemAbility;
class Character;
class PlayerDatas;
class Player;
class TurnController;

class PlayerItems
{
private:
	std::shared_ptr<TurnController> _turnController;
	std::vector<std::shared_ptr<ItemAbility>> _items;
	int _fullNum;
	std::shared_ptr<Character> _player;
public:
	void initialize(std::shared_ptr<TurnController> turnController, std::shared_ptr<Character> player){ this->_turnController = turnController;  this->_player = player; }
	bool throwItem(int index, std::shared_ptr<PlayerDatas> playerDatas);
	void use(int index, std::shared_ptr<PlayerDatas> playerDatas);
	std::string getName(int index);
	int getSize();
	void save(int index);
	void load(int index);
	bool isFull();
	bool add(std::shared_ptr<ItemAbility> item);
	bool add_startingPreparation(std::shared_ptr<ItemAbility> item);
	bool isEmpty();
	std::shared_ptr<ItemAbility> getAndErase(int index);
	std::shared_ptr<ItemAbility> get(int index){ return this->_items[index]; };
	PlayerItems(int fullNum);
	~PlayerItems();
};

