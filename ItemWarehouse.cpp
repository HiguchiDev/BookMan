#include "ItemWarehouse.h"
#include <fstream>
#include "ItemAbility.h"
#include <string>
#include "DxLib.h"

ItemWarehouse::ItemWarehouse()
{
	
}


ItemWarehouse::~ItemWarehouse()
{
}

std::shared_ptr<ItemAbility> ItemWarehouse::get(int index)
{
	if (index >= this->_itemAbilitys.size()){
		return nullptr;
	}
	else{
		return this->_itemAbilitys[index];
	}
}

void ItemWarehouse::add(std::shared_ptr<ItemAbility> itemAbility)
{
	this->_itemAbilitys.push_back(itemAbility);
}

void ItemWarehouse::save(int dataIndex)
{
	std::string fileName = "ItemWarehouse" + std::to_string(dataIndex);
	fileName += ".csv";

	std::ofstream afs(fileName, std::ios_base::trunc);

	if (!afs.is_open()){
	
	}
	else{
		for (int i = 0; i < this->_itemAbilitys.size(); i++){
			afs << this->_itemAbilitys[i]->toString() << std::endl;
		}
	}
}

bool ItemWarehouse::isEmpty()
{
	return this->_itemAbilitys.empty();
}

std::shared_ptr<ItemAbility> ItemWarehouse::getAndErase(int index)
{
	std::shared_ptr<ItemAbility> returnItem = this->_itemAbilitys[index];

	this->_itemAbilitys.erase(this->_itemAbilitys.begin() + index);

	return returnItem;
}


int ItemWarehouse::getSize()
{
	return this->_itemAbilitys.size();
}

void ItemWarehouse::load(int dataIndex)
{
	std::string fileName = "ItemWarehouse" + std::to_string(dataIndex);
	fileName += ".csv";

	std::fstream ifs(fileName);

	if (!ifs.is_open()) {
		printfDx("%s‚ðƒ[ƒh‚Å‚«‚Ü‚¹‚ñ‚Å‚µ‚½B\n", fileName.c_str());
	}
	else{
		while (1){
			std::string itemName;
			std::getline(ifs, itemName);

			if (ifs.eof() || ifs.fail()){
				break;
			}

			this->_itemAbilitys.push_back(ItemAbility::createInstance(itemName));
		}
	}
}