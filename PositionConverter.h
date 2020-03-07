#pragma once
#include "DxLib.h"
#include <memory>

class Position;

class PositionConverter
{
private:
	const float _BLOCKBASE;
	const float _BLOCKHEIGHT;
	const float _BLOCKDEPTH;
public:
	VECTOR get3DPosition(std::shared_ptr<Position> position);

	PositionConverter();
	~PositionConverter();
};

