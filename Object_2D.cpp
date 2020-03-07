#include "Object_2D.h"
#include "Object2DAttribute.h"

Object_2D::Object_2D(std::string fileName) : ScreenMaterial(fileName)
{
	SetUseASyncLoadFlag(false);
	this->_handle = LoadGraph(fileName.c_str());
	//this->_attribute = attribute;
}


Object_2D::~Object_2D()
{
	this->finalize();
}

void Object_2D::finalize()
{
	this->_finish = true;
	DeleteGraph(this->_handle);
}

void Object_2D::draw()
{
	DrawGraph((int)this->_position.x, (int)this->_position.y, this->_handle, TRUE);
}

void Object_2D::setPosition(VECTOR position)
{
	this->_position = position;
	//MV1SetPosition(this->_handle, this->_position);
}