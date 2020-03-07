#pragma once
#include <memory>
#include "Direction.h"
#include <string>
#include "WeaponType.h"
#include <unordered_map>

class Character;

class Weapon
{
protected:
	WeaponType::Type _TYPE;
	std::unordered_map<Direction::Directions, int> _distanceOfRow;
	std::unordered_map<Direction::Directions, int> _distanceOfColumn;
	int _damege;
	bool _broken;
	int _durability;
public:
	void setDurability(int durability);
	int getDurability();
	void giveDamage(int point);
	int getDamege(){ return this->_damege; };
	WeaponType::Type getType(){ return this->_TYPE; };
	virtual void attack(std::shared_ptr<Character> character, Direction::Directions DIRECTION) = 0;
	virtual std::string toString() = 0;
	static std::shared_ptr<Weapon> createInstance(std::string name);
	static std::shared_ptr<Weapon> createInstance(int damage);
	Weapon();
	~Weapon();
};

