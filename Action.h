#pragma once
class Action
{
public:
	enum Actions{
		ATTACK,
		MOVE,
		BENDBACKWARD,	//仰け反る
		NEUTRAL,
		DEATH,
		WARP,
		EXAMINED,
		MENUOPEN,
		DECISION,	//決定
		CANCEL,	//キャンセル
	};

	Action();
	~Action();
};

