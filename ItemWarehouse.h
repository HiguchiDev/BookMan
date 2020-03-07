#pragma once
#include <memory>
#include <vector>

class ItemAbility;

class ItemWarehouse
{
private:
	std::vector<std::shared_ptr<ItemAbility>> _itemAbilitys;
public:
	std::shared_ptr<ItemAbility> get(int index);
	std::shared_ptr<ItemAbility> getAndErase(int index);
	int getSize();
	bool isEmpty();
	void add(std::shared_ptr<ItemAbility> itemAbility);
	void save(int dataIndex);
	void load(int dataIndex);
	ItemWarehouse();
	~ItemWarehouse();
};

