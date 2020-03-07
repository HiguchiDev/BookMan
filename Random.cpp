#include "Random.h"
#include "DxLib.h"

Random::Random()
{
}


Random::~Random()
{
}

bool Random::isWinning(int percent)
{
	return !(GetRand(99) + 1 >= percent);
}