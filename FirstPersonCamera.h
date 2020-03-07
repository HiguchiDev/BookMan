#pragma once
#include "Camera.h"

class FirstPersonCamera
	: public Camera
{
public:
	void update();
	void initialize(VECTOR position);
	FirstPersonCamera(VECTOR initialPosition, float speed, VECTOR pPos);
	~FirstPersonCamera();
};

