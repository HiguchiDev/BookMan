#include "PlayerWearProtective.h"
#include <fstream>

PlayerWearProtective::PlayerWearProtective()
{
}


PlayerWearProtective::~PlayerWearProtective()
{
}

void PlayerWearProtective::add(std::shared_ptr<WearProtective> wear)
{
	this->_wears.push_back(wear);
}

int PlayerWearProtective::getSize()
{
	return this->_wears.size();
}

bool PlayerWearProtective::isEmpty()
{
	return this->_wears.empty();
}

std::shared_ptr<WearProtective> PlayerWearProtective::getAndErase(int index)
{
	std::shared_ptr<WearProtective> returnItem = this->_wears[index];

	this->_wears.erase(this->_wears.begin() + index);

	return returnItem;
}

std::shared_ptr<WearProtective> PlayerWearProtective::get(int index)
{
	return this->_wears[index];
}

void PlayerWearProtective::load(int index)
{
	std::string fileName = "PlayerWear" + std::to_string(index);
	fileName += ".csv";

	std::fstream ifs(fileName);

	if (!ifs.is_open()) {
		printfDx("PlayerWearをロードできませんでした。\n");
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

			std::shared_ptr<WearProtective> createdWear = WearProtective::createInstance(itemName);
			createdWear->setDurability(std::atoi(durability.c_str()));

			this->_wears.push_back(createdWear);
		}
	}

}

void PlayerWearProtective::save(int index)
{
	std::string fileName = "PlayerWear" + std::to_string(index);
	fileName += ".csv";

	std::ofstream afs(fileName, std::ios_base::trunc);

	if (!afs.is_open()){
		printfDx("PlayerWearセーブできませんでした。\n");
	}
	else{
		for (int i = 0; i < this->_wears.size(); i++){
			afs << this->_wears[i]->toString() << std::endl;
			afs << this->_wears[i]->getStatesCorrection()->getStatesPoint(State::DURABILITY) << std::endl;
		}
	}
}