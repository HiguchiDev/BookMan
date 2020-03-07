#include "ItemAbility.h"
#include "PlayerDatas.h"
#include "DxLib.h"
#include "StatesPoint.h"
#include "HealthItem.h"
#include "SpringThrowType.h"

ItemAbility::ItemAbility()
{
	this->_name = "�����Ă�";
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
	if (fileName == "�����ӂ���"){
		return std::make_shared<HealthItem>(0.25f, "25��", "�����ӂ���");
	}
	else if (fileName == "�����ӂ���"){
		return std::make_shared<HealthItem>(0.5f, "50��", "�����ӂ���");
	}
	else if (fileName == "�����ӂ���"){
		return std::make_shared<HealthItem>(0.75f, "75��", "�����ӂ���");
	}
	else if (fileName == "���[�v"){
		return std::make_shared<SpringThrowType>();
	}
	else{
		return nullptr;
	}
}