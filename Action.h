#pragma once
class Action
{
public:
	enum Actions{
		ATTACK,
		MOVE,
		BENDBACKWARD,	//‹Â‚¯”½‚é
		NEUTRAL,
		DEATH,
		WARP,
		EXAMINED,
		MENUOPEN,
		DECISION,	//Œˆ’è
		CANCEL,	//ƒLƒƒƒ“ƒZƒ‹
	};

	Action();
	~Action();
};

