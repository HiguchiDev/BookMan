#pragma once
#include "ScreenMaterial.h"
#include "DxLib.h"
#include <string>

class Object_3D_Duplicate :
	public ScreenMaterial
{
protected:
	bool _animationFinish;
	bool isCameraIn(VECTOR position);
public:
	bool isCameraIn();
	void finalize();
	virtual void draw();
	void setPosition(VECTOR position);
	void rotate(float angle);
	void animation(VECTOR newPos, float speed);
	bool isAnimationFinish();
	float getUpdatedPosition(float pos, float newPos, float speed);
	Object_3D_Duplicate(std::string fileName);
	~Object_3D_Duplicate();
};

