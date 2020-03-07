#pragma once
class State
{
public:
	enum States{
		ATTACK,
		DEFENSE,
		HITPOINT,
		MAGICPOINT,
		EXP,
		LEVEL,
		MONEY,

		DURABILITY,	//‘Ï‹v“x
		HPMAX,
		MPMAX,

	};
	States _STATE;

	State();
	~State();
};

