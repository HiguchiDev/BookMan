#include "SwordsMan.h"
#include "Object_3D_Duplicate.h"
#include "ScreenMaterial.h"
#include "StatesPoint.h"

SwordsMan::SwordsMan(std::string name) : WearProtective(name)
{
	//this->_screenMaterial = std::make_shared <Object_3D_Duplicate>();

	this->_TYPE = WearProtective::SWORDSMAN;
}


SwordsMan::~SwordsMan()
{
}
