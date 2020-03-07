#pragma once
#include <unordered_map>

class AbnormalState
{
public:
	//���
	enum Kind{
		PARALYSIS,
		POISON,
	};
private:
	std::unordered_map<Kind, int> _abnormalStateTurnNum;	//��Ԉُ�̎c��^�[����

public:
	void update(Kind KIND, int point);
	int getTurnNum(Kind KIND);
	AbnormalState();
	~AbnormalState();
};

