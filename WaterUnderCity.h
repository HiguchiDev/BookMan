#pragma once
#include "Stage.h"
#include <memory>

class PlayerDatas;

class WaterUnderCity :
	public Stage
{
public:
	WaterUnderCity(std::shared_ptr<PlayerDatas> playerData);
	~WaterUnderCity();
};

