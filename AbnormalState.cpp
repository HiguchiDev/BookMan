#include "AbnormalState.h"


AbnormalState::AbnormalState()
{
}


AbnormalState::~AbnormalState()
{
}

void AbnormalState::update(Kind KIND, int point)
{
	this->_abnormalStateTurnNum[KIND] = point;
}

int AbnormalState::getTurnNum(Kind KIND)
{
	return this->_abnormalStateTurnNum[KIND];
}