#include "DamageDisplay.h"
#include "DxLib.h"
#include <string>
#include "Position.h"
#include "PositionConverter.h"

DamageDisplay::DamageDisplay()
{
	SetFontSize(28);
}


DamageDisplay::~DamageDisplay()
{
}

void DamageDisplay::add(std::shared_ptr<Position> pos, int damage)
{
	this->_damegePositions.push_back(pos);
	this->_damegeValueMap[pos] = damage;

	PositionConverter pc;

	this->_damegePositionValueMap[pos] = std::make_shared<BezierCurve_ThreePoint>();

	int initPosX = ConvWorldPosToScreenPos(VGet(pc.get3DPosition(pos).x, pc.get3DPosition(pos).y, pc.get3DPosition(pos).z)).x;
	int initPosY = ConvWorldPosToScreenPos(VGet(pc.get3DPosition(pos).x, pc.get3DPosition(pos).y, pc.get3DPosition(pos).z)).y;

	this->_damegePositionValueMap[pos]->setPoint(initPosX, initPosY, initPosX, initPosY, initPosX, initPosY - 40, 0.06f, 100);
}

void DamageDisplay::update()
{

	for (int i = 0; i < this->_damegePositions.size(); i++){
		
		this->_damegePositionValueMap[this->_damegePositions[i]]->start();

		if (this->_damegePositionValueMap[this->_damegePositions[i]]->isEnd()){
			this->_damegePositions.erase(this->_damegePositions.begin() + i);
			i--;
		}
		else{
			DrawString(this->_damegePositionValueMap[this->_damegePositions[i]]->get_x(), this->_damegePositionValueMap[this->_damegePositions[i]]->get_y(), std::to_string(this->_damegeValueMap[this->_damegePositions[i]]).c_str(), GetColor(255, 0, 0));
		}
	}
}

std::unique_ptr<DamageDisplay> & DamageDisplay::getInstance()
{
	if (_instance.get() == nullptr){
		_instance = std::make_unique<DamageDisplay>();
	}
	return _instance;
}


//std::unique_ptr<DamageDisplay> DamageDisplay::_instance;
