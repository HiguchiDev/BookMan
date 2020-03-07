#pragma once
#include "ScreenMaterial.h"
#include <string>

class Object_3D :
	public ScreenMaterial
{
private:
	bool _animationFinish;
public:
	void finalize();
	void draw();
	void setPosition(VECTOR position);
	void rotate(float angle);
	void animation(VECTOR newPos, float speed);
	bool isAnimationFinish();
	float getUpdatedPosition(float pos, float newPos, float speed);
	Object_3D(std::string fileName);
	~Object_3D();
};

