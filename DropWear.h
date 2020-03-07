#pragma once
#include "ItemAbility.h"
#include <memory>

class WearProtective;

class DropWear :
	public ItemAbility
{
private:
	std::shared_ptr<WearProtective> _weapon;
public:
	bool isWeaponChange(){ return false; };
	bool isWearChange(){ return true; };
	void use(std::shared_ptr<PlayerDatas> playerDatas);
	DropWear(std::shared_ptr<WearProtective> weapon);
	~DropWear();
};

