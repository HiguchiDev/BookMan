#include "SubjectivityCamera.h"
#include "Character.h"
#include "ScreenMaterial.h"

SubjectivityCamera::SubjectivityCamera(VECTOR initialPosition, float speed, VECTOR pPos, std::shared_ptr<Character> player) : Camera(initialPosition, speed, pPos)
{
	this->_player = player;

	GetMousePoint(&this->_mousePosX, &this->_mousePosY);

	SetCameraNearFar(10.0f, 2000.0f);
}


SubjectivityCamera::~SubjectivityCamera()
{
}

void rotate3(float *x, float *y, const double ang, const float mx, const float my){
	const float ox = *x - mx, oy = *y - my;
	*x = (float)(ox * cos(ang) + oy * sin(ang));
	*y = (float)(-ox * sin(ang) + oy * cos(ang));
	*x += mx;
	*y += my;
}

void SubjectivityCamera::update()
{
	int mousePosX, mousePosY;
	int moveValueX, moveValueY;

	GetMousePoint(&mousePosX, &mousePosY);
	
	moveValueX = this->_mousePosX - mousePosX / 2;
	moveValueY = this->_mousePosY - mousePosY;

	VECTOR pos;
	
	this->_newAngle = -moveValueX;
	pos.y = this->_player->getScreenMaterial()->getPosition().y + moveValueY * 3;
	pos.z = 1.0f;
	
	ConvScreenPosToWorldPos(pos);

	pos.z /= 2;


		this->_position.y = this->getUpdatedPosition(this->_position.y, this->_newPosition.y);

		const float ox = this->_position.x - pPos.x, oy = this->_position.z - pPos.z;
		this->_position.z = (float)sin(this->_ragian * DX_PI_F / 180.f) * -1000;
		this->_position.x = (float)cos(this->_ragian * DX_PI_F / 180.f) * 1000;

		this->_position.z += pPos.z;
		this->_position.x += pPos.x;

		
		
		if (this->_ragian > 360.0f){
			//this->_ragian *= -1;
			this->_ragian = this->_ragian - 360.0f;
			
		}
		else if (this->_ragian < 0.0f){
			this->_ragian += 360.0f;
		}
		

		

		if (this->_newAngle * DX_PI_F / 180.0f > _ragian * DX_PI_F / 180.0f){
			this->_ragian = this->_newAngle;
			if (this->_newAngle * DX_PI_F / 180.0f < this->_ragian * DX_PI_F / 180.0f){
				this->_ragian = this->_newAngle;
			}
			//rotate3(&this->_position.x, &this->_position.z, this->_ragian * DX_PI_F / 180.0f, this->pPos.x, this->pPos.z);

		}
		else if (this->_newAngle * DX_PI_F / 180.0f < _ragian * DX_PI_F / 180.0f){
			this->_ragian = this->_newAngle;
			if (this->_newAngle * DX_PI_F / 180.0f > this->_ragian * DX_PI_F / 180.0f){
				this->_ragian = this->_newAngle;
			}
			//rotate3(&this->_position.x, &this->_position.z, this->_ragian * DX_PI_F / 180.0f, this->pPos.x, this->pPos.z);
		}


		SetCameraPositionAndTarget_UpVecY(this->_player->getScreenMaterial()->getPosition(), VGet(_position.x, pos.y, _position.z));
}

void SubjectivityCamera::initialize(VECTOR position)
{

}

void SubjectivityCamera::move(VECTOR newPosition, VECTOR pos)
{

}

void SubjectivityCamera::rotate(Direction::Directions DIRECTION)
{

}