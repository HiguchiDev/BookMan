#pragma once
#include "Direction.h"
#include "MoveType.h"

class PlayerDirectionGetter
{
public:
	static Direction::Directions get(Direction::Directions CAMERADIRECTION, MoveType::MoveTypes CHARACTERMOVETYPE);
	PlayerDirectionGetter();
	~PlayerDirectionGetter();
};

