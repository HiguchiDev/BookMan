#include "CurorThereIsALimit.h"
#include "ScreenMaterial.h"
#include "DxLib.h"

CurorThereIsALimit::CurorThereIsALimit(int menuNum, float distanceRow, float distanceColumn, float x, float y, int limitNum) : Cursor(menuNum, distanceRow, distanceColumn, x, y)
{
	this->_limitNum = limitNum;
}


CurorThereIsALimit::~CurorThereIsALimit()
{
}

void CurorThereIsALimit::move(MoveType::MoveTypes MOVETYPE)
{
	if (MOVETYPE == MoveType::UP && this->_selectedNum > 0){
		
		

		if (this->_limitNum - this->_selectedNum >= 0){
			this->_obj->setPosition(VGet(this->_obj->getPosition().x, this->_obj->getPosition().y - this->_distanceColumn, this->_obj->getPosition().z));
		}
		
		this->_selectedNum--;
	}
	else if (MOVETYPE == MoveType::DOWN && this->_selectedNum < this->_menuNum - 1){
		if (this->_selectedNum < this->_limitNum){
			this->_obj->setPosition(VGet(this->_obj->getPosition().x, this->_obj->getPosition().y + this->_distanceColumn, this->_obj->getPosition().z));
			
		}

		this->_selectedNum++;
	}
}