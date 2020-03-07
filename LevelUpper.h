#pragma once
#include "CharacterData.h"
#include <memory>
#include "PlayerDatas.h"

class LevelUpper
{
private:
	static std::shared_ptr<PlayerDatas> _playerDatas;
	static int _exp_nextLevelUp;
public:
	static void addExp(std::shared_ptr<CharacterData> enemyStatesPoint);
	static int nextLevelUpExp();
	static void addExp(std::shared_ptr<CharacterData> enemyStatesPoint, bool isInit);
	static void initialize(std::shared_ptr<PlayerDatas> statesPoint);
	LevelUpper(std::shared_ptr<PlayerDatas> statesPoint);
	~LevelUpper();
};

