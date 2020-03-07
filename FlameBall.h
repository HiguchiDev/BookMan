#pragma once
#include <memory>
#include "Weapon.h"

class Effect;
class StatesPoint;

class FlameBall :
	public Weapon
{
private:
	std::shared_ptr<StatesPoint> _statesPoint;
	std::string _name;
public:
	std::shared_ptr<Effect> _effect;

	std::string toString();
	void attack(std::shared_ptr<Character> character, Direction::Directions DIRECTION);
	FlameBall(std::string name);
	~FlameBall();
};

