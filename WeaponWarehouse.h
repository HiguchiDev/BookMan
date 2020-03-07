#pragma once
#include <memory>
#include <vector>

class Weapon;

class WeaponWarehouse
{
private:
	std::vector<std::shared_ptr<Weapon>> _weapons;

public:
	std::shared_ptr<Weapon> get(int index);
	std::shared_ptr<Weapon> getAndErase(int index);
	int getSize();
	bool isEmpty();
	void add(std::shared_ptr<Weapon> weapon);
	void save(int dataIndex);
	void load(int dataIndex);
	WeaponWarehouse();
	~WeaponWarehouse();
};

