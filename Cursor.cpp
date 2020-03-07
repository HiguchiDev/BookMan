#include "Cursor.h"
#include "DxLib.h"
#include "Object_2D.h"
#include "Object2DAttribute.h"

void Cursor::move(MoveType::MoveTypes MOVETYPE)
{
	if (MOVETYPE == MoveType::UP && this->_selectedNum > 0){
		this->_obj->setPosition(VGet(this->_obj->getPosition().x, this->_obj->getPosition().y - this->_distanceColumn, this->_obj->getPosition().z));
		this->_selectedNum--;
	}
	else if (MOVETYPE == MoveType::DOWN && this->_selectedNum < this->_menuNum - 1){
		this->_obj->setPosition(VGet(this->_obj->getPosition().x, this->_obj->getPosition().y + this->_distanceColumn, this->_obj->getPosition().z));
		this->_selectedNum++;
	}
}

int Cursor::getSelectedNum()
{
	return this->_selectedNum;
}

void Cursor::updateMenuNum(int newMenuNum)
{
	if (newMenuNum >= 0){
		this->_menuNum = newMenuNum;

		if (this->_selectedNum > this->_menuNum - 1 && this->_selectedNum > 0){
			this->_obj->setPosition(VGet(this->_obj->getPosition().x, this->_obj->getPosition().y - (this->_distanceColumn * (this->_selectedNum - (this->_menuNum - 1))), this->_obj->getPosition().z));
			this->_selectedNum = this->_menuNum - 1;
		}
	}
}

Cursor::Cursor(int menuNum, float distanceRow, float distanceColumn, float x, float y)
{
	this->_distanceRow = distanceRow;
	this->_distanceColumn = distanceColumn;
	this->_selectedNum = 0;
	this->_menuNum = menuNum;
	this->_obj = std::make_shared<Object_2D>("Cursor.png");
	this->_x = x;
	this->_y = y;
	this->_obj->setPosition(VGet(this->_x, this->_y, 0.0));
}

Cursor::~Cursor()
{
}

void Cursor::update()
{
	this->_obj->draw();
}