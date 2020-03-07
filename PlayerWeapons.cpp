#include "PlayerWeapons.h"
#include "Weapon.h"
#include "PlayerDatas.h"
#include "DxLib.h"
#include <fstream>

PlayerWeapons::PlayerWeapons(int fullNum)
{
	this->_fullNum = fullNum;
	
}


PlayerWeapons::~PlayerWeapons()
{
}

void PlayerWeapons::add(std::shared_ptr<Weapon> item)
{
	this->_weapons.push_back(item);
}

void PlayerWeapons::save(int index)
{
	std::string fileName = "PlayerWeapons" + std::to_string(index);
	fileName += ".csv";

	std::ofstream afs(fileName, std::ios_base::trunc);

	if (!afs.is_open()){
		printfDx("ItemDataをセーブできませんでした。\n");
	}
	else{
		for (int i = 0; i < this->_weapons.size(); i++){
			afs << this->_weapons[i]->toString() << std::endl;
			afs << this->_weapons[i]->getDurability() << std::endl;
		}
	}
}

std::shared_ptr<Weapon> PlayerWeapons::getAndErase(int index)
{
	std::shared_ptr<Weapon> returnItem = this->_weapons[index];

	this->_weapons.erase(this->_weapons.begin() + index);

	return returnItem;
}

std::shared_ptr<Weapon> PlayerWeapons::get(int index)
{
	std::shared_ptr<Weapon> returnItem = this->_weapons[index];
	return returnItem;
}

bool PlayerWeapons::isEmpty()
{
	return this->_weapons.empty();
}

void PlayerWeapons::load(int index)
{
	std::string fileName = "PlayerWeapons" + std::to_string(index);
	fileName += ".csv";

	std::fstream ifs(fileName);

	if (!ifs.is_open()) {
		printfDx("PlayerWeaponsをロードできませんでした。\n");
	}
	else{
		while (1){
			std::string itemName;
			std::getline(ifs, itemName);

			std::string durability;
			std::getline(ifs, durability);

			if (ifs.eof() || ifs.fail()){
				break;
			}

			std::shared_ptr<Weapon> createdWeapon = Weapon::createInstance(itemName);
			if (createdWeapon != nullptr){
				createdWeapon->setDurability(std::atoi(durability.c_str()));
				this->_weapons.push_back(createdWeapon);
			}
		}
	}

	//printfDx("PlayerWeaponsロード %d\n", this->_weapons.size());
}
/*
void PlayerWeapons::use(int index, std::shared_ptr<PlayerDatas> playerDatas)
{
	this->_weapons[index]->use(playerDatas);

	this->_weapons.erase(this->_weapons.begin() + index);
}*/

bool PlayerWeapons::isFull()
{
	return this->_weapons.size() == this->_fullNum;
}

int PlayerWeapons::getSize()
{
	return this->_weapons.size();
}

std::string PlayerWeapons::getName(int index)
{
	return this->_weapons[index]->toString();
}