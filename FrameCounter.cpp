#include "FrameCounter.h"


FrameCounter::FrameCounter()
{
	this->_count = 1;
}


FrameCounter::~FrameCounter()
{
}

void FrameCounter::update()
{
	this->_count++;

	if (this->_count > 60){
		this->_count = 1;
	}
}

int FrameCounter::getCount()
{
	return this->_count;
}

void FrameCounter::reset()
{
	this->_count = 1;
}