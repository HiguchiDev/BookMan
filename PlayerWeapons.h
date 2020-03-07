#pragma once
#include <memory>
#include <vector>

class Weapon;

class PlayerWeapons
{
public:
	std::vector<std::shared_ptr<Weapon>> _weapons;
	int _fullNum;
public:
	//void use(int index, std::shared_ptr<PlayerDatas> playerDatas);
	std::string getName(int index);
	std::shared_ptr<Weapon> get(int index);
	int getSize();
	void save(int index);
	void load(int index);
	bool isFull();
	void add(std::shared_ptr<Weapon> item);
	bool isEmpty();
	std::shared_ptr<Weapon> getAndErase(int index);
	PlayerWeapons(int fullNum);
	~PlayerWeapons();
};

