#pragma once
#include "Weapon.h"
class EnemyStandardWeapon :
	public Weapon
{
public:
	std::string toString();
	void attack(std::shared_ptr<Character> character, Direction::Directions DIRECTION);
	EnemyStandardWeapon(int damage);
	~EnemyStandardWeapon();
};

