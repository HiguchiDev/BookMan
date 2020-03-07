#pragma once
#include "ItemAbility.h"
#include <memory>

class Weapon;

class DropWeapon :
	public ItemAbility
{
private:
	std::shared_ptr<Weapon> _weapon;
public:
	bool isWeaponChange(){ return true; };
	bool isWearChange(){ return false; };
	void use(std::shared_ptr<PlayerDatas> playerDatas);
	DropWeapon(std::shared_ptr<Weapon> weapon);
	~DropWeapon();
};

