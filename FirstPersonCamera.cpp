#include "FirstPersonCamera.h"
#include "DxLib.h"
#include "Direction.h"
#include "Direction_AngleConverter.h"

FirstPersonCamera::FirstPersonCamera(VECTOR initialPosition, float speed, VECTOR pPos) : Camera(initialPosition, speed, pPos)
{
	this->pPos = pPos;
	this->_rotateSpeed = 10.0;
	this->_ragian = 0.0;
	this->_newAngle = 0.0;
	this->_position = initialPosition;
	this->_newPosition = initialPosition;
	this->_speed = speed;
	SetCameraPositionAndAngle(this->_position, 0.0, 0.0, 0.0);

	Direction_AngleConverter converter;

	this->_DIRECTION = Direction::Directions::NORTH;
	this->_newAngle = converter.getAngle(this->_DIRECTION);

	SetCameraNearFar(5.0f, 1000.0f);
}


FirstPersonCamera::~FirstPersonCamera()
{

}

void FirstPersonCamera::update()
{
	this->_position.x = this->getUpdatedPosition(this->_position.x, this->_newPosition.x);
	this->_position.y = this->getUpdatedPosition(this->_position.y, this->_newPosition.y);
	this->_position.z = this->getUpdatedPosition(this->_position.z, this->_newPosition.z);

	if (this->_newAngle > this->_ragian){
		this->_ragian += 5.0f;
		if (this->_ragian > this->_newAngle){
			this->_ragian = this->_newAngle;
		}
	}
	else{
		if (this->_newAngle < this->_ragian){
			this->_ragian -= 5.0f;
			if (this->_ragian < this->_newAngle){
				this->_ragian = this->_newAngle;
			}
		}
	}

	Direction_AngleConverter dac;

	SetCameraPositionAndAngle(this->_position, 0.0, this->_ragian * DX_PI_F / 180.f, 0.0);
}

void FirstPersonCamera::initialize(VECTOR position)
{
	this->_position = position;
}
