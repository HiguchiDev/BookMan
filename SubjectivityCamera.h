#pragma once
#include "DxLib.h"
#include "Direction.h"
#include "MoveType.h"
#include "Camera.h"
#include <memory>

class Character;

class SubjectivityCamera
	: public Camera
{
private:
	std::shared_ptr<Character> _player;
	int _mousePosX, _mousePosY;
public:
	void update();
	void initialize(VECTOR position);
	void move(VECTOR newPosition, VECTOR pos);
	void rotate(Direction::Directions DIRECTION);
	
	SubjectivityCamera(VECTOR initialPosition, float speed, VECTOR pPos, std::shared_ptr<Character> player);
	~SubjectivityCamera();
};

