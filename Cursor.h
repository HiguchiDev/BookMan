#pragma once
#include "MoveType.h"
#include <memory>

class ScreenMaterial;

class Cursor
{
protected:
	float _distanceRow;
	float _distanceColumn;
	int _selectedNum;
	int _menuNum;
	std::shared_ptr<ScreenMaterial> _obj;
	float _x, _y;
public:
	void update();
	int getMenuNum(){ return this->_menuNum; };
	void updateMenuNum(int newMenuNum);
	virtual void move(MoveType::MoveTypes MOVETYPE);
	int getSelectedNum();

	Cursor(int menuNum, float distanceRow, float distanceColumn, float x, float y);
	~Cursor();
};

