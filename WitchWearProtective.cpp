#include "WitchWearProtective.h"
#include "Object_3D_Duplicate.h"
#include "ScreenMaterial.h"
#include "StatesPoint.h"

WitchWearProtective::WitchWearProtective(std::string name) : WearProtective(name)
{
	//this->_screenMaterial = std::make_shared <Object_3D_Duplicate>();

	this->_TYPE = WearProtective::WITCH;
}


WitchWearProtective::~WitchWearProtective()
{

}
