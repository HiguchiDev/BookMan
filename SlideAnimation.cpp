#include "SlideAnimation.h"


SlideAnimation::SlideAnimation(float speed)
{
	this->_speed = speed;
}


SlideAnimation::~SlideAnimation()
{
}

void SlideAnimation::update()
{

	this->_pos.x = this->getUpdatedPosition(_pos.x, _destinationPos.x, _speed);
	this->_pos.y = this->getUpdatedPosition(_pos.y, _destinationPos.y, _speed);
	this->_pos.z = this->getUpdatedPosition(_pos.z, _destinationPos.z, _speed);

	if (this->_pos.x == _destinationPos.x &&
		this->_pos.y == _destinationPos.y &&
		this->_pos.z == _destinationPos.z){
		
		this->_finish = true;
	}
	else{
		this->_finish = false;
	}
}

float SlideAnimation::getUpdatedPosition(float pos, float newPos, float speed)
{
	if (pos > newPos){
		pos -= speed;
		this->_finish = false;
		if (pos < newPos){
			pos = newPos;
			this->_finish = true;
		}
	}
	else if (pos < newPos){
		pos += speed;
		this->_finish = false;
		if (pos > newPos){
			pos = newPos;
			this->_finish = true;
		}
	}

	return pos;
}
