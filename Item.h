#pragma once
#include "FieldMaterial.h"
#include <memory>
#include <string>

class Character;
class Effect;
class PlayerDatas;
class Position;
class ItemAbility;

class Item
	: public FieldMaterial, public std::enable_shared_from_this<Item>
{
protected:
	std::shared_ptr<Effect> _effect;
	std::string _name;
	std::shared_ptr<ItemAbility> _ability;
public:
	bool isWeaponChange();
	bool isWearChange();
	std::shared_ptr<ItemAbility> getAbility();
	void updateCollisionInformation(std::shared_ptr<Position> newPosition);
	void initializePosition();
	void update();
	static std::shared_ptr<Item> createItem(std::string fileName, std::shared_ptr<Position> position);
	std::string toString();
	Item(std::string fileName, std::shared_ptr<Position> position);
	Item(std::string fileName, std::shared_ptr<Position> position, std::shared_ptr<ItemAbility> ability);
	~Item();
};

