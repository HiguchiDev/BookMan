#pragma once
#include "ItemAbility.h"

class Trap;

class SpringThrowType :
	public ItemAbility
{
private:
	std::shared_ptr<Trap> _spring;
public:
	bool throwAbility(std::shared_ptr<PlayerDatas> playerDatas);
	void use(std::shared_ptr<PlayerDatas> playerDatas);
	SpringThrowType();
	~SpringThrowType();
};

