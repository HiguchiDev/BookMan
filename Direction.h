#pragma once
class Direction
{
public:
	enum Directions{
		EAST,
		WEST,
		NORTH,
		SOUTH,
		EASTNORTH,
		EASTSOUTH,
		WESTNORTH,
		WESTSOUTH,
		COUNT,
	};

	Direction();
	~Direction();
};

