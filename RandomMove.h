#pragma once
#include "Random.h"

class RandomMove
{
private:
	Random _randomGetter;
public:

	int getRandomMoveValue(int limit);

	RandomMove();
	~RandomMove();
};

