#include "Object_3D_Duplicate.h"
#include "HandleCreater.h"
#include "Animation.h"
#include "SlideAnimation.h"
#include "WarpAnimation.h"

std::unordered_map<std::string, int> HandleCreater::_handleMap;

Object_3D_Duplicate::Object_3D_Duplicate(std::string fileName) : ScreenMaterial(fileName)
{
	this->_animationFinish = true;

	this->_animation = std::make_shared<SlideAnimation>(7.0f);

	SetUseASyncLoadFlag(false);

	HandleCreater handleCreater;

	this->_handle = handleCreater.get3DHandle(fileName);
}


Object_3D_Duplicate::~Object_3D_Duplicate()
{

	this->finalize();
}


void Object_3D_Duplicate::finalize()
{
	HandleCreater handleCreater;
	if (handleCreater.isOriginHandle(this->_handle)){

	}
	else{
		MV1DeleteModel(this->_handle);
	}

	this->_finish = true;
}

void Object_3D_Duplicate::draw()
{
	int correction = 30;

	//座標更新してから描画
	if (this->_visible && this->_handle != -1 && this->isCameraIn()){
		MV1SetPosition(this->_handle, this->_position);
		MV1DrawModel(this->_handle);
	}
}

bool Object_3D_Duplicate::isCameraIn()
{
	int correction = 13;

	if (!CheckCameraViewClip(VGet(this->_position.x + correction, this->_position.y + correction, this->_position.z + correction)) ||
		!CheckCameraViewClip(VGet(this->_position.x - correction, this->_position.y + correction, this->_position.z + correction)) ||
		!CheckCameraViewClip(VGet(this->_position.x + correction, this->_position.y + correction, this->_position.z - correction)) ||
		!CheckCameraViewClip(VGet(this->_position.x - correction, this->_position.y + correction, this->_position.z - correction)) ||
		!CheckCameraViewClip(VGet(this->_position.x + correction, this->_position.y - correction, this->_position.z + correction)) ||
		!CheckCameraViewClip(VGet(this->_position.x - correction, this->_position.y - correction, this->_position.z + correction)) ||
		!CheckCameraViewClip(VGet(this->_position.x + correction, this->_position.y - correction, this->_position.z - correction)) ||
		!CheckCameraViewClip(VGet(this->_position.x - correction, this->_position.y - correction, this->_position.z - correction))){
		return true;
	}

	return false;


}

bool Object_3D_Duplicate::isCameraIn(VECTOR position)
{
	int correction = 13;

	if (!CheckCameraViewClip(VGet(position.x + correction, position.y + correction, position.z + correction)) ||
		!CheckCameraViewClip(VGet(position.x - correction, position.y + correction, position.z + correction)) ||
		!CheckCameraViewClip(VGet(position.x + correction, position.y + correction, position.z - correction)) ||
		!CheckCameraViewClip(VGet(position.x - correction, position.y + correction, position.z - correction)) ||
		!CheckCameraViewClip(VGet(position.x + correction, position.y - correction, position.z + correction)) ||
		!CheckCameraViewClip(VGet(position.x - correction, position.y - correction, position.z + correction)) ||
		!CheckCameraViewClip(VGet(position.x + correction, position.y - correction, position.z - correction)) ||
		!CheckCameraViewClip(VGet(position.x - correction, position.y - correction, position.z - correction))){
		return true;
	}

	return false;


}

void Object_3D_Duplicate::setPosition(VECTOR position)
{
	this->_position = position;

	//	MV1SetPosition(this->_handle, this->_position);
}

void Object_3D_Duplicate::rotate(float angle)
{
	this->_angle = angle;
	MV1SetRotationXYZ(this->_handle, VGet(0.0f, angle * DX_PI_F / 180.0f, 0.0f));
}

void Object_3D_Duplicate::animation(VECTOR newPos, float speed)
{
	//新しい座標がカメラに入っていない && 現在の座標がカメラに入っていない
	if (!this->isCameraIn(newPos) && !this->isCameraIn(this->_position)){
		this->_animation->finalize();
	}
	//新しい座標がカメラに入っている && 現在の座標がカメラに入っていない
	else if (this->isCameraIn(newPos) && !this->isCameraIn(this->_position)){

	}

	if (this->_animation->isFinish()){
		this->_animation = this->_animation->getNextAnimation(speed);

		this->_animation->start(this->_position, newPos, speed);
	}

	this->_animation->update();
	this->_position = this->_animation->getPos();

	this->_animationFinish = this->_animation->isFinish();
}

float Object_3D_Duplicate::getUpdatedPosition(float pos, float newPos, float speed)
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

bool Object_3D_Duplicate::isAnimationFinish()
{
	return this->_animationFinish;
}

