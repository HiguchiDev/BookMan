#include "ItemAbility.h"
#include "PlayerDatas.h"
#include "DxLib.h"
#include "StatesPoint.h"
#include "HealthItem.h"
#include "SpringThrowType.h"

ItemAbility::ItemAbility()
{
	this->_name = "‚ ‚¢‚Ä‚Ş";
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
	if (fileName == "‚©‚¢‚Ó‚­¬"){
		return std::make_shared<HealthItem>(0.25f, "25“", "‚©‚¢‚Ó‚­¬");
	}
	else if (fileName == "‚©‚¢‚Ó‚­’†"){
		return std::make_shared<HealthItem>(0.5f, "50“", "‚©‚¢‚Ó‚­’†");
	}
	else if (fileName == "‚©‚¢‚Ó‚­‘å"){
		return std::make_shared<HealthItem>(0.75f, "75“", "‚©‚¢‚Ó‚­‘å");
	}
	else if (fileName == "ƒ[ƒv"){
		return std::make_shared<SpringThrowType>();
	}
	else{
		return nullptr;
	}
}