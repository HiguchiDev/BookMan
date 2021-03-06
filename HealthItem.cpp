#include "HealthItem.h"
#include "PlayerDatas.h"
#include "DxLib.h"
#include "StatesPoint.h"
#include "MessgeBox.h"
#include "Collision.h"
#include "Effect.h"
#include "EffectUpdater.h"
#include "PositionConverter.h"

HealthItem::HealthItem(float percent, std::string percentString, std::string name)
{
	this->_percent = percent;

	this->_name = name;
	this->_explanatoryText = "最大HP の " + percentString;
	this->_explanatoryText += "回復します";
}


HealthItem::~HealthItem()
{
}

void HealthItem::use(std::shared_ptr<PlayerDatas> playerDatas)
{
	std::shared_ptr<Effect> ef = std::make_shared<Effect>("Heal.efk");
	ef->start(Direction::EAST);

	PositionConverter pc;
	ef->setPos(pc.get3DPosition(Collision::getInstance()->getPlayerPos()));
	EffectUpdater::getInstance()->add(ef);
	playerDatas->getStatesPoint()->upDateStatesPoint(State::HITPOINT, playerDatas->getStatesPoint()->getStatesPoint(State::HITPOINT) + playerDatas->getStatesPoint()->getStatesPoint(State::HPMAX) * this->_percent);

	std::string message = "HPが" + std::to_string((int)(playerDatas->getStatesPoint()->getStatesPoint(State::HPMAX) * this->_percent)) + "回復した！";

	MessgeBox::getInstance()->add(message);

}