#include "DropWeapon.h"
#include "Weapon.h"
#include "PlayerDatas.h"
#include "PlayerWeapons.h"
#include "MessgeBox.h"

DropWeapon::DropWeapon(std::shared_ptr<Weapon> weapon)
{
	this->_weapon = weapon;
}


DropWeapon::~DropWeapon()
{
}

void DropWeapon::use(std::shared_ptr<PlayerDatas> playerDatas)
{
	std::string message = this->_weapon->toString() + "‚ðŽè‚É“ü‚ê‚Ü‚µ‚½B";
	MessgeBox::getInstance()->add(message);
	playerDatas->getPlayerWeapons()->add(this->_weapon);
	//this->_weapon
}