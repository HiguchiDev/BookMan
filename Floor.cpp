#include "Floor.h"
#include "Position.h"
#include "PositionConverter.h"
#include "ScreenMaterial.h"
#include "Collision.h"
#include "Object_3D.h"
#include "Object_3D_Duplicate.h"
#include "FloorObject_3D_Duplicate.h"

Floor::Floor(std::string fileName, std::shared_ptr<Position> position)
{
	this->_position = position;
	this->_screenMaterial = std::make_shared<FloorObject_3D_Duplicate>(fileName);
}


Floor::~Floor()
{

}

bool Floor::isLoadCompetion()
{
	return this->_screenMaterial->isLoadCompletion();
}

void Floor::draw()
{
	PositionConverter converter;

	this->_screenMaterial->setPosition(converter.get3DPosition(this->_position));

	this->_screenMaterial->draw();
}