#pragma once
#include "Direction.h"
#include "Position.h"
#include "Character.h"

class PlayerFollow
{
public:
	Direction::Directions getFollowDirection(std::shared_ptr<Character> character);
	PlayerFollow();
	~PlayerFollow();
};

