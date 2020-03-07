#pragma once
#include <memory>
#include <vector>
#include "CharacterData.h"
#include "ScreenMaterial.h"

class PlayerItems;
class StatesPoint;
class PlayerKeyConfig;
class ItemWarehouse;
class WeaponWarehouse;
class PlayerWeapons;
class Player;
class Weapon;
class Trap;
class WearWarehouse;
class PlayerWearProtective;
class Character;
class WearProtective;

class PlayerDatas
	: public CharacterData
{
private:
	std::shared_ptr<ItemWarehouse> _itemWarehouse;
	std::shared_ptr<WeaponWarehouse> _weaponWarehouse;
	std::shared_ptr<PlayerItems> _playerItems;
	std::shared_ptr<PlayerKeyConfig> _playerKeyConfig;
	std::vector<std::string> _crearedStageNames;
	std::shared_ptr<PlayerWeapons> _playerWeapons;
	std::string _activeStageName;
	std::shared_ptr<Weapon> _equipedWeapon;
	std::shared_ptr<WearProtective> _equipedWear;
	std::shared_ptr<PlayerWearProtective> _playerWears;
	std::shared_ptr<WearWarehouse> _wearWarehouse;
	std::shared_ptr<Trap> _trap;
	
	int _stageFloor;
	int handle;
	int mPHandle;
public:
	std::shared_ptr<WearWarehouse> getWearWarehouse();
	std::shared_ptr<ItemWarehouse> getWarehouse();
	std::shared_ptr<WeaponWarehouse> getWeaponWarehouse();
	std::shared_ptr<PlayerKeyConfig> getPlayerKeyConfig();
	std::shared_ptr<PlayerWearProtective> getPlayerWears();
	std::shared_ptr<PlayerItems> getPlayerItems();
	std::shared_ptr<PlayerWeapons> getPlayerWeapons();

	void updateStatesPoint();
	void addThrowTrap(std::shared_ptr<Trap> trap){ this->_trap = trap; };
	std::shared_ptr<Trap> getTrap(){ return this->_trap; };
	void initialize(std::shared_ptr<Character> player);

	void equipWeapon(int index);
	void equipWear(int index);
	std::shared_ptr<Weapon> getEquipedWeapon();
	std::shared_ptr<WearProtective> getEquipedWear();
	void removeStageData();
	void setStageFloor(int index);
	int getStageFloor();
	void draw();

	void setActiveStageName(std::string name);
	std::string getActiveStageName();

	bool load(int index);
	
	void save_stageDataIncludes(int index);
	void save(int index);

	PlayerDatas();
	~PlayerDatas();
};

