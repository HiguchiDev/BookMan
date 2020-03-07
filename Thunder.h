#pragma once
#include <memory>
#include "Weapon.h"
#include <vector>

class Effect;
class StatesPoint;

class Thunder :
	public Weapon
{
private:
	std::vector<std::shared_ptr<Effect>> _effects;
	std::shared_ptr<StatesPoint> _statesPoint;
	std::string _name;
public:
	std::shared_ptr<Effect> _effect;

	std::string toString();
	void attack(std::shared_ptr<Character> character, Direction::Directions DIRECTION);
	Thunder(std::string name);
	~Thunder();
};

