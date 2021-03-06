#include "ItemAbility.h"
#include "PlayerDatas.h"
#include "DxLib.h"
#include "StatesPoint.h"
#include "HealthItem.h"
#include "SpringThrowType.h"

ItemAbility::ItemAbility()
{
	this->_name = "あいてむ";
}


ItemAbility::~ItemAbility()
{
}

std::string ItemAbility::toString()
{
	return this->_name;
}

std::shared_ptr<ItemAbility> ItemAbility::createInstance(std::string fileName)
{
	if (fileName == "かいふく小"){
		return std::make_shared<HealthItem>(0.25f, "25％", "かいふく小");
	}
	else if (fileName == "かいふく中"){
		return std::make_shared<HealthItem>(0.5f, "50％", "かいふく中");
	}
	else if (fileName == "かいふく大"){
		return std::make_shared<HealthItem>(0.75f, "75％", "かいふく大");
	}
	else if (fileName == "ワープ"){
		return std::make_shared<SpringThrowType>();
	}
	else{
		return nullptr;
	}
}