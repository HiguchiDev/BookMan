#include "WeaponWarehouse.h"
#include "Weapon.h"
#include <fstream>
#include <string>
#include "DxLib.h"

WeaponWarehouse::WeaponWarehouse()
{
}


WeaponWarehouse::~WeaponWarehouse()
{
}

std::shared_ptr<Weapon> WeaponWarehouse::get(int index)
{
	if (index >= this->_weapons.size()){
		return nullptr;
	}
	else{
		return this->_weapons[index];
	}
}

void WeaponWarehouse::add(std::shared_ptr<Weapon> itemAbility)
{
	this->_weapons.push_back(itemAbility);
}

void WeaponWarehouse::save(int dataIndex)
{
	std::string fileName = "WeaponWarehouse" + std::to_string(dataIndex);
	fileName += ".csv";

	std::ofstream afs(fileName, std::ios_base::trunc);

	if (!afs.is_open()){
		//printfDx("ItemDataをセーブできませんでした。\n");
	}
	else{
		for (int i = 0; i < this->_weapons.size(); i++){
			afs << this->_weapons[i]->toString() << std::endl;
		}
	}
}

bool WeaponWarehouse::isEmpty()
{
	return this->_weapons.empty();
}

std::shared_ptr<Weapon> WeaponWarehouse::getAndErase(int index)
{
	std::shared_ptr<Weapon> returnItem = this->_weapons[index];

	this->_weapons.erase(this->_weapons.begin() + index);

	return returnItem;
}


int WeaponWarehouse::getSize()
{
	return this->_weapons.size();
}

void WeaponWarehouse::load(int dataIndex)
{
	std::string fileName = "WeaponWarehouse" + std::to_string(dataIndex);
	fileName += ".csv";

	std::fstream ifs(fileName);

	if (!ifs.is_open()) {
	//	printfDx("%sをロードできませんでした。\n", fileName.c_str());
	}
	else{
		
		while (1){
			std::string itemName;
			std::getline(ifs, itemName);

			if (ifs.eof() || ifs.fail()){
				break;
			}
			std::shared_ptr<Weapon> w = Weapon::createInstance(itemName);
			if (w != nullptr){
				this->_weapons.push_back(w);
			
			}
		}
	}
}