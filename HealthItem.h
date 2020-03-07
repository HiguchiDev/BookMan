#pragma once
#include "ItemAbility.h"

class HealthItem :
	public ItemAbility
{
private:
	float _percent;
public:
	void use(std::shared_ptr<PlayerDatas> playerDatas);
	HealthItem(float percent, std::string percentString, std::string name);
	~HealthItem();
};

