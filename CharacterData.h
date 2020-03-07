#pragma once
#include <memory>
#include "StatesPoint.h"
#include <string>

class CharacterData
{
protected:
	std::shared_ptr<StatesPoint> _statesPoint;
	std::string _characterName;
public:
	void dataRead();
	std::shared_ptr<StatesPoint> getStatesPoint();
	CharacterData(std::string fileName);
	~CharacterData();
};