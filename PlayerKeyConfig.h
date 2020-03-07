#pragma once
#include <unordered_map>
#include "Direction.h"
#include "MoveType.h"
#include "Action.h"

class PlayerKeyConfig
{
private:
	std::unordered_map<Direction::Directions, int> _cameraDirectionKeyConfig;
	std::unordered_map<MoveType::MoveTypes, int> _moveKeyConfig;
	std::unordered_map<Action::Actions, int> _actionKeyConfig;
public:
	int PlayerKeyConfig::getActionTypeKey(Action::Actions ACTION);
	int getMoveTypeKey(MoveType::MoveTypes MOVETYPE);
	int getCameraDirectionKey(Direction::Directions DIRECTION);
	void setConfig(int, Direction::Directions DIRECTION);
	void setConfig(int, MoveType::MoveTypes MOVETYPE);

	PlayerKeyConfig();
	~PlayerKeyConfig();
};

