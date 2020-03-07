#pragma once
#include "Scene.h"
#include <memory>

class PlayerDatas;
class Cursor;

class StartingPreparation :
	public Scene
{
private:
	std::shared_ptr<Cursor> _warehouseCursor;
	std::shared_ptr<Cursor> _wearWarehouseCursor;

	std::shared_ptr<Cursor> _playerItemCursor;
	std::shared_ptr<PlayerDatas> _playerDatas;
	std::shared_ptr<Cursor> _activeCursor;

	std::shared_ptr<Cursor> _weaponWarehouseCursor;
	std::shared_ptr<Cursor> _playerWearCursor;

	std::shared_ptr<Cursor> _playerWeaponCursor;
	std::shared_ptr<Cursor> _activeWeaponCursor;


	bool _wearSelect;
	int _backGround;
	bool _weaponSelect;
	bool _isInit = false;
public:
	void update();
	void finalize();
	StartingPreparation(std::shared_ptr<PlayerDatas> playerDatas);
	~StartingPreparation();
};

