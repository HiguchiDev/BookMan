#pragma once
#include <memory>

class Player;

class Save
{
private:

public:
	void dataSave(std::shared_ptr<Player> player);
	Save();
	~Save();
};

