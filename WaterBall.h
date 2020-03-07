#pragma once
#include "Weapon.h"
#include "Effect.h"

class StatesPoint;

class WaterBall :
	public Weapon
	
{
private:
	std::shared_ptr<Effect> _effect;
	std::shared_ptr<StatesPoint> _statesPoint;
	std::string _name;
public:
	

	std::string toString();
	void attack(std::shared_ptr<Character> character, Direction::Directions DIRECTION);
	WaterBall(std::string name);
	~WaterBall();
};

