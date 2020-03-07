#pragma once
#include "WearProtective.h"
#include <string>

class LeatherSuit :
	public WearProtective
{
private:

public:
	LeatherSuit(std::string name);
	~LeatherSuit();
};

