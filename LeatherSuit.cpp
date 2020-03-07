#include "LeatherSuit.h"


LeatherSuit::LeatherSuit(std::string name) : WearProtective(name)
{
	//this->_statesCorrection->upDateStatesPoint(State::DEFENSE, 5);

	this->_TYPE = WearProtective::SWORDSMAN;
}


LeatherSuit::~LeatherSuit()
{
}
