#include "DropWear.h"
#include "WearProtective.h"
#include "PlayerDatas.h"
#include "PlayerWearProtective.h"
#include "MessgeBox.h"

DropWear::DropWear(std::shared_ptr<WearProtective> weapon)
{
	this->_weapon = weapon;

	
}


DropWear::~DropWear()
{
}

void DropWear::use(std::shared_ptr<PlayerDatas> playerDatas)
{
	std::string message = this->_weapon->toString() + "‚ðŽè‚É“ü‚ê‚Ü‚µ‚½B";
	MessgeBox::getInstance()->add(message);
	playerDatas->getPlayerWears()->add(this->_weapon);
	//this->_weapon->setVisible(true);
	//this->_weapon
}