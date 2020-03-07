#pragma once
#include <unordered_map>

class AbnormalState
{
public:
	//í—Ş
	enum Kind{
		PARALYSIS,
		POISON,
	};
private:
	std::unordered_map<Kind, int> _abnormalStateTurnNum;	//ó‘ÔˆÙí‚Ìc‚èƒ^[ƒ“”

public:
	void update(Kind KIND, int point);
	int getTurnNum(Kind KIND);
	AbnormalState();
	~AbnormalState();
};

