#pragma once
class Action
{
public:
	enum Actions{
		ATTACK,
		MOVE,
		BENDBACKWARD,	//������
		NEUTRAL,
		DEATH,
		WARP,
		EXAMINED,
		MENUOPEN,
		DECISION,	//����
		CANCEL,	//�L�����Z��
	};

	Action();
	~Action();
};

