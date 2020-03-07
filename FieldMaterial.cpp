#include "FieldMaterial.h"
#include "ScreenMaterial.h"
#include "PositionConverter.h"
#include "Position.h"
#include "Object_3D.h"
#include "Object_3D_Duplicate.h"

FieldMaterial::FieldMaterial(std::string fileName, std::shared_ptr<Position> position)
{
	this->_screenMaterial = std::make_shared<Object_3D_Duplicate>(fileName);
	

	this->_finish = false;	
	this->_visible = true;
	this->_positionInitialized = false;
	this->_position = position;

	PositionConverter pc;

	this->_screenMaterial->initializePos(pc.get3DPosition(this->_position));
}


FieldMaterial::~FieldMaterial()
{

}


bool FieldMaterial::isFinish()
{
	return this->_finish;
}

bool FieldMaterial::isVisible()
{
	return this->_visible;
}

void FieldMaterial::setVisible(bool visible)
{
	this->_visible = visible;
}

void FieldMaterial::setFieldPos(std::shared_ptr<Position> position)
{
	
	this->updateCollisionInformation(this->_position);
	this->_position = position;
}

std::shared_ptr<Position> FieldMaterial::getPos()
{
	return this->_position;
}

void FieldMaterial::initialize()
{
	//ˆê“x‚¾‚¯ŒÄ‚Ô
	if (this->_positionInitialized == false){
		this->initializePosition();
		this->_positionInitialized = true;
	}
}

bool FieldMaterial::isInitialized()
{
	return this->_screenMaterial->isLoadCompletion();
}

void FieldMaterial::finalize()
{
	this->_screenMaterial->finalize();
	this->_finish = true;
}

void FieldMaterial::draw()
{
	PositionConverter converter;

	this->_screenMaterial->setPosition(converter.get3DPosition(this->_position));

	if (this->_visible){
		this->_screenMaterial->draw();
	}

	
}

void FieldMaterial::action()
{

}