#pragma once
#include "DxLib.h"
#include "Direction.h"
#include "MoveType.h"

//�R�X�g���N�^�ŏ������W�ƃJ�����̈ړ��X�s�[�h��^���Arotate�֐��ŔC�ӂ̊p�x�ŉ�]����B
//update�𖈃t���[���ĂԂ��Ƃ�move�Őݒ肵�����W�ւ�speed�̑����ňړ�����B
class Camera
{
protected:
	float rotateCount = 0.0f;
	VECTOR _position;
	VECTOR _newPosition;
	float _speed;
	double _rotateSpeed;
	double _newAngle;
	double _ragian;
	VECTOR pPos;
	Direction::Directions _DIRECTION;
	float getUpdatedPosition(float pos, float newPos);

public:
	virtual void update();
	virtual void initialize(VECTOR position);
	virtual void move(VECTOR newPosition, VECTOR pos);
	Direction::Directions getDirection();
	virtual void rotate(Direction::Directions DIRECTION);
	Camera(VECTOR initialPosition, float speed, VECTOR pPos);
	~Camera();
};

