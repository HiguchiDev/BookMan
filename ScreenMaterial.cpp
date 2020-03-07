#include "ScreenMaterial.h"
#include "Animation.h"

void ScreenMaterial::setPosition(VECTOR position)
{
	this->_position = position;
}

bool ScreenMaterial::isVisible()
{
	return this->_visible;
}

void ScreenMaterial::setVisible(bool visible)
{
	this->_visible = visible;
}

int ScreenMaterial::getHandle()
{
	return this->_handle;
}

float ScreenMaterial::getAngle()
{
	return this->_angle;
}
VECTOR ScreenMaterial::getPosition()
{
	return this->_position;
}

void ScreenMaterial::initializePos(VECTOR position)
{
	this->_position = position;
}

ScreenMaterial::ScreenMaterial(std::string fileName)
{
	this->_loadCompletion = false;
	this->_position = VGet(0, 0, 0);
	this->_visible = true;
	this->_finish = false;
	this->_angle = 0.0f;

	this->_fileName = fileName;
}

bool ScreenMaterial::isLoadCompletion()
{
	return !CheckHandleASyncLoad(this->_handle);
}

ScreenMaterial::~ScreenMaterial()
{

}

bool ScreenMaterial::isFinish()
{
	return this->_finish;
}

void ScreenMaterial::setAnimation(std::shared_ptr<Animation> animation)
{
	if (this->_animation->isFinish()){
		this->_animation = animation;
	}
}