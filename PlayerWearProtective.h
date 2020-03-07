#pragma once
#include "WearProtective.h"
#include <memory>
#include <vector>

class PlayerWearProtective
{
private:
	std::vector<std::shared_ptr<WearProtective>> _wears;
public:
	void setDurability(int durability);
	void add(std::shared_ptr<WearProtective> wear);
	std::shared_ptr<WearProtective> getAndErase(int index);
	std::shared_ptr<WearProtective> get(int index);
	bool isFull(){ return this->_wears.size() >= 3; };
	int getSize();
	bool isEmpty();
	void save(int index);
	void load(int index);
	PlayerWearProtective();
	~PlayerWearProtective();
};

