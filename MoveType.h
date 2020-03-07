#pragma once
class MoveType
{
public:
	enum MoveTypes{
		LEFT,
		RIGHT,
		UP,
		DOWN,
		LEFTLOWER,
		LEFTUPPER,
		RIGHTLOWER,
		RIGHTUPPER,
	};
	MoveType();
	~MoveType();
};

