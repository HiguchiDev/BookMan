#include "Item.h"
#include "Character.h"
#include "Effect.h"
#include "PositionConverter.h"
#include "PlayerDatas.h"
#include "StatesPoint.h"
#include "ItemAbility.h"
#include "HealthItem.h"
#include "Weapon.h"
#include "DropWeapon.h"
#include "DropWear.h"
#include "WearProtective.h"
#include "SpringThrowType.h"

Item::Item(std::string fileName, std::shared_ptr<Position> position) : FieldMaterial(fileName, position)
{
	this->_effect = std::make_shared<Effect>("Health.efk");
	this->_name = "ƒAƒCƒeƒ€";
	//this->_ability = std::make_shared<HealthItem>();
	this->_visible = true;
//	this->_screenMaterial->setVisible(false);
}

Item::Item(std::string fileName, std::shared_ptr<Position> position, std::shared_ptr<ItemAbility> ability) : FieldMaterial(fileName, position)
{
	this->_effect = std::make_shared<Effect>("Health.efk");
	this->_ability = ability;
	this->_visible = true;

//	this->_screenMaterial->setVisible(false);
}

std::shared_ptr<ItemAbility> Item::getAbility()
{
	return this->_ability;
}

bool Item::isWeaponChange()
{

	return this->_ability->isWeaponChange();
}

bool Item::isWearChange()
{
	return this->_ability->isWearChange();
}

Item::~Item()
{
}

void Item::update()
{
	this->_effect->update();
}

std::string Item::toString()
{
	return this->_name;
}

void Item::updateCollisionInformation(std::shared_ptr<Position> newPosition)
{

}

void Item::initializePosition()
{
	Collision::getInstance()->add(shared_from_this(), this->getPos());
}

std::shared_ptr<Item> Item::createItem(std::string fileName, std::shared_ptr<Position> position)
{
	std::shared_ptr<ItemAbility> ability = ItemAbility::createInstance(fileName);

	if (ability != nullptr){
		return std::make_shared<Item>("potion.pmd", position, ability);
	}
	else{
		std::shared_ptr<Weapon> weapon;

		weapon = Weapon::createInstance(fileName.c_str());

		std::shared_ptr<WearProtective> wear;

		wear = WearProtective::createInstance(fileName.c_str());

		if (weapon != nullptr){
			return std::make_shared<Item>("Œ•.pmd", position, std::make_shared<DropWeapon>(weapon));
		}
		else if (wear != nullptr){
			return std::make_shared<Item>("•ž.pmd", position, std::make_shared<DropWear>(wear));
		}
		else{
			return nullptr;
		}
	}


	return nullptr;
}