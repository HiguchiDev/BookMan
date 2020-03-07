#include "Animation.h"

Animation::Animation()
{
	this->_pos = VGet(0, 0, 0);
	this->_destinationPos = VGet(0, 0, 0);
	this->_finish = true;
}


Animation::~Animation()
{

}

void Animation::finalize()
{
	this->_pos = this->_destinationPos;
}

void Animation::start(VECTOR pos, VECTOR destinationPos, float speed)
{
	this->_speed = speed;
	this->_pos = pos;
	this->_destinationPos = destinationPos;
	this->_finish = false;
}

std::shared_ptr<Animation> Animation::getNextAnimation(float speed)
{
	return shared_from_this();
}

bool Animation::isFinish()
{
	return this->_finish;
}

VECTOR Animation::getPos()
{
	return this->_pos;
}