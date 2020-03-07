#pragma once
#include "DxLib.h"
#include "Direction.h"
#include "MoveType.h"

//コストラクタで初期座標とカメラの移動スピードを与え、rotate関数で任意の角度で回転する。
//updateを毎フレーム呼ぶことでmoveで設定した座標へとspeedの速さで移動する。
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

