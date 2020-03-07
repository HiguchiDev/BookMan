#pragma once
#include "Weapon.h"
#include <unordered_map>
#include <memory>

class StatesPoint;

class SwordOfTheTree :
	public Weapon
{
private:
	std::string _name;
	std::shared_ptr<StatesPoint> _statesPoint;
public:
	std::string toString();
	void attack(std::shared_ptr<Character> character, Direction::Directions DIRECTION);
	SwordOfTheTree(std::string name, WeaponType::Type TYPE);
	~SwordOfTheTree();
};

