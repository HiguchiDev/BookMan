#include "WearWarehouse.h"
#include "WearProtective.h"
#include <fstream>
#include <string>
#include "DxLib.h"

WearWarehouse::WearWarehouse()
{
}


WearWarehouse::~WearWarehouse()
{
}

std::shared_ptr<WearProtective> WearWarehouse::get(int index)
{
	if (index >= this->_weapons.size()){
		return nullptr;
	}
	else{
		return this->_weapons[index];
	}
}

void WearWarehouse::add(std::shared_ptr<WearProtective> itemAbility)
{
	this->_weapons.push_back(itemAbility);
}

void WearWarehouse::save(int dataIndex)
{
	std::string fileName = "WearWarehouse" + std::to_string(dataIndex);
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

bool WearWarehouse::isEmpty()
{
	return this->_weapons.empty();
}

std::shared_ptr<WearProtective> WearWarehouse::getAndErase(int index)
{
	std::shared_ptr<WearProtective> returnItem = this->_weapons[index];

	this->_weapons.erase(this->_weapons.begin() + index);

	return returnItem;
}


int WearWarehouse::getSize()
{
	return this->_weapons.size();
}

void WearWarehouse::load(int dataIndex)
{
	std::string fileName = "WearWarehouse" + std::to_string(dataIndex);
	fileName += ".csv";

	std::fstream ifs(fileName);

	if (!ifs.is_open()) {
		//printfDx("%sをロードできませんでした。\n", fileName.c_str());
	}
	else{

		while (1){
			std::string itemName;
			std::getline(ifs, itemName);

			if (ifs.eof() || ifs.fail()){
				break;
			}

			this->_weapons.push_back(WearProtective::createInstance(itemName));
		}
	}
}