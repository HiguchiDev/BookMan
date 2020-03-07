#pragma once
#include "Scene.h"
#include <vector>
#include <string>

class Ending :
	public Scene
{
private:
	std::vector<std::string> _endingMessages;
	std::vector<int> _messageY;
	int _interval = 0;
public:
	void update();
	void finalize();
	Ending();
	~Ending();
};

