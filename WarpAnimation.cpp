#include "WarpAnimation.h"
#include "BezierCurve.h"
#include "SlideAnimation.h"

WarpAnimation::WarpAnimation()
{
	this->_bezierCurveXY = std::make_shared<BezierCurve_ThreePoint>();
	this->_bezierCurveXZ = std::make_shared<BezierCurve_ThreePoint>();
	this->_warped = false;
	this->_finish = false;
}


WarpAnimation::~WarpAnimation()
{
}

void WarpAnimation::update()
{
	if (!this->_finish && !this->_warped){
		if (this->_bezierCurveXY->isEnd() && this->_bezierCurveXZ->isEnd() || 
			(this->_pos.x == _destinationPos.x &&
			this->_pos.y == _destinationPos.y &&
			this->_pos.z == _destinationPos.z)){

			this->_warped = true;
			this->_finish = true;
		}
		else{


			
			this->_pos.x = this->_bezierCurveXY->get_x();
			this->_pos.y = this->_bezierCurveXY->get_y();
			this->_pos.z = this->_bezierCurveXZ->get_y();

			this->_bezierCurveXY->start();
			this->_bezierCurveXZ->start();
		}

	}
//	
}

std::shared_ptr<Animation> WarpAnimation::getNextAnimation(float speed)
{
	return std::make_shared<SlideAnimation>(speed);
}

void WarpAnimation::start(VECTOR pos, VECTOR destinationPos, float speed)
{

	this->_pos = pos;
	this->_destinationPos = destinationPos;

	int centerX = (pos.x + destinationPos.x) / 2;
	int centerY = 200;
	int centerZ = (pos.z + destinationPos.z) / 2;

	this->_bezierCurveXY->setPoint(pos.x, pos.y, destinationPos.x, destinationPos.y, centerX, centerY, speed, 100);
	this->_bezierCurveXZ->setPoint(pos.x, pos.z, destinationPos.x, destinationPos.z, centerX, centerZ, speed, 100);

	
	this->_finish = false;
}