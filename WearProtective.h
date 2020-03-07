#pragma once
#include <memory>
#include <string>
#include "StatesPoint.h"
#include "ScreenMaterial.h"

class WearProtective
{

public:

	enum Type{
		WITCH,
		SWORDSMAN,
		SUIT,
	};
	std::string _name;
	std::shared_ptr<StatesPoint> getStatesCorrection();
	static std::shared_ptr<WearProtective> createInstance(std::string name);
	std::string toString(){ return this->_name; };
	void giveDamage(int point);
	bool isBroken(){ return this->_broken; };
	WearProtective::Type getType();
	void setDurability(int durability);
	bool _broken;
	WearProtective(std::string name);
	~WearProtective();
protected:
	std::shared_ptr<StatesPoint> _statesCorrection;
	std::shared_ptr<ScreenMaterial> _screenMaterial;
	Type _TYPE;
};

