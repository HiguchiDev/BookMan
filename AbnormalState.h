#pragma once
#include <unordered_map>

class AbnormalState
{
public:
	//種類
	enum Kind{
		PARALYSIS,
		POISON,
	};
private:
	std::unordered_map<Kind, int> _abnormalStateTurnNum;	//状態異常の残りターン数

public:
	void update(Kind KIND, int point);
	int getTurnNum(Kind KIND);
	AbnormalState();
	~AbnormalState();
};

