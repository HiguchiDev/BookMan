#pragma once
#include "WearProtective.h"
#include <string>

class SwordsMan :
	public WearProtective
{
public:
	SwordsMan(std::string name);
	~SwordsMan();
};

