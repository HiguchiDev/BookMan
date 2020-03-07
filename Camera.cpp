#include "Camera.h"
#include <math.h>
#include "Direction_AngleConverter.h"
#include "MoveType_RotateConverter.h"

void Camera::rotate(Direction::Directions DIRECTION)
{
	Direction_AngleConverter converter;

	this->_DIRECTION = DIRECTION;

	if (this->_ragian < -270.0f){
		this->_ragian = 0.0f;
	}

	if (this->_newAngle == 360.0f){
		this->_ragian = 0.0f;
		this->_newAngle = converter.getAngle(DIRECTION);
	}
	else{
		this->_newAngle = converter.getAngle(DIRECTION);
	}

	if (this->_ragian > 180.0f && this->_newAngle == 0){
		this->_newAngle = 360.0f;
	}


	if (this->_newAngle - this->_ragian > 180 ||
		this->_ragian - this->_newAngle > 180){
		this->_newAngle -= 360;
	}
}

Direction::Directions Camera::getDirection()
{
	return this->_DIRECTION;
}

Camera::Camera(VECTOR initialPosition, float speed, VECTOR pPos)
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

	SetCameraNearFar(10.0f, 400.0f);
}


Camera::~Camera()
{

}

void rotate2(float *x, float *y, const double ang, const float mx, const float my){
	const float ox = *x - mx, oy = *y - my;
	*x = (float)(ox * cos(ang) + oy * sin(ang));
	*y = (float)(-ox * sin(ang) + oy * cos(ang));
	*x += mx;
	*y += my;
}

void Camera::update()
{
	this->_position.y = this->getUpdatedPosition(this->_position.y, this->_newPosition.y);

	const float ox = this->_position.x - pPos.x, oy = this->_position.z - pPos.z;
	this->_position.z = (float)sin(this->_ragian * DX_PI_F / 180.f) * -100;
	this->_position.x = (float)cos(this->_ragian * DX_PI_F / 180.f) * 100;

	this->_position.z += pPos.z;
	this->_position.x += pPos.x;

	
	if (this->_newAngle * DX_PI_F / 180.0f > _ragian * DX_PI_F / 180.0f){
		this->_ragian += this->_rotateSpeed;
		if (this->_newAngle * DX_PI_F / 180.0f < this->_ragian * DX_PI_F / 180.0f){
			this->_ragian = this->_newAngle;
		}
		//rotate2(&this->_position.x, &this->_position.z, this->_ragian * DX_PI_F / 180.0f, this->pPos.x, this->pPos.z);

	}
	else if (this->_newAngle * DX_PI_F / 180.0f < _ragian * DX_PI_F / 180.0f){
		this->_ragian -= this->_rotateSpeed;
		if (this->_newAngle * DX_PI_F / 180.0f > this->_ragian * DX_PI_F / 180.0f){
			this->_ragian = this->_newAngle;
		}
		//rotate2(&this->_position.x, &this->_position.z, this->_ragian * DX_PI_F / 180.0f, this->pPos.x, this->pPos.z);
	}

	SetCameraPositionAndTarget_UpVecY(VGet(_position.x, _position.y, _position.z), this->pPos);
}


float Camera::getUpdatedPosition(float pos, float newPos)
{
	if (pos > newPos){
		pos -= this->_speed;
		if (pos < newPos){
			pos = newPos;
		}
	}
	else if(pos < newPos){
		pos += this->_speed;
		if (pos > newPos){
			pos = newPos;
		}
	}

	return pos;
}

void Camera::move(VECTOR newPosition, VECTOR pos)
{
	this->pPos = pos;

	newPosition.y = 220;
	this->_newPosition = newPosition;
	//this->_position = newPosition;
}

void Camera::initialize(VECTOR position)
{
	this->_position = position;

	this->_position.y = 220;

	SetCameraPositionAndAngle(this->_position, 0.0, 0.0, 0.0);
}