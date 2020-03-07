#pragma once
#include <vector>
#include <memory>

class WearProtective;

class WearWarehouse
{
private:
	std::vector<std::shared_ptr<WearProtective>> _weapons;

public:
	std::shared_ptr<WearProtective> get(int index);
	std::shared_ptr<WearProtective> getAndErase(int index);
	int getSize();
	bool isEmpty();
	void add(std::shared_ptr<WearProtective> weapon);
	void save(int dataIndex);
	void load(int dataIndex);
	WearWarehouse();
	~WearWarehouse();
};

