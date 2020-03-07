#pragma once
#include <string>
#include "ScreenMaterial.h"
#include <memory>

class Object2DAttribute;

class Object_2D
	:
	public ScreenMaterial
{
private:
	int _handle;
	std::shared_ptr< Object2DAttribute > _attribute;

public:
	void finalize();
	void draw();
	void setPosition(VECTOR position);
	void animation(VECTOR newPos, float speed){};
	bool isAnimationFinish(){ return true; };
	void rotate(float angle){};
	Object_2D(std::string fileName);
	~Object_2D();
};