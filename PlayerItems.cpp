#include "PlayerItems.h"
#include "ItemAbility.h"
#include "Character.h"
#include "PlayerDatas.h"
#include <fstream>
#include "MessgeBox.h"
#include "Player.h"
#include "TurnController.h"

PlayerItems::PlayerItems(int fullNum)
{
	this->_fullNum = fullNum;
}


PlayerItems::~PlayerItems()
{
}

bool PlayerItems::add(std::shared_ptr<ItemAbility> item)
{
	if (this->_items.size() < this->_fullNum){
		std::string message = item->toString();
		message += "をてにいれました。";
		MessgeBox::getInstance()->add(message);
		this->_items.push_back(item);
		return true;
	}
	else{
		MessgeBox::getInstance()->add("アイテムがいっぱいです。");
		return false;
	}
}

bool PlayerItems::add_startingPreparation(std::shared_ptr<ItemAbility> item)
{
	if (this->_items.size() < this->_fullNum){

		this->_items.push_back(item);
		return true;
	}
	else{
		return false;
	}
}

void PlayerItems::save(int index)
{
	std::string fileName = "PlayerItems" + std::to_string(index);
	fileName += ".csv";

	std::ofstream afs(fileName, std::ios_base::trunc);

	if (!afs.is_open()){
		
		("ItemDataをセーブできませんでした。\n");
	}
	else{
		for (int i = 0; i < this->_items.size(); i++){
			afs << this->_items[i]->toString() << std::endl;
		}
	}
}

std::shared_ptr<ItemAbility> PlayerItems::getAndErase(int index)
{
	std::shared_ptr<ItemAbility> returnItem = this->_items[index];
	
	this->_items.erase(this->_items.begin() + index);
	
	return returnItem;
}

bool PlayerItems::isEmpty()
{
	return this->_items.empty();
}

void PlayerItems::load(int index)
{
	std::string fileName = "PlayerItems" + std::to_string(index);
	fileName += ".csv";
	std::fstream ifs(fileName);

	if (!ifs.is_open()) {
		printfDx("ItemDataをロードできませんでした。\n");
	}
	else{
		while (1){
			std::string itemName;
			std::getline(ifs, itemName);

			if (ifs.eof() || ifs.fail()){
				break;
			}

			this->_items.push_back(ItemAbility::createInstance(itemName));
		}
	}
}

bool PlayerItems::throwItem(int index, std::shared_ptr<PlayerDatas> playerDatas)
{
	if (this->_items[index]->throwAbility(playerDatas)){
		//this->_turnController->setTurnFinishedCharacter(this->_player);
		this->_items.erase(this->_items.begin() + index);

		return true;
	}

	return false;
}


void PlayerItems::use(int index, std::shared_ptr<PlayerDatas> playerDatas)
{
	this->_items[index]->use(playerDatas);
	this->_turnController->setTurnFinishedCharacter(this->_player);
	this->_items.erase(this->_items.begin() + index);
}

bool PlayerItems::isFull()
{
	return this->_items.size() == this->_fullNum;
}

int PlayerItems::getSize()
{
	return this->_items.size();
}

std::string PlayerItems::getName(int index)
{
	return this->_items[index]->toString();
}