#pragma once
#include "Scene.h"
#include <memory>
#include <vector>
#include <string>

class PlayerDatas;
class Cursor;

class EquipScreen
	: public Scene
{
private:
	int _menuBackHandle;
	int _screenLimit;
	float _equipmentNameInterval_x;
	float _equipmentNameInterval_y;
	std::shared_ptr<Cursor> _cursor;
	bool _weapon;
	std::shared_ptr<Cursor> _cursor2;
	int _command = false;
public:
	void update();
	void finalize();
	EquipScreen(std::shared_ptr<PlayerDatas> playerDatas);
	~EquipScreen();
};