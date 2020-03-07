#include "Object_3D.h"
#include "HandleCreater.h"

Object_3D::Object_3D(std::string fileName) : ScreenMaterial(fileName)
{
	this->_animationFinish = true;

	SetUseASyncLoadFlag(true);
	
	HandleCreater handleCreater;

	this->_handle = MV1LoadModel(this->_fileName.c_str());
}


Object_3D::~Object_3D()
{
	
}


void Object_3D::finalize()
{
	MV1DeleteModel(this->_handle);
	this->_finish = true;
}

void Object_3D::draw()
{
	
	//À•WXV‚µ‚Ä‚©‚ç•`‰æ
	if (this->_handle != -1 && !CheckCameraViewClip(this->_position)){
		MV1SetPosition(this->_handle, this->_position);
		MV1DrawModel(this->_handle);
	}
}

void Object_3D::setPosition(VECTOR position)
{
	this->_position = position;
	MV1SetPosition(this->_handle, this->_position);
}

void Object_3D::rotate(float angle)
{
	MV1SetRotationXYZ(this->_handle, VGet(0.0f, /*MV1GetRotationXYZ(this->_handle).y - */angle * DX_PI_F / 180.0f, 0.0f));
}

void Object_3D::animation(VECTOR newPos, float speed)
{
	this->_position.x = this->getUpdatedPosition(this->_position.x, newPos.x, speed);
	this->_position.y = this->getUpdatedPosition(this->_position.y, newPos.y, speed);
	this->_position.z = this->getUpdatedPosition(this->_position.z, newPos.z, speed);

	MV1SetPosition(this->_handle, this->_position);

	if (this->_position.x == newPos.x &&
		this->_position.y == newPos.y &&
		this->_position.z == newPos.z){
		this->_animationFinish = true;
	}
}

float Object_3D::getUpdatedPosition(float pos, float newPos, float speed)
{
	if (pos > newPos){
		pos -= speed;
		this->_animationFinish = false;
		if (pos < newPos){
			pos = newPos;
			this->_animationFinish = true;
		}
	}
	else if (pos < newPos){
		pos += speed;
		this->_animationFinish = false;
		if (pos > newPos){
			pos = newPos;
			this->_animationFinish = true;
		}
	}

	return pos;
}

bool Object_3D::isAnimationFinish()
{
	return this->_animationFinish;
}